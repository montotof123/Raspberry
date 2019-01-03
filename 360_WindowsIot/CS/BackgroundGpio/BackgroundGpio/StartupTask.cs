using System;
using Windows.ApplicationModel.Background;
using Windows.Devices.Gpio;
using Windows.System.Threading;

// The Background Application template is documented at http://go.microsoft.com/fwlink/?LinkID=533884&clcid=0x409

namespace BackgroundGpio
{
    public sealed class StartupTask : IBackgroundTask
    {
        /// <summary>
        /// Variables de gestion du GPIO
        /// </summary>
        private GpioController _gpc;
        private GpioPin _red;
        private GpioPin _green;
        private GpioPin _sw1;
        private GpioPin _sw2;

        /// <summary>
        /// Timer de clignotement
        /// </summary>
        private ThreadPoolTimer timerRed;
        private ThreadPoolTimer timerGreen;

        /// <summary>
        /// Etat des LED
        /// </summary>
        private int etatLedVerte = 0;
        private bool clignVerte = false;

        private BackgroundTaskDeferral deferral;

        public void Run(IBackgroundTaskInstance taskInstance)
        {
            // 
            // TODO: Insert code to perform background work
            //
            // If you start any asynchronous methods here, prevent the task
            // from closing prematurely by using BackgroundTaskDeferral as
            // described in http://aka.ms/backgroundtaskdeferral
            //

            // Initialisation GPIO
            _gpc = GpioController.GetDefault();

            // LED rouge
            _red = _gpc.OpenPin(27);
            _red.SetDriveMode(GpioPinDriveMode.Output);

            // LED verte
            _green = _gpc.OpenPin(17);
            _green.SetDriveMode(GpioPinDriveMode.Output);

            // Bouton 1 avec résistance PullDown et anti rebond 10ms
            _sw1 = _gpc.OpenPin(12);
            _sw1.SetDriveMode(GpioPinDriveMode.InputPullDown);
            _sw1.DebounceTimeout = new TimeSpan(0, 0, 0, 0, 10);
            _sw1.ValueChanged += _sw1_ValueChanged;

            // Bouton 2 avec résistance PullUp et anti rebond 10ms
            _sw2 = _gpc.OpenPin(16);
            _sw2.SetDriveMode(GpioPinDriveMode.InputPullUp);
            _sw2.DebounceTimeout = new TimeSpan(0, 0, 0, 0, 10);
            _sw2.ValueChanged += _sw2_ValueChanged;

            // Préparation des timer
            timerRed = ThreadPoolTimer.CreatePeriodicTimer(this.TimerRed_Tick, TimeSpan.FromMilliseconds(15000));
            timerGreen = ThreadPoolTimer.CreatePeriodicTimer(this.TimerGreen_Tick, TimeSpan.FromMilliseconds(200));

            // Mise en tache de fond
            deferral = taskInstance.GetDeferral();
        }

        /// <summary>
        /// Appelé par le timer vert
        /// Change la valeur de la LED verte pour la faire clignoter si c'est possible
        /// </summary>
        /// <param name="timer"></param>
        private void TimerGreen_Tick(ThreadPoolTimer timer)
        {
            if (clignVerte)
            {
                if (_green.Read() == GpioPinValue.Low)
                {
                    _green.Write(GpioPinValue.High);
                }
                else
                {
                    _green.Write(GpioPinValue.Low);
                }
            }
        }

        /// <summary>
        /// Appelé par le timer rouge
        /// Change la valeur de la LED rouge pour la faire clignoter
        /// </summary>
        /// <param name="timer"></param>
        private void TimerRed_Tick(ThreadPoolTimer timer)
        {
            if (_red.Read() == GpioPinValue.Low)
            {
                _red.Write(GpioPinValue.High);
            }
            else
            {
                _red.Write(GpioPinValue.Low);
            }
        }

        /// <summary>
        /// Changement d'état de SW2
        /// Fait passer la led verte allumé -> éteint -> clignote -> allumé
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        private void _sw2_ValueChanged(GpioPin sender, GpioPinValueChangedEventArgs args)
        {
            switch (etatLedVerte)
            {
                case 0:
                    clignVerte = false;
                    _green.Write(GpioPinValue.High);
                    etatLedVerte = 2;
                    break;
                case 1:
                    clignVerte = true;
                    etatLedVerte = 0;
                    break;
                case 2:
                    clignVerte = false;
                    _green.Write(GpioPinValue.Low);
                    etatLedVerte = 1;
                    break;
            }
        }

        /// <summary>
        /// Changement d'état de SW1
        /// Fait passer la led verte allumé -> clignote -> éteint -> allumé
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        private void _sw1_ValueChanged(GpioPin sender, GpioPinValueChangedEventArgs args)
        {
            switch (etatLedVerte)
            {
                case 0:
                    clignVerte = false;
                    _green.Write(GpioPinValue.High);
                    etatLedVerte = 1;
                    break;
                case 1:
                    clignVerte = true;
                    etatLedVerte = 2;
                    break;
                case 2:
                    clignVerte = false;
                    _green.Write(GpioPinValue.Low);
                    etatLedVerte = 0;
                    break;
            }
        }
    }
}
