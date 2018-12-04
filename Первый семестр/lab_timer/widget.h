/**
    widget.h
    Purpose: Main form header

    @author Denis Aksoy
    @version 1.0 29/11/18
*/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QApplication>
#include <QGridLayout>

#include "timer_item.h"
#include "timer.h"
#include "alarm.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    const int MSECS_HOUR = 3600000;
    const int MSECS_MIN = 60000;
    const int MSECS_SEC = 1000;
    const int SETTINGS_NO_ENTRY = -1;
    /**
        Main form constructor

        @param application pointer to QApplication
        @param parent must be nullptr
    */
    explicit Widget(QApplication *application, QWidget *parent = nullptr);
    /**
        Main form destructor
    */
    ~Widget();

private:
    const int MORNING_INITIAL_HOURS = 7;
    const int MORNING_INITIAL_MINS = 15;
    const int MORNING_INITIAL_SECS = 0;
    const int DINNER_INITIAL_HOURS = 14;
    const int DINNER_INITIAL_MINS = 0;
    const int DINNER_INITIAL_SECS = 0;
    const int EVENING_INITIAL_HOURS = 18;
    const int EVENING_INITIAL_MINS = 0;
    const int EVENING_INITIAL_SECS = 0;
    const int TIMER_5S_MILLISECONDS = 5000;
    const int TIMER_20S_MILLISECONDS = 20000;
    const int TIMER_60S_MILLISECONDS = 60000;

    Ui::Widget *ui;
    QApplication *application;
    QTimer *tCurrentTime;

    Alarm *alarmMorning;
    Alarm *alarmDinner;
    Alarm *alarmEvening;

    Timer *timer5s;
    Timer *timer20s;
    Timer *timer60s;

    QGridLayout *saglTimers;
    QWidget* sawTimers;

    std::vector<QObject *> timerItems;

private slots:
    /**
        Slot for updating label displaying current time
    */
    void updateCurrentTime();
    /**
        Slot for add alarm
    */
    void addAlarm();
    /**
        Slot for add timer
    */
    void addTimer();
};

#endif // WIDGET_H
