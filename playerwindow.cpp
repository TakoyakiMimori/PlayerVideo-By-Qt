#include "playerwindow.h"
#include "ui_playerwindow.h"
#include <windows.h>
#include <QString>

PlayerWindow::PlayerWindow(QWidget *parent)
    : QWidget{parent},
    m_isPlay(false)

{
    // Create the user interface
    TimeMatrix time_matrix;
    ui->setupUi(this);
    setWindowTitle("VideoPlayer");
    resize(800,600);
    // Set the icon for the window
    m_icon.addFile(":/icons/videoplayer.png");
    setWindowIcon(m_icon);
    // initialize the volume
    ui->VolumeSlider->setRange(0,100);
    ui->VolumeSlider->setValue(50);
    // initialize the rate
    ui->RateComboBox->setCurrentIndex(1);

    // Connect the signals and slots
    m_timer = new QTimer(this);
    ui->VedioSlider->setTracking(true);
    m_len = 0;
    m_pos = 0;
    m_isSetHwnd = false;
    connect(m_timer, &QTimer::timeout, this, &PlayerWindow::onTimerTimeout);
    connect(ui->PlayButton, &QPushButton::clicked, this, &PlayerWindow::onPlayClicked);
    connect(ui->PauseButton, &QPushButton::clicked, this, &PlayerWindow::onPauseClicked);
    connect(ui->StopButton, &QPushButton::clicked, this, &PlayerWindow::onStopClicked);
    //connect(ui->VedioSlider, &QSlider::valueChanged, this, &PlayerWindow::onPosSliderChanged);
    connect(ui->VedioSlider, &QSlider::sliderPressed, this, &PlayerWindow::onPosSliderClicked);
    connect(ui->VedioSlider, &QSlider::sliderReleased, this, &PlayerWindow::onPosSliderReleased);
    connect(ui->VedioSlider, &QSlider::sliderMoved, this, &PlayerWindow::onPosSliderMoving);
    connect(ui->VolumeSlider, &QSlider::valueChanged, this, &PlayerWindow::onVolumeSliderChanged);
    connect(ui->RateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PlayerWindow::onRateChanged);
}
PlayerWindow::~PlayerWindow(){
    delete ui;
}

void PlayerWindow::onPlayClicked(){
    qDebug() << "Debug输出：" << "开始播放 视频长度是" << m_len << "秒" << "\n";
    qDebug() << "Debug输出：" << "视频是否设置窗口" << m_isSetHwnd << "\n";
    qDebug() << "Debug输出：" << "视频是否正在播放" << m_isPlay << "\n";
    if(m_isPlay){
        setWindowTitle("正在播放中");
        return;
    }
    //检测加载
    std::wstring m_url = ui->PlayerUrl->text().toStdWString();
    m_isLoaded = m_vlc.LoadMedia(m_url);
    if(!m_isLoaded){
        setWindowTitle("加载视频失败");
        return;
    }
    //检测Hwnd是否为空

    if(m_len ==0){
        //设置窗口
        m_isSetHwnd = m_vlc.SetHWnd(ui->VideoWidget);
        if(!m_isSetHwnd) {
            setWindowTitle("设置窗口失败");
            return;
        }
        else {
            setWindowTitle("设置窗口成功");
        }
        Sleep(500);
        //获取视频长度

        /*while(m_len == 0){
            Sleep(20);
            m_len = m_vlc.GetLength();
        }

        if(m_len != -1) {
            ui->VedioSlider->setRange(0, m_len);
            time_matrix.SetTimeLen(m_len);
            time_matrix.SetTimePos(0);
            QString time = time_matrix.GetTime();
            ui->TimerEdit->setText(time);
            setWindowTitle("播放成功");
            m_timer->start(200);
        }*/
        /*/else {
            setWindowTitle("获取视频长度失败");
            return;
        }*/
    }
    //检测是否可以播放
    m_isPause = false;
    m_isPlay = m_vlc.Play();
    if(m_len == 0){
        while(m_len == 0){
        Sleep(20);
        m_len = m_vlc.GetLength();
    }
        if(m_len != -1) {
        ui->VedioSlider->setRange(0, m_len);
        time_matrix.SetTimeLen(m_len);
        time_matrix.SetTimePos(0);
        QString time = time_matrix.GetTime();
        ui->TimerEdit->setText(time);
        setWindowTitle("播放成功");
        m_timer->start(200);
    }
    }
    if(!m_isPlay){
        setWindowTitle("播放失败");
        return;
    }


    qDebug() << "Debug输出：" << "视频长度是" << m_len << "秒" << "\n";
    qDebug() << "Debug输出：" << "视频路径是" << m_url.c_str() << "\n";
    qDebug() << "Debug输出：" << "视频是否设置窗口" << m_isSetHwnd << "\n";
    qDebug() << "Debug输出：" << "视频是否正在播放" << m_isPlay << "\n";
    return;
}

