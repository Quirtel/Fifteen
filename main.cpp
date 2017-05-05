#include "fifteen.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("Neridia, Inc.");
	QCoreApplication::setOrganizationDomain("neridia-nova.com");
	QCoreApplication::setApplicationName("Fifteen");

	MainWindow w;
	w.show();

	return a.exec();
}
