#include "unit_test.hh"


namespace unittest
{

void
TestSpec::test(int(*fn)(), std::string tname)
{
    Test t(tname, fn);
    test_cases.push_back(t);
}

bool TestSpec::run() 
{   
    bool total = false;
    for(Test& t : test_cases) {

        printf("TestCases: %s\n", t.name.c_str());
        printf("====== Standard Output =====\n");
        bool ok = t.fn();
        printf("====== End of Output   =====\n");
        if(ok == 0) {
            printf("\n[Pass]\n");
        } else {
            printf("\n[Failed]\n");
        }
        total |= ok;
    }
    return total;
}






}