void PlayerWindow::onPauseClicked(){
    qDebug() << "Debug输出：" <<"视频是否设置窗口" << m_isSetHwnd << "\n";
    qDebug() << "Debug输出：" <<"视频是否正在播放" << m_isPlay << "\n";
    if(!m_isSetHwnd) {
        setWindowTitle("没有设置窗口");
        return;
    }
    if(m_len == 0) {
        setWindowTitle("没有视频正在播放");
        return;
    }
    if(m_isPause) {
        setWindowTitle("视频已暂停");
        return;
    }
    m_vlc.Pause();
    m_isPlay = false;
    m_isPause = true;
    setWindowTitle("暂停");
}

void PlayerWindow::onStopClicked(){
    qDebug() << "Debug输出：" <<"视频是否设置窗口" << m_isSetHwnd << "\n";
    qDebug() << "Debug输出：" <<"视频是否正在播放" << m_isPlay << "\n";
    if(m_len == 0){
        setWindowTitle("没有视频正在播放");
        return;
    }
    m_vlc.Stop();
    m_isPlay = false;
    m_isPause = false;
    m_len = 0;
    m_pos = 0;
    m_isSetHwnd = false;
    m_isLoaded = false;
    setWindowTitle("取消播放");
    m_timer->stop();
    ui->VedioSlider->setValue(0);

}
void PlayerWindow::onTimerTimeout(){
    m_pos = m_vlc.GetPosition();
    ui->VedioSlider->setValue(m_pos);
    time_matrix.SetTimePos(m_pos);
    QString time = time_matrix.GetTime();
    ui->TimerEdit->setText(time);
}

void PlayerWindow::onPosSliderClicked(){
    m_timer->stop();
      //可能会引起问题的功能性语句
    qDebug() << "Debug输出：" << "滑块点击后m_isPlay值为" << m_isPlay << "\n";
}
void PlayerWindow::onPosSliderReleased(){
    m_pos = ui->VedioSlider->value();
    qDebug() << "Debug输出：" << "timeout后播放进度是" << m_pos << "\n";
    m_vlc.SetPosition(m_pos);
    time_matrix.SetTimePos(m_pos);
    QString time = time_matrix.GetTime();
    ui->TimerEdit->setText(time);
    if(m_isPause && !m_isPlay) {m_vlc.Play();} //可能有问题的语句
    m_timer->start(1000);
}

void PlayerWindow::onPosSliderMoving(int pos){ //出现滑动时或跳播时视频声音延迟的问题2月9日
    m_vlc.Pause();
    time_matrix.SetTimePos(pos);
    QString time = time_matrix.GetTime();
    ui->TimerEdit->setText(time);
    m_vlc.SetPosition(pos);
    m_pos != pos ? setWindowTitle("设置视频进度成功"): setWindowTitle("视频进度不变");
    m_vlc.Play();
    m_pos = ui->VedioSlider->value();
    qDebug() << "Debug输出：" << "现在的播放进度是" << pos << "\n";
    qDebug() << "Debug输出：" << "现在的m_pos是" << m_pos << "\n";
}

/*/void PlayerWindow::onPosSliderChanged(int pos){
    m_vlc.SetPosition(pos);
    time_matrix.SetTimePos(pos);
    QString time = time_matrix.GetTime();
    ui->TimerEdit->setText(time);
    setWindowTitle("设置视频进度成功");
    m_vlc.Play();
    m_timer->start(200);

}*/

void PlayerWindow::onVolumeSliderChanged(int pos){
    m_vlc.SetVolume(pos);
    setWindowTitle("设置声音成功");
}

void PlayerWindow::onRateChanged(){
    int m_rateIndex = ui->RateComboBox->currentIndex();
    switch (m_rateIndex)
    {
    case 0:
        m_vlc.SetRate(0.5);
        break;
    case 1:
        m_vlc.SetRate(1);
        break;
    case 2:
        m_vlc.SetRate(1.5);
        break;
    case 3:
        m_vlc.SetRate(2.0);
        break;
    default:
        break;
    }
    setWindowTitle("设置速率成功");
}
TimeMatrix::TimeMatrix(){
        hour_now = 0;
        min_now = 0;
        sec_now = 0;
        hour_tol = 0;
        min_tol = 0;
        sec_tol = 0;
    }

void TimeMatrix::SetTimePos(int pos){
        hour_now = pos / 3600;
        min_now = (pos - hour_now*3600)/60;
        sec_now = pos - hour_now*3600 - min_now*60;
    }
void TimeMatrix::SetTimeLen(int len){
        hour_tol = len / 3600;
        min_tol = (len - hour_tol*3600)/60;
        sec_tol = len - hour_tol*3600 - min_tol*60;
    }
QString TimeMatrix::GetTime(){
    QString time = QString("%1:%2:%3/%4:%5:%6").arg(hour_now,2,10,QLatin1Char('0')).arg(min_now,2,10,QLatin1Char('0')).arg(sec_now,2,10,QLatin1Char('0'))
        .arg(hour_tol,2,10,QLatin1Char('0')).arg(min_tol,2,10,QLatin1Char('0')).arg(sec_tol,2,10,QLatin1Char('0'));
        /*/qDebug() << "Debug输出：""现在的播放进度是" << hour_now << ":"
                 << min_now << ":"
                 << sec_now << "/"
                 << hour_tol << ":"
                 << min_tol << ":"
                 << sec_tol<< "\n";*/
        //qDebug() << "Debug输出：""现在的Time是" << time << "\n";
        return time;
    }
