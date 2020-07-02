#ifndef __WORKER_HANDLER_HPP__
#define __WORKER_HANDLER_HPP__


class WorkerHandler : public layer
{
public:
    WorkerHandler()
        : _worker_services(16)
    {

    }
    ~WorkerHandler()
    {

    }
    void start()
    {
        _worker_services.run();
        
    }
    virtual void do_fun() { /* implementation here */ }

    boost::asio::io_service & get_io_service()
    {
        return _worker_services.get_io_service();
    }


private:

    io_service_pool _worker_services;
};

#endif