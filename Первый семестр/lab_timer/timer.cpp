/**
    timer.cpp
    Purpose: Timer Class. Starts QTimer of timer by start-button pressing.
    Loads timer state when QTimer starts. Saves timer state on application quit

    @author Denis Aksoy
    @version 1.0 29/11/18
*/

#include "timer.h"

#include <QSound>
#include <QSettings>

// Timer class constructor
Timer::Timer(QGridLayout *saglTimers, int row, QTime time,
 std::string savedValue, std::string savedTime, QObject *parent)
 : QObject(parent), savedValue(savedValue), savedTime(savedTime), time(time)
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    pbDisable = new QPushButton("X");
    pbEnable = new QPushButton(">");
    lName = new QLabel("Таймер " + time.toString());
    lState = new QLabel("Выкл.");
    saglTimers->addWidget(pbDisable, row, COL_PB_DISABLE);
    saglTimers->addWidget(pbEnable, row, COL_PB_ENABLE);
    saglTimers->addWidget(lName, row, COL_LABEL_NAME);
    saglTimers->addWidget(lState, row, COL_LABEL_STATE);

    tTimer = new QTimer();
    tTick = new QTimer();
    tTick->setInterval(LABEL_UPDATE_INTERVAL);
    connect(tTick, SIGNAL(timeout()), this, SLOT(update()));
    connect(tTimer, SIGNAL(timeout()), this, SLOT(complete()));
    connect(pbDisable, SIGNAL(clicked()), this, SLOT(disable()));
    connect(pbEnable, SIGNAL(clicked()), this, SLOT(enable()));
}

// Timer class destructor
Timer::~Timer() {
    delete tTimer;
    delete tTick;
}

// Slot function updating label with timer state
void Timer::update() {
    int hours = tTimer->remainingTime() / MSECS_HOUR;
    int minutes = (tTimer->remainingTime() - (hours * MSECS_HOUR)) / MSECS_MIN;
    int seconds = (
     tTimer->remainingTime() - (hours * MSECS_HOUR) - (minutes * MSECS_MIN)
    ) / MSECS_SEC;
    QTime remainingTime(hours, minutes, seconds, 0);

    if (tTimer->isActive()) {
        lState->setText(remainingTime.toString());
    }
}

// Slot function for enable timer
void Timer::enable() {
    QTime timeZero(0, 0, 0, 0);
    int interval = timeZero.msecsTo(time);

    tTimer->setInterval(interval);
    tTimer->start();
    tTick->start();
    update();
}

// Slot function for disable timer
void Timer::disable() {
    tTimer->stop();
    tTick->stop();
    lState->setText("Выкл.");
}

// Slot function for finish timer
void Timer::complete() {
    disable();
    QSound::play("sound.wav");
}

// Slot function for save alarm state to config
void Timer::saveValue() {
    QSettings settings("settings.ini", QSettings::IniFormat);

    if (tTimer->isActive())
        settings.setValue(savedValue.c_str(), tTimer->remainingTime());
    else
        settings.setValue(savedValue.c_str(),
         time.hour() * MSECS_HOUR + time.minute() * MSECS_MIN + time.second() *
          MSECS_SEC);

    settings.setValue(savedTime.c_str(),
     time.hour() * MSECS_HOUR + time.minute() * MSECS_MIN + time.second() *
      MSECS_SEC);
}
