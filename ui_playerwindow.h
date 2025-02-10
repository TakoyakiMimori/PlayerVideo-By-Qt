/********************************************************************************
** Form generated from reading UI file 'playerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERWINDOW_H
#define UI_PLAYERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerWindow
{
public:
    QSlider *VolumeSlider;
    QSlider *VedioSlider;
    QPushButton *PlayButton;
    QPushButton *StopButton;
    QLineEdit *PlayerUrl;
    QPushButton *PauseButton;
    QWidget *VideoWidget;
    QComboBox *RateComboBox;
    QLabel *label;
    QLabel *TimerEdit;

    void setupUi(QWidget *PlayerWindow)
    {
        if (PlayerWindow->objectName().isEmpty())
            PlayerWindow->setObjectName("PlayerWindow");
        PlayerWindow->resize(907, 584);
        VolumeSlider = new QSlider(PlayerWindow);
        VolumeSlider->setObjectName("VolumeSlider");
        VolumeSlider->setGeometry(QRect(870, 130, 16, 301));
        VolumeSlider->setOrientation(Qt::Orientation::Vertical);
        VedioSlider = new QSlider(PlayerWindow);
        VedioSlider->setObjectName("VedioSlider");
        VedioSlider->setGeometry(QRect(20, 480, 671, 16));
        VedioSlider->setOrientation(Qt::Orientation::Horizontal);
        PlayButton = new QPushButton(PlayerWindow);
        PlayButton->setObjectName("PlayButton");
        PlayButton->setGeometry(QRect(340, 520, 75, 24));
        StopButton = new QPushButton(PlayerWindow);
        StopButton->setObjectName("StopButton");
        StopButton->setGeometry(QRect(450, 520, 75, 24));
        PlayerUrl = new QLineEdit(PlayerWindow);
        PlayerUrl->setObjectName("PlayerUrl");
        PlayerUrl->setGeometry(QRect(190, 450, 651, 20));
        PauseButton = new QPushButton(PlayerWindow);
        PauseButton->setObjectName("PauseButton");
        PauseButton->setGeometry(QRect(230, 520, 75, 24));
        VideoWidget = new QWidget(PlayerWindow);
        VideoWidget->setObjectName("VideoWidget");
        VideoWidget->setGeometry(QRect(30, 20, 821, 411));
        RateComboBox = new QComboBox(PlayerWindow);
        RateComboBox->addItem(QString());
        RateComboBox->addItem(QString());
        RateComboBox->addItem(QString());
        RateComboBox->addItem(QString());
        RateComboBox->setObjectName("RateComboBox");
        RateComboBox->setGeometry(QRect(640, 520, 69, 22));
        label = new QLabel(PlayerWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 450, 91, 16));
        TimerEdit = new QLabel(PlayerWindow);
        TimerEdit->setObjectName("TimerEdit");
        TimerEdit->setGeometry(QRect(730, 480, 141, 20));

        retranslateUi(PlayerWindow);

        QMetaObject::connectSlotsByName(PlayerWindow);
    } // setupUi

    void retranslateUi(QWidget *PlayerWindow)
    {
        PlayerWindow->setWindowTitle(QCoreApplication::translate("PlayerWindow", "Form", nullptr));
        PlayButton->setText(QCoreApplication::translate("PlayerWindow", "Play", nullptr));
        StopButton->setText(QCoreApplication::translate("PlayerWindow", "Stop", nullptr));
        PauseButton->setText(QCoreApplication::translate("PlayerWindow", "Pause", nullptr));
        RateComboBox->setItemText(0, QCoreApplication::translate("PlayerWindow", "0.5x", nullptr));
        RateComboBox->setItemText(1, QCoreApplication::translate("PlayerWindow", "1.0x", nullptr));
        RateComboBox->setItemText(2, QCoreApplication::translate("PlayerWindow", "1.5x", nullptr));
        RateComboBox->setItemText(3, QCoreApplication::translate("PlayerWindow", "2.0x", nullptr));

        label->setText(QCoreApplication::translate("PlayerWindow", "\350\247\206\351\242\221\346\222\255\346\224\276\345\234\260\345\235\200", nullptr));
        TimerEdit->setText(QCoreApplication::translate("PlayerWindow", "00:00:00/00:00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerWindow: public Ui_PlayerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWINDOW_H
