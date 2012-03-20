#include "Collection.hpp"

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
	Collection c;
	c.Rebuild();

    QApplication app(argc, argv);
    app.setOrganizationName("Trolltech");
    app.setApplicationName("Application Example");
    MainWindow mainWin;

    mainWin.show();

    return app.exec();
}
