#ifndef __SESSION_HANDLER_HPP__
#define __SESSION_HANDLER_HPP__

#include "inc.hpp"


class SessionHandler : public std::enable_shared_from_this<SessionHandler> {
public :
    SessionHandler(boost::asio::io_service & io_service)
        : _io_service(io_service)
        , _socket(io_service)
        , _strand(io_service)
        
    {
        memset(buffer, 0x00, sizeof(buffer));
        std::cout << "SessionHandler.." << std::endl;
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
                                boost::asio::buffer(buffer),
                                // boost::asio::transfer_exactly(8192) , 
                                boost::asio::transfer_at_least(1),
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


        // std::shared_ptr<std::vector<char>> read_data = std::make_shared<std::vector<char>>(_read_buffer.begin(), _read_buffer.begin() + read_size);
        OnReaded(buffer, read_size);
        // memset(buffer, 0x00, sizeof(buffer);
        read_packet();
    }

    // void send_packet(boost::array<char, 8192> write_buffer, std::size_t size)
    void send_packet(char* send_buffer, std::size_t size)
    {
        boost::asio::async_write(_socket, 
                                  boost::asio::buffer(send_buffer, size), 
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
    virtual void OnReaded(char read_data[], std::size_t size) = 0;
    virtual void OnWrited() = 0;

public:
    boost::asio::io_service & _io_service;
    boost::asio::ip::tcp::socket _socket;
    // std::vector<char> _read_buffer;
    boost::array<char, 8192> _read_buffer;
    char buffer[8192];
    boost::asio::io_service::strand _strand;

    std::vector<boost::shared_ptr<boost::asio::deadline_timer>> timers;
};

#endif