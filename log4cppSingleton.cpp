//我写的单例模式的log4cpp日志 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
using namespace log4cpp;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ostringstream;

class Mylogger
{
public:
    static Mylogger * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void crit(const char* msg){
        _cate->crit(msg);
    }
    void fatal(const char* msg){
        _cate->fatal(msg);
    }
    void warn(const char* msg){
        _cate->warn(msg);
    }
    void error(const char* msg){
        _cate->error(msg);
    }
    void debug(const char* msg){
        _cate->debug(msg);
    }
    void info(const char* msg){
        _cate->info(msg);
    }
	
private:
    Mylogger(){
        //每个布局只能被绑定一次,一对一
        PatternLayout * ptn1 = new PatternLayout();
        ptn1->setConversionPattern("%d %c [%p] %m%n");
        
        PatternLayout * ptn2 = new PatternLayout();
        ptn2->setConversionPattern("%d %c [%p] %m%n");
        
        //1.日志输出器
            //输出到屏幕终端
        OstreamAppender* pos = new OstreamAppender("console", &cout);
        pos->setLayout(ptn1);
            //输出到文件:基类指针指向派生类对象
        /* Appender* appender2 = new FileAppender("log", "program.log"); */
        /* appender2->setLayout(ptn2); */
            //输出到回滚文件
        RollingFileAppender * rolling = new RollingFileAppender("rollingFile",
                                                "rollingfile.log", 5*128, 9);

        //2.日志记录器
        _cate = &Category::getInstance(string("sub1")); //创建叶对象
        _cate->setPriority(Priority::DEBUG);      //设置日志优先级
        _cate->addAppender(pos);
        _cate->addAppender(rolling);
    }

    ~Mylogger(){
        Category::shutdown();
    }

    Mylogger(const Mylogger & rhs) = delete;
    Mylogger & operator=(const Mylogger & rhs) = delete;

private:
    Category * _cate;
    static Mylogger * _pInstance;
};

Mylogger * Mylogger::_pInstance = nullptr;

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
    
    //规范使用单例模式的写法
    Mylogger::getInstance()->info("The log is info message");
}

void LogInfo(const char * msg){
    ostringstream oss;
    oss << __FILE__ << " " << __FUNCTION__ << " " <<  __LINE__<< " " << msg;
    string res = oss.str();
    Mylogger::getInstance()->info(res.c_str());

    /* char buffer[1024]; */
    /* sprintf(buffer, "%s %s %d %s" ,__FILE__, __FUNCTION__, __LINE__, msg); */
    // Mylogger::getInstance()->error(msg); 
    /* Mylogger::getInstance()->info(buffer); */
}

void LogError(const char * msg){
    ostringstream oss;
    oss << __FILE__ << " " << __FUNCTION__ << " " <<  __LINE__<< " " << msg;
    string res = oss.str();
    Mylogger::getInstance()->info(res.c_str());
}

void LogWarn(const char * msg){
    ostringstream oss;
    oss << __FILE__ << " " << __func__ << " " <<  __LINE__<< " " << msg;
    string res = oss.str();
    Mylogger::getInstance()->info(res.c_str());
}

void LogDebug(const char * msg){
    ostringstream oss;
    oss << __FILE__ << " " << __func__ << " " <<  __LINE__<< " " << msg;
    string res = oss.str();
    Mylogger::getInstance()->info(res.c_str());
}

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}

//第三步:最终希望的效果
 //LogDebug("The log is debug message");
//日期 记录器名字 [优先级] 文件名 函数名 行号 日志信息

int main()
{
    /* test0(); */
    int count = 50;
    while(count--){
        test1();
    }
    return 0;
}
