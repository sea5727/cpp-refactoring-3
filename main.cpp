#include "inc.hpp"


int main(int, char**) {

    AcceptHandler<SessionHandler> cln;
    cln.start(5103); // 8 + 1 thread + mainthread 1 = 10
    
    WorkerHandler wh;
    wh.start(); //worker 16 : total 26
    
    while(1)
    {
        // std::cout << "Hello, world!?\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}

