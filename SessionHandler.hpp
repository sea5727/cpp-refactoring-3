#ifndef __SESSION_HANDLER_HPP__
#define __SESSION_HANDLER_HPP__

#include "inc.hpp"


class SessionHandler : public std::enable_shared_from_this<SessionHandler> {
private:
    std::function<void (char[], int)> mReceiveEventHandler;
public:
    void ReceiveEventHandler( const std::function<void(char[], int)>& eventHandler )
    {
        mReceiveEventHandler = eventHandler;
    }
public :
    SessionHandler(boost::asio::io_service & io_service)
        : _io_service(io_service)
        , _socket(io_service)
        , _strand(io_service)
        
    {
        std::cout << "SessionHandler.." << std::endl;
        mReceiveEventHandler = nullptr;
    }
    
    ~SessionHandler(){}

public :
    void start()
    {
        read_packet();
    }
    boost::asio::ip::tcp::socket & socket()
    {
        return _socket;
    }
    void read_packet()
    {
        boost::asio::async_read( _socket, 
                                boost::asio::buffer(_packet_buffer),
                                boost::asio::transfer_at_least(1),
                                [me=shared_from_this()](boost::system::error_code const & error_code, std::size_t read_size){
                                    me->read_packet_done(error_code, read_size);
                                });
    }
    void read_packet_done(boost::system::error_code const & error_code, std::size_t read_size)
    {
        if(error_code) 
        {
            std::cout << "read_packet_done.. error : " << error_code.message() << std::endl;
            _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            // _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
            return;

        }
        std::cout.write(&_packet_buffer[0], read_size);
        if(mReceiveEventHandler != nullptr)
        {
            mReceiveEventHandler(_packet_buffer.c_array(), read_size);
        }
        // printf("recv... %s", _packet_buffer);
        read_packet();
    }

private:
    boost::asio::io_service & _io_service;
    boost::asio::ip::tcp::socket _socket;
    boost::array<char, 8192> _packet_buffer;
    boost::asio::io_service::strand _strand;

};

#endif