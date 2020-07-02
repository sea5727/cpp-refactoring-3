#ifndef __CHILD_SESSION_HANDLER_HPP__
#define __CHILD_SESSION_HANDLER_HPP__

#include "inc.hpp"

void externtestfunction(std::string where);

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
    virtual void OnReaded(std::shared_ptr<std::vector<char>> read_buffer, std::size_t size);
    virtual void OnWrited();

public :


};

#endif