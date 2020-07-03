#ifndef __LISTEN_HANDLER_HPP__
#define __LISTEN_HANDLER_HPP__

#include "inc.hpp"


template <typename ConnectionHandler>
class AcceptHandler : public layer
{
    using shared_hantler_t = std::shared_ptr<ConnectionHandler>;
public : 
    AcceptHandler()
         : _io_service(1)
         , _acceptor(_io_service)
         , _if_services(8)
    {
        // std::cout << "AcceptHandler.." << std::endl;
    }
    // virtual void do_fun() { /* implementation here */ }
    void start(uint16_t port)
    {
        
        
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        _acceptor.open(endpoint.protocol());
        _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        _acceptor.bind(endpoint);
        _acceptor.listen();

        auto handler = std::make_shared<ConnectionHandler> (_if_services.get_io_service());
        
        _acceptor.async_accept( handler->socket(),
                                [=](boost::system::error_code error_code){
                                    handle_new_connection(handler, error_code);
                                });
        
        _if_services.run();
        _accept_threads.emplace_back([&] {
            _io_service.run();
        });

    }
    boost::asio::io_service & get_if_service()
    {
        return _if_services.get_io_service();
    }
private:
    void handle_new_connection( shared_hantler_t handler , boost::system::error_code const & error_code)
    {
        if(error_code) 
        {
            std::cout << "handle_new_connection.. error : " << error_code.message() << std::endl;
            return;
        }
        handler->start();

        // auto nh = std::shared_ptr<SessionHandler>(_if_services.get_io_service());
        
        auto new_handler = std::make_shared<ConnectionHandler> (_if_services.get_io_service());
        
        _acceptor.async_accept( new_handler->socket(), 
                                [=](boost::system::error_code error_code) {
                                    handle_new_connection(new_handler, error_code );
                                });
    }


private:
    std::vector<std::thread> _accept_threads;
    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::acceptor _acceptor;
    io_service_pool _if_services;


    
    

};

#endif