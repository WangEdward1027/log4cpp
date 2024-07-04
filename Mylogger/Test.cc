#include "Mylogger.hh"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void test0(){
    Mylogger::getInstance()->warn("The log is a warn message");
    Mylogger::getInstance()->error("The log is an error message");
    Mylogger::getInstance()->info("The log is an info message");
    Mylogger::getInstance()->debug("this is a debug msg");
    Mylogger::destroy();
}

void test1(){
    cout << __FILE__ << endl;
    cout << __func__ << endl;
    cout << __LINE__ << endl;
}


void test2(){
    cout << addPrefix("this is a msg") << endl;
}

void test3(){
    /* Mylogger::getInstance()->warn(addPrefix("The log is a warn message")); */
    LogWarn("this is a warn msg");
    Mylogger::destroy();
}

int main(void){
    test3();
    return 0;
}
