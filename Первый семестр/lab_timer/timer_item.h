/**
    timer_item.h
    Purpose: Interface for Timer and Alarm classes header

    @author Denis Aksoy
    @version 1.0 29/11/18
*/

#ifndef TIMER_ITEM_H
#define TIMER_ITEM_H

#include <QObject>

class TimerItem
{
public:
    /**
        Virtual destructor of TimerItem interface
    */
    virtual ~TimerItem() = 0;
    /**
        Slot function updating label with timer state
    */
    virtual void update() = 0;
    /**
        Slot function for enable timer or alarm
    */
    virtual void enable() = 0;
    /**
        Slot function for disable timer or alarm
    */
    virtual void disable() = 0;
    /**
        Slot function for finish timer or alarm
    */
    virtual void complete() = 0;
    /**
        Slot function for save data to config
    */
    virtual void saveValue() = 0;
};

Q_DECLARE_INTERFACE(TimerItem, "TimerItem")

#endif // TIMER_ITEM_H
