#include "inc.hpp"

void externtestfunction(std::string where)
{
    std::cout << "where : " << where << "this thread id : " << std::this_thread::get_id() << std::endl;
    pm.run();
}


void ChildSessionHandler::OnReaded(std::shared_ptr<std::vector<char>> read_data, std::size_t size) 
{ 
    std::cout << "OnReaded!!! size : " << size << std::endl;

    // auto io = pm.wh.get_io_service();
    boost::asio::io_service &io = pm.wh.get_io_service();
    // io.post(std::bind(externtestfunction, "worker"));

    io.post([&]{
        boost::asio::io_service &ifo = this->_io_service;
        ifo.post([&]{
            std::cout << "iof post!!!" << std::endl;
            send_packet(reinterpret_cast<char*>(read_data->data()), read_data->size());
            
        });
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

