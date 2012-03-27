#include "Collection.hpp"
#include "CollectionModel.hpp"

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
	Collection c;
	c.Rebuild();

    QApplication app(argc, argv);
    MainWindow mainWin;

    mainWin.show();

    return app.exec();
}
