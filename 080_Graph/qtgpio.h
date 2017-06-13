#ifndef QTGPIO_H
#define QTGPIO_H

//These includes are required
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "mmapGpio.h"

//QtGpio object derived from QWidget
class QtGpio : public QWidget
{
    Q_OBJECT     // Q_OBJECT macro is boilerplate. Must exist in all Qt applications

    public:
        explicit QtGpio(QWidget *parent = 0); // QtGpio constructor...must take on a parent parameter that defaults to NULL
        ~QtGpio(); // QtGpio destructor
    public slots: // Slot Methods
        void btnON(void);
        void btnOFF(void);
        void readInputPin(void);

    private:
        QPushButton *onBtn, *offBtn; // We need two Buttons
        QLabel *lblBtnState, *lblInputPinState; // two labels
        QVBoxLayout *vbox; // a vertical layout manager
        QTimer *timer; // a timer
        mmapGpio *rpiGpio; // a reference to the mmapGpio class to control the GPIO

};
#endif