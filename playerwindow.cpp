#include "playerwindow.h"
#include "ui_playerwindow.h"

PlayerWindow::PlayerWindow(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);
    setWindowTitle("VideoPlayer");
    resize(800,600);

}
PlayerWindow::~PlayerWindow(){
    delete ui;
}
