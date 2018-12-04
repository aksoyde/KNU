/**
    alarm.cpp
    Purpose: Alarm Class. Starts timer of alarm by start-button pressing.
    Loads alarm state when timer starts. Saves alarm state on application quit

    @author Denis Aksoy
    @version 1.0 29/11/18
*/

#include "alarm.h"

#include <QTimer>
#include <QTime>
#include <QSound>
#include <QSettings>
#include <QScrollArea>
#include <QGridLayout>

// Alarm class constructor
Alarm::Alarm(QGridLayout *saglTimers, int row, QTime time,
 std::string savedValue, QObject *parent)
    : QObject(parent), time(time), savedValue(savedValue)
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    pbDisable = new QPushButton("X");
    pbEnable = new QPushButton(">");
    lName = new QLabel("Будильник " + time.toString());
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

    if (
     settings.value(savedValue.c_str(), SETTINGS_NO_ENTRY) != SETTINGS_NO_ENTRY
    ) {
        enable();
    }
}

// Alarm class destructor
Alarm::~Alarm() {
    delete tTimer;
    delete tTick;
}

// Slot function updating label with alarm state
void Alarm::update() {
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

// Slot function for enable alarm
void Alarm::enable() {
    int interval = QTime::currentTime().msecsTo(time);
    if (interval <= 0) {
        interval += DAY_INTERVAL;
    }

    tTimer->setInterval(interval);
    tTimer->start();
    tTick->start();
    update();
}

// Slot function for disable alarm
void Alarm::disable() {
    lState->setText("Выкл");
    tTimer->stop();
    tTick->stop();
}

// Slot function for finish alarm
void Alarm::complete() {
    disable();
    QSound::play("sound.wav");
}

// Slot function for save alarm data to config
void Alarm::saveValue() {
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue(savedValue.c_str(),
     time.hour() * MSECS_HOUR + time.minute() * MSECS_MIN + time.second() *
      MSECS_SEC);
}
