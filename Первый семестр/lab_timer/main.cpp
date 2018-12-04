/**
    main.cpp
    Purpose: Creates and run application. Show main form

    @author Denis Aksoy
    @version 1.0 29/11/18
*/

#include "widget.h"
#include <QApplication>

// Entry point function of the application
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w(&a);
    w.show();

    return a.exec();
}
