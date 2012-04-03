#include <QApplication>
#include <QSettings>
#include <QTextCodec>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication::setOrganizationName("mattrick");
    QApplication::setOrganizationDomain("none.empty");
    QApplication::setApplicationName("filmweb");
    QApplication::setApplicationVersion("0.2");

    QSettings::setDefaultFormat(QSettings::IniFormat);

    MainWindow mainWin;

    mainWin.setWindowTitle(QApplication::applicationName()+" v"+QApplication::applicationVersion());
    mainWin.show();

    return app.exec();
}
