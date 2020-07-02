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
        OnConnected();
        read_packet();
    }
    boost::asio::ip::tcp::socket & socket()
    {
        return _socket;
    }
    void read_packet()
    {
        
        boost::asio::async_read( _socket, 
                                boost::asio::buffer(_read_buffer),
                                boost::asio::transfer_exactly(8192) , 
                                // boost::asio::transfer_at_least(1),
                                [me=shared_from_this()](boost::system::error_code const & error_code, std::size_t read_size){
                                    me->read_packet_done(error_code, read_size);
                                });
    }
    void read_packet_done(boost::system::error_code const & error_code, std::size_t read_size)
    {
        if(error_code) 
        {
            // boost::asio::ip::tcp::endpoint endpoint = _socket.remote_endpoint(error_code);
            try 
            { 
                std::cout << "read_packet_done.. error : " << error_code.message() << std::endl;
                _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                // _socket.close();
            }
            catch(std::exception const& e) 
            {
                std::cout << "catch!! e.what : " << e.what() << std::endl; 
            }
            catch(...) 
            { 
                std::cout << "whoops!" << std::endl; 
            }
            
            std::cout << "exception??? " << error_code.message() << std::endl;
            // _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            // _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
            return;

        }
        // std::cout.write(&_read_buffer[0], read_size);
        if(mReceiveEventHandler != nullptr)
        {
            mReceiveEventHandler(_read_buffer.c_array(), read_size);
        }
        OnReaded(_read_buffer, read_size);
        read_packet();
    }

    void send_packet(boost::array<char, 8192> write_buffer, std::size_t size)
    {
        boost::asio::async_write(_socket, 
                                  boost::asio::buffer(write_buffer, size), 
                                [me=shared_from_this()](boost::system::error_code error_code, std::size_t write_size){
                                    me->write_packet_done(error_code, write_size);

        });
    }
    void write_packet_done(boost::system::error_code error_code, std::size_t write_size)
    {
        if(error_code)
        {
            // std::cerr << "write_packet_done.. error: " << error_code.message() << std::endl;
            return;
        }
        OnWrited();
        // std::cout << "write! success : " << write_size << std::endl;
    }  
    virtual void OnConnected() = 0;
    virtual void OnReaded(boost::array<char, 8192> read_buffer, std::size_t size) = 0;
    virtual void OnWrited() = 0;

public:
    boost::asio::io_service & _io_service;
    boost::asio::ip::tcp::socket _socket;
    boost::array<char, 8192> _read_buffer;
    boost::asio::io_service::strand _strand;
};

#endif