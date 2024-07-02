//编译时，g++ log4cppTest.cpp -llog4cpp -lpthread

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
using namespace log4cpp;

int main(int argc, char* argv[]) {
	//1.Appender代表输出器 (决定日志的目的地)
    //ostreamAppender构造函数的第一个参数代表目的地名字
    //第二个参数是一个ostream *,决定了目的地。这里传入&cout表示输出到终端
    Appender *appender1 = new OstreamAppender("console", &std::cout);
	//目的地与日志格式 进行了绑定
    appender1->setLayout(new BasicLayout());
    
    //2.FileAppender构造函数的第一个参数代表目的地名字
    //第二个参数是要将日志保存到文件的文件名字
    Appender *appender2 = new FileAppender("default", "program.log");
	appender2->setLayout(new BasicLayout());
    
    //3.getRoot创建出root级别的Category对象 ()记录器对象
	Category& root = Category::getRoot();
	//root设置优先级为WARN级别 (日志系统的优先级,即门槛)
    root.setPriority(Priority::WARN); //设置日志优先级
	//root设置目的地 —— 输出到终端
    root.addAppender(appender1);

    //getInstance创建了一个名为sub1的叶子级别的Category对象
    //sub1继承了root的优先级和目的地
	Category& sub1 = Category::getInstance(std::string("sub1"));
	//在输出到终端的基础上, 还会将日志信息保存到文件 (添加了一个目的地)
    sub1.addAppender(appender2);

	// use of functions for logging messages
	root.error("root error"); //error函数决定了这条日志信息的优先级为EROR
	root.info("root info");  //pass
	sub1.error("sub1 error"); //输出到终端并保存文件
	sub1.warn("sub1 warn");  //输出到终端并保存文件

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two"); //终端

	// use of streams for logging messages
	root << Priority::ERROR << "Streamed root error"; //终端
	root << Priority::INFO << "Streamed root info";  //pass
	sub1 << Priority::ERROR << "Streamed sub1 error"; //终端+文件
	sub1 << Priority::WARN << "Streamed sub1 warn"; //终端+文件

	// or this way:
	root.errorStream() << "Another streamed error"; //终端

	return 0;
}
