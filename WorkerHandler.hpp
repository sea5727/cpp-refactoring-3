#ifndef __WORKER_HANDLER_HPP__
#define __WORKER_HANDLER_HPP__


class WorkerHandler
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

private:

    io_service_pool _worker_services;
};

#endif