#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("mattrick");
    QApplication::setOrganizationDomain("none.empty");
    QApplication::setApplicationName("filmweb");
    QApplication::setApplicationVersion("0.2");

    MainWindow mainWin;

    mainWin.setWindowTitle(QApplication::applicationName()+" v"+QApplication::applicationVersion());
    mainWin.show();

    return app.exec();
}
