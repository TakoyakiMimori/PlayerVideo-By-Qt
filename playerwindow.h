#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H


#include <QWidget>
#include <QIcon>
#include <QTimer>
#include <ui_playerwindow.h>
#include "CVlc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayerWindow;
}
QT_END_NAMESPACE

class TimeMatrix{
public:
    TimeMatrix();
    void SetTimePos(int pos);
    void SetTimeLen(int len);
    QString GetTime();
private:
    int hour_now = 0;
    int min_now = 0;
    int sec_now = 0;
    int hour_tol = 0;
    int min_tol = 0;
    int sec_tol = 0;
};

class PlayerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWindow(QWidget *parent = nullptr);
    ~PlayerWindow();
private slots:
    void onPlayClicked();
    void onPauseClicked();
    void onStopClicked();
    void onTimerTimeout();

    //void onPosSliderChanged(int pos);
    void onPosSliderClicked();
    void onPosSliderReleased();
    void onPosSliderMoving(int pos);

    void onVolumeSliderChanged(int volume);
    void onRateChanged();

private:
    Ui::PlayerWindow* ui;
    QIcon m_icon;
    bool m_isLoaded;
    bool m_isPlay;
    bool m_isPause;
    bool m_isSetHwnd;
    QTimer* m_timer;
    CVlc m_vlc;
    int m_pos;
    int m_len;
    std::wstring m_path;
    float m_rate;
    TimeMatrix time_matrix;
signals:
};



#endif // PLAYERWINDOW_H
