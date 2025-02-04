#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H


#include <QWidget>
#include <ui_playerwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayerWindow;
}
QT_END_NAMESPACE
class PlayerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWindow(QWidget *parent = nullptr);
    ~PlayerWindow();
private:
    Ui::PlayerWindow* ui;
signals:
};

#endif // PLAYERWINDOW_H
