
#ifndef __PROCESS_MANAGER_HPP__
#define __PROCESS_MANAGER_HPP__

#include "inc.hpp"

// class ProcessManager : public singleton<ProcessManager>
// {
// friend class singleton<ProcessManager>; 
// protected: 
//     ProcessManager() // 생성자와 소멸자의 구현 내용은 헤더에 기술되어야 한다. 
//     {

//     } 
// private: // delete가 불가능하도록 소멸자는 반드시 private으로 선언한다. 
//     ~ProcessManager() 
//     {

//     } 
class ProcessManager
{
public: // 사용하고자 하는 함수를 추가한다. // 실제 사용하는 함수는 마음대로 적절하게 구현한다. 
    ProcessManager(){}
    ~ProcessManager(){}
    void work() const; 
    int run()
    {
        std::cout << "this is pm run" << std::endl;
    }
public:
    AcceptHandler<ChildSessionHandler> cln;
    WorkerHandler wh;
};

#endif