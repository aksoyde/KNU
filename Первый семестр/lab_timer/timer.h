/**
    timer.h
    Purpose: Timer class header

    @author Denis Aksoy
    @version 1.0 29/11/18
*/

#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTime>

#include "timer_item.h"

class Timer: public QObject, public TimerItem
{
    Q_OBJECT
    Q_INTERFACES(TimerItem)

private:
    const int LABEL_UPDATE_INTERVAL = 1000;
    const int TICK_MILLISECONDS = 1000;
    const int COL_PB_DISABLE = 1;
    const int COL_PB_ENABLE = 2;
    const int COL_LABEL_NAME = 3;
    const int COL_LABEL_STATE = 4;
    const int SETTINGS_NO_ENTRY = -1;
    const int MSECS_HOUR = 3600000;
    const int MSECS_MIN = 60000;
    const int MSECS_SEC = 1000;

    QGridLayout *saglTimers;
    QTimer      *tTick;
    QPushButton *pbDelete;
    QPushButton *pbDisable;
    QPushButton *pbEnable;
    QLabel      *lName;
    QLabel      *lState;
    std::string  savedValue;
    std::string  savedTime;

public:
    QTime        time;
    QTimer      *tTimer;
    /**
        Timer class constructor

        @param pbEnable pointer to push putton for starting timer
        @param label pointer to label displaying timer state
        @param interval timer interval in miliseconds
        @savedValue section and key name in configfile for saveing/loading timer
        state
        @parent must be nullptr
    */
    explicit Timer(QGridLayout *saglTimers, int row, QTime time,
     std::string savedValue, std::string savedTime, QObject *parent = nullptr);
    /**
        Timer class destructor
    */
    ~Timer();

public slots:
    /**
        Slot function updating label with timer state
    */
    void update();
    /**
        Slot function for enable timer
    */
    void enable();
    /**
        Slot function for disable timer
    */
    void disable();
    /**
        Slot function for finish timer
    */
    void complete();
    /**
        Slot function for save data to config
    */
    void saveValue();
};

#endif // TIMER_H
