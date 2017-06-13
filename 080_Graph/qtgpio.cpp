#include "qtgpio.h"
/****************************************************************************************
 * Constructor - The constructor of a class subclassed from QWidgets, must have a *parent
 *               parameter defaulting to NULL.
 *               In the constructor we usually do the following:
 *               1 - instatiate all controls/widgets/objects declared in the header file
 *               2 - add all widgets/controls to a layout manager
 *               3 - set the global layout manager as the window's layout
 *               4 - use 'connect' to connect signals to slot methods
 *               5 - Other initialization stuff
 ****************************************************************************************/
QtGpio::QtGpio(QWidget *parent): QWidget(parent)
{
    onBtn = new QPushButton("ON"); // instantiate buttons
    offBtn = new QPushButton("OFF");
    lblBtnState  = new QLabel("GPIO 4 OFF"); // instatiate labels
    lblInputPinState = new QLabel("Input pin value is : ?? ");
    vbox = new QVBoxLayout(); // instantiate layout manager
    timer = new QTimer(this); // instantiate timer....make timer child of the QtGpio class

    rpiGpio = new mmapGpio(); // instantiate mmapGpio object
    rpiGpio->setPinDir(4,mmapGpio::OUTPUT); // set pin direction for GPIO4 & 17
    rpiGpio->setPinDir(17,mmapGpio::INPUT);

    vbox->addWidget(lblInputPinState); // add all controls/widgets to layout manager
    vbox->addWidget(onBtn);
    vbox->addWidget(offBtn);
    vbox->addWidget(lblBtnState);

    this->setLayout(vbox); // set vbox as the window's (object's) layout manager
                           // this step also designates all controls (QPushButton, QLabel & QVBoxLayout) as children
                           // of the QtGpio class....
    this->setWindowTitle("GUI for GPIO Toggling");   // Set window title

    connect(timer, SIGNAL(timeout()), this, SLOT(readInputPin())); //connect timer's timeout() signal to the readInputPin() slot method

    connect(onBtn, SIGNAL(clicked()), this, SLOT(btnON()));//connect onBtn's clicked() signal to the btnON() slot method
    connect(offBtn, SIGNAL(clicked()),this, SLOT(btnOFF()));//connect offBtn's clicked() signal to the btnOFF() slot method

    timer->start(250); // start timer. The timeout() signal is emitted every 250ms....therefor readInputPin slot method() runs once every 250ms
}

/**********************************************************************************************
 * Destructor - Since all references to Qt based controls/widgets are 'parented' either through
 *              the layout manager or through pasing the  'this' pointer to their constructor
 *              we do not need to worry about deallocating their heap memory when they're done.
 *              We do however need to worry about the memory of the rpiGpio object which is not
 *              Qt based and not 'parented'
 * *******************************************************************************************/
QtGpio::~QtGpio(void){
    delete rpiGpio;
}

/********************************************************************************************
 * btnON() - slot method called whenever the onBtn button is pressed (see connect()
 *           call in constructor). It sets GPIO4 to high..turning on the LED as well
 *           as updating the text displayed by the lblBtnState label
 *******************************************************************************************/

void QtGpio::btnON(void){
    lblBtnState->setText("GPIO 4 ON");
    rpiGpio->writePinHigh(4);
}


/********************************************************************************************
 * btnOFF() - slot method called whenever the offBtn button is pressed (see connect()
 *           call in constructor). It clears GPIO4 to LOW..turning OFF the LED as well
 *           as updating the text displayed by the lblBtnState label
 *******************************************************************************************/
void QtGpio::btnOFF(void){
    lblBtnState->setText("GPIO 4 OFF");
    rpiGpio->writePinLow(4);
}


/**************************************************************************************************
 * readInputPin()  - slot method called once every 250ms (whenever the timeout() signal is emitted)
 *                   (see connect() nd timer->start() calls  in constructor). When called this
 *                   slot method reads the state of GPIO17 and updates the lblInputPinState label.
 **************************************************************************************************/
void QtGpio::readInputPin(void){
    unsigned int pinVal;
    pinVal = rpiGpio->readPin(17);
    if(pinVal == mmapGpio::HIGH)
        lblInputPinState->setText("GPIO17 is HIGH...PushButton not pressed");
    else
        lblInputPinState->setText("GPIO17 is LOW...PushButton pressed");
}