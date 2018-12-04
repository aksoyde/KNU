/**
    CS-?? Asn ?
    widget.cpp
    Purpose: Main form

    @author Denis Aksoy
    @version 1.0 29/11/18
*/

#include <QTime>
#include <QSettings>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QApplication *application, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    application(application)
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    ui->setupUi(this);

    tCurrentTime = new QTimer();
    tCurrentTime->setInterval(1000);
    connect(tCurrentTime, SIGNAL(timeout()), this, SLOT(updateCurrentTime()));
    tCurrentTime->start();

    connect(tCurrentTime, SIGNAL(timeout()), this, SLOT(updateCurrentTime()));

    saglTimers = new QGridLayout();
    sawTimers = new QWidget();
    sawTimers->setLayout(saglTimers);
    ui->saTimers->setWidget(sawTimers);
    saglTimers->setSpacing(10);
    saglTimers->setAlignment(Qt::AlignTop);

    connect(ui->pbAddAlarm, SIGNAL(clicked()), this, SLOT(addAlarm()));
    connect(ui->pbAddTimer, SIGNAL(clicked()), this, SLOT(addTimer()));

    int i = 0;

    while (
     (
      settings.value("alarm/" + QString::number(i),
      SETTINGS_NO_ENTRY) != SETTINGS_NO_ENTRY
     ) ||
     (
      settings.value("timer/" + QString::number(i),
      SETTINGS_NO_ENTRY) != SETTINGS_NO_ENTRY
     )
    ) {
        int alarmValue = settings.value(
         "alarm/" + QString::number(i), SETTINGS_NO_ENTRY
        ).toInt();
        int timerValue = settings.value(
         "timer/" + QString::number(i), SETTINGS_NO_ENTRY
        ).toInt();
        int timerTime = settings.value(
         "timer_time/" + QString::number(i), SETTINGS_NO_ENTRY
        ).toInt();

        if (alarmValue != SETTINGS_NO_ENTRY) {
            int hours = alarmValue / MSECS_HOUR;
            int minutes = (alarmValue - (hours * MSECS_HOUR)) / MSECS_MIN;
            int seconds = (
             alarmValue - (hours * MSECS_HOUR) - (minutes * MSECS_MIN)
            ) / MSECS_SEC;
            QObject *alarm = new Alarm(saglTimers,
             static_cast<int>(timerItems.size()),
             QTime(hours, minutes, seconds, 0),
             "alarm/" + std::to_string(timerItems.size()));

            timerItems.push_back(alarm);

            connect(application, SIGNAL(aboutToQuit()), alarm,
             SLOT(saveValue()));
            connect(ui->pbAlarms, SIGNAL(clicked()), alarm, SLOT(enable()));
        } else {
            int hours = timerTime / MSECS_HOUR;
            int minutes = (timerTime - (hours * MSECS_HOUR)) / MSECS_MIN;
            int seconds = (
             timerTime - (hours * MSECS_HOUR) - (minutes * MSECS_MIN)
            ) / MSECS_SEC;
            QObject *timer = new Timer(saglTimers,
             static_cast<int>(timerItems.size()),
             QTime(hours, minutes, seconds, 0),
             "timer/" + std::to_string(timerItems.size()),
             "timer_time/" + std::to_string(timerItems.size()));

            if (timerValue != timerTime) {

                hours = timerValue / MSECS_HOUR;
                minutes = (timerValue - (hours * MSECS_HOUR)) / MSECS_MIN;
                seconds = (timerValue - (hours * MSECS_HOUR) - (
                 minutes * MSECS_MIN)
                ) / MSECS_SEC;

                dynamic_cast<Timer *>(timer)->time = QTime(hours, minutes,
                 seconds, 0);
                dynamic_cast<Timer *>(timer)->enable();
            }

            timerItems.push_back(timer);

            connect(application, SIGNAL(aboutToQuit()), timer,
             SLOT(saveValue()));
            connect(ui->pbTimers, SIGNAL(clicked()), timer, SLOT(enable()));
        }

        i++;
    }
}

Widget::~Widget() {
    delete ui;
    delete tCurrentTime;
}

// Slot for updating label displaying current time
void Widget::updateCurrentTime() {
    ui->lCurrentTime->setText(
     "Текущее время: " + QTime::currentTime().toString());
}

// Slot for add alarm
void Widget::addAlarm() {
    QObject *alarm = new Alarm(saglTimers,
     static_cast<int>(timerItems.size()), ui->timeEdit->time(),
     "alarm/" + std::to_string(timerItems.size()));

    timerItems.push_back(alarm);

    connect(application, SIGNAL(aboutToQuit()), alarm, SLOT(saveValue()));
    connect(ui->pbAlarms, SIGNAL(clicked()), alarm, SLOT(enable()));
}

// Slot for add timer
void Widget::addTimer() {
    QObject *timer = new Timer(saglTimers,
     static_cast<int>(timerItems.size()), ui->timeEdit->time(),
     "timer/" + std::to_string(timerItems.size()),
     "timer_time/" + std::to_string(timerItems.size()));

    timerItems.push_back(timer);

    connect(application, SIGNAL(aboutToQuit()), timer, SLOT(saveValue()));
    connect(ui->pbTimers, SIGNAL(clicked()), timer, SLOT(enable()));
}

