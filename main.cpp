#include "inc.hpp"


struct _if_login_req{
    int a;
    int b;
    int c;
};

ProcessManager pm;

//tmf.tasks.
void userFunction(char buffer[], int size)
{
    printf("buffer : %s", buffer);
    std::cout << "this is user function " << std::endl;
    // pm.cln.send.to.wh(buf);
    
}
int main(int, char**) {

    

    AcceptHandler<SessionHandler> &cln = pm.cln;
    cln.ReceiveEventHandler(&userFunction);
    // AcceptHandler<SessionHandler> cln;
    cln.start(5103); 
    
    WorkerHandler &wh = pm.wh;
    // WorkerHandler wh;
    wh.start(); 
    

    // ProcessManager::getInstance().run();

    while(1)
    {
        // std::cout << "Hello, world!?\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}

