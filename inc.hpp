#ifndef __INC_HPP__
#define __INC_HPP__

#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind/bind.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <memory>
#include "io_service_pool.hpp"
#include "layer.hpp"
#include "SessionHandler.hpp"


#include "AcceptHandler.hpp"
#include "WorkerHandler.hpp"
#include "ChildSessionHandler.hpp"
#include "ProcessManager.hpp"



#include "singleton.hpp"
// #include "mysingleton.hpp"

extern ProcessManager pm;

#endif