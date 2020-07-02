#ifndef __TEST_HPP__
#define __TEST_HPP__

class testclass{
public:
    testclass(){}
    ~testclass(){}
    virtual void testfunc()
    {

    }

    virtual void testfunc2() = 0;
};

#endif