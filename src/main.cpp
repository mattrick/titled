#include <QApplication>
#include <QSettings>
#include <QTextCodec>

#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication::setOrganizationName("mattrick");
    QApplication::setOrganizationDomain("none.empty");
    QApplication::setApplicationName("titled");
    QApplication::setApplicationVersion("0.2.1");

    QSettings::setDefaultFormat(QSettings::IniFormat);

    MainWindow mainWin;

    mainWin.setWindowTitle(QApplication::applicationName()+" v"+QApplication::applicationVersion());
    mainWin.show();

    return app.exec();
}
