#include "MyApplication.hpp"

int main(int argc, char *argv[])
{
	MyApplication myapp(argc, argv);

	/*QApplication::setOrganizationName("mattrick");
	QApplication::setOrganizationDomain("none.empty");
	QApplication::setApplicationName("titled");
	QApplication::setApplicationVersion("0.3");*/

	return myapp.exec();
}
