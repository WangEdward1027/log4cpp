#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <string>
using namespace log4cpp;
using std::string;

int main()
{
    //要读取的配置文件名
	string initFileName = "log4cpp.properties";
	PropertyConfigurator::configure(initFileName);

	Category & root = Category::getRoot();

	Category & sub1 = Category::getInstance(string("sub1"));

	Category & sub2 = Category::getInstance(string("sub1.sub2"));

	root.warn("Storm is coming");

	sub1.debug("Received storm warning");
	sub1.info("Closing all hatches");

	sub2.debug("Hiding solar panels");
	sub2.error("Solar panels are blocked");
	sub2.debug("Applying protective shield");
	sub2.warn("Unfolding protective shield");
	sub2.info("Solar panels are shielded");

	sub1.info("All hatches closed");

	root.info("Ready for storm.");

	Category::shutdown();

	return 0;
}
