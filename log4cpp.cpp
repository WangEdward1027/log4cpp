//BasicLayout,少量注释版

#include "log4cpp/Appender.hh"
#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include <iostream>
#include <fstream>
#include <string>
using namespace log4cpp;
using std::cout;
using std::string;
using std::ofstream;

int main()
{
    //1.日志输出器
    Appender* appender1 = new OstreamAppender("console", &cout);  
    appender1->setLayout(new BasicLayout());
    
    Appender* appender2 = new FileAppender("log", "program.log");
    appender2->setLayout(new BasicLayout());

    Appender* appender3 = new FileAppender("log", "program.log");
    appender3->setLayout(new BasicLayout());

    std::ofstream ofs("program2.log");
    OstreamAppender * appender4 = new OstreamAppender("file", &ofs);
    appender4->setLayout(new BasicLayout());
    
    //2.日志记录器
    Category & root = Category::getRoot(); //用getRoot()创建根对象
    root.setPriority(Priority::WARN);      //设置日志优先级
    root.addAppender(appender1);
    
    Category & sub1 = Category::getInstance(string("sub1"));//创建叶对象
    sub1.addAppender(appender2);
    
    Category & sub2 = Category::getInstance(string("sub2"));
    sub2.addAppender(appender3);

    Category & sub11 = Category::getInstance(string("sub1.sub11"));
    sub11.setAdditivity(false); //不继承
    sub11.addAppender(appender4);

    //输出日志:方式1
    root.error("root error");
    root.info("root info");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");
    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    sub11.error("sub11 error");
    
    //方式2
    sub11.warn("%d + %d == %s", 1, 1 ,"two");

    //方式3
    root << Priority::ERROR << "Streamed root error";
    root << Priority::INFO << "Streamed root info";
    sub1 << Priority::ERROR << "Streamed sub1 error";
    sub1 << Priority::WARN << "Streamed sub1 warn";

    //方式4
    sub2.errorStream() << "errorStream";
    sub2.warnStream() << "warnStream()";

    Category::shutdown();

    return 0;
}
