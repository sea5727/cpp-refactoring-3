#include "inc.hpp"

//2020-07-02
//AcceptHandler 는 TCP의 port? 및 if_thread 관리
//SessionHandler 는 TCP의 read , write, close 등 정책 정의 , 세션 객체 ( socket 당 1개의 객체 )
//ChildSessionHandler 는 application 단 로직 구현 ?
//                      사설 프로토콜이 될수도 있고                    


/* Naming : 
 * TCPServer
 * TCPSession
 * ~~Protocol
 * ClnProtocol
**/

// ChildSesionHandler를 수정하여 아래를 구현해야할듯하다 ? 
// 1. TCP size 동일하게 전송
// 2. TCP HEADER 사설규격 ? 
// 3. HTTP ? 
// 4. 기타 사설규격 ㅎㄷㄷ하다...


ProcessManager pm;


void userFunction(char buffer[], int size) // tcp server recv handler
{
    // printf("buffer : %s", buffer);
    // std::cout << "this is user function " << std::endl;


    ///////////////////////////////
    // cln.send.to.worker(buf);

}
int main(int, char**) {

    

    AcceptHandler<ChildSessionHandler> &cln = pm.cln;
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

