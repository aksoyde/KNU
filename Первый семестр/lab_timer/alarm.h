/**
    alarm.h
    Purpose: Alarm class header

    @author Denis Aksoy
    @version 1.0 29/11/18
*/

#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTime>

#include "timer_item.h"

class Alarm : public QObject, public TimerItem
{
    Q_OBJECT
    Q_INTERFACES(TimerItem)

private:
    const int LABEL_UPDATE_INTERVAL = 1000;
    const int ALARM_DISABLED = 0;
    const int ALARM_ENABLED = 1;
    const int TICK_MILLISECONDS = 1000;
    const int DAY_INTERVAL = 86400000;
    const int COL_PB_DISABLE = 1;
    const int COL_PB_ENABLE = 2;
    const int COL_LABEL_NAME = 3;
    const int COL_LABEL_STATE = 4;
    const int SETTINGS_NO_ENTRY = -1;
    const int MSECS_HOUR = 3600000;
    const int MSECS_MIN = 60000;
    const int MSECS_SEC = 1000;

    QGridLayout *saglTimers;
    QTimer      *tTimer;
    QTimer      *tTick;
    QPushButton *pbDelete;
    QPushButton *pbDisable;
    QPushButton *pbEnable;
    QLabel      *lName;
    QLabel      *lState;
    QTime        time;
    std::string savedValue;

public:
    /**
        Alarm class constructor

        @param pbEnable pointer to push putton for starting timer
        @param label pointer to label displaying timer state
        @param hours hours value when to alarm
        @param mins mins value when to alarm
        @param secs secs value when to alarm
        @savedValue section and key name in configfile for saveing/loading timer
        state
        @parent must be nullptr
    */
    explicit Alarm(QGridLayout *saglTimers, int row, QTime time,
     std::string savedValue, QObject *parent = nullptr);
    /**
        Alarm class destructor
    */
    ~Alarm();

// signals:

public slots:
    /**
        Slot function updating label with timer state
    */
    void update();
    /**
        Slot function for enable alarm
    */
    void enable();
    /**
        Slot function for disable alarm
    */
    void disable();
    /**
        Slot function for finish alarm
    */
    void complete();
    /**
        Slot function for save data to config
    */
    void saveValue();
};

#endif // ALARM_H
