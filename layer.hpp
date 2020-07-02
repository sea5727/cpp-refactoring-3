#ifndef __LAYER_HPP__
#define __LAYER_HPP__

#include "inc.hpp"

class Ilayer
{
public:
    // non-virtual interface
    void fun() { do_fun(); } // equivalent to "this->do_fun()"
    // enable deletion of a Derived* through a Base*
    virtual ~Ilayer() = default;    
private:
    // pure virtual implementation
    virtual void do_fun() = 0; 
    virtual void send() = 0;
};

class layer : public Ilayer
{
public:
    
    virtual void do_fun() 
    {
        std::cout << "this is do fun!!" << std::endl;
    }
    virtual void send()
    {
        
    }
};

#endif