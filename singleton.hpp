#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

template <class T> 
class singleton 
{ 
public: 
    static T& getInstance(void) 
    { 
        static T object; return object; 
    }
    
    static T* getPointer(void) 
    { 
        return &getInstance(); 
    } 
    
    static const T& getConst(void) 
    { 
        return getInstance(); 
    } 

protected: 
    singleton() 
    {

    } 
    ~singleton() 
    {

    } 
private: 
    singleton(const singleton&); 
    singleton& operator=(const singleton&); 
};



 #endif