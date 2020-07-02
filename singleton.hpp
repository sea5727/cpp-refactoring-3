#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

template <class T> 
class singleton 
{
private: 
    // static T * _object; 
    
public: 
    static T & getInstance(void) 
    {
        static T _object;
        return _object;
    }
    
    static T* getPointer(void) 
    { 
        return &getInstance(); 
    } 
    
    static const T& getConst(void) 
    { 
        return getInstance(); 
    } 

public: 
    singleton() 
    {

    } 
    ~singleton() 
    {

    } 
    singleton(const singleton&){};   
    singleton& operator=(const singleton&); 
};



 #endif