#include "inc.hpp"

void externtestfunction(std::string where)
{
    std::cout << "where : " << where << "this thread id : " << std::this_thread::get_id() << std::endl;
    pm.run();
}


void ChildSessionHandler::OnReaded(char read_data[], std::size_t size) 
{ 
    std::cout <<  "Data : " << read_data << "OnReaded!!! size : " << size << std::endl;

//여기는 interface thread 구간임.
//버퍼포인터를 worker로 넘겨준다.

    boost::shared_ptr<char> p_buffer(new char[size], std::default_delete<char[]>());
    std::copy(read_data, read_data + size, p_buffer.get());
    
    // auto io = pm.wh.get_io_service();
    boost::asio::io_service &io = pm.wh.get_io_service();
    // io.post(std::bind(externtestfunction, "worker"));

    io.post([p_buffer, size]{
        //working..
        std::cout <<  "Data : " << p_buffer << "worker!!! size : " << size << std::endl;
        // boost::asio::io_service &ifo = this->_io_service;
        
        // ifo.post([p_buffer, size]{
        //     std::string if_str(read_data->begin(), read_data->end());
        //     // std::cout << "addr : " << &read_data << "Data : " << read_data << "OnReaded!!!" << str << " size : " << size << std::endl;
        //     send_packet(reinterpret_cast<char*>(read_data->data()), read_data->size());
            
        //     boost::shared_ptr<boost::asio::deadline_timer> ptr_dt(new boost::asio::deadline_timer(this->_io_service, boost::posix_time::seconds(5)));
        //     ptr_dt->async_wait(boost::bind(&externtestfunction, "test"));
        //     this->timers.push_back(ptr_dt);
        // });

    });
    
}

void ChildSessionHandler::OnWrited()
{
    std::cout << "OnWrited!!!" << std::endl;
    // pm.run();
    // cln.send.to.wh("data");
    pm.cln.do_fun();
    // pm.wh.do_task
    // send_to_worker()

    pm.wh.get_io_service();
}

