#ifndef __CHILD_SESSION_HANDLER_HPP__
#define __CHILD_SESSION_HANDLER_HPP__

#include "inc.hpp"


class ChildSessionHandler : public SessionHandler{

public :
    ChildSessionHandler(boost::asio::io_service & io_service) : SessionHandler(io_service)
    {
    }
    
    ~ChildSessionHandler()
    {
    }
    virtual void OnConnected()
    {
        // std::cout << "OnConnected!!!" << std::endl;
    }
    virtual void OnReaded(boost::array<char, 8192> read_buffer, std::size_t size) 
    { 
        std::cout << "OnReaded!!! size : " << size << std::endl;

        send_packet(read_buffer, size);
    }
    virtual void OnWrited()
    {
        // std::cout << "OnWrited!!!" << std::endl;
    }

public :


};

#endif