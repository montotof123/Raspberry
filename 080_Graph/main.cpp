#include <QApplication>
#include "qtgpio.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); //instantiate object responsible for Qt's event loop
    QtGpio window; // instantiate a QtGpio object
    window.show(); // show it
    return app.exec();// start the Event loop
}