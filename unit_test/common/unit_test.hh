#ifndef __UNIT_TEST__
#define __UNIT_TEST__


#include <string>
#include <vector>

namespace unittest
{


class TestSpec
{

public:

    
    class Test {
    public:
        std::string name;
        int(*fn)();
        Test(std::string name_, int(*fn_)()) 
            : name(name_), fn(fn_)
        {}
    };

    std::string name;
    std::vector<Test> test_cases;
    
    int num_testcases;

    TestSpec(std::string name_)
        : name(name_)
    {}

    void test(int(*fn)(), std::string tname);

    bool run();
    


};




}








#endif