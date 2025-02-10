#include "mainwindow.h"
#include "playerwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerWindow videoplayer;
    videoplayer.show();
    return a.exec();
}
