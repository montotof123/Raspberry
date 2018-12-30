using System;
using System.Diagnostics;
using Windows.Devices.Gpio;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

// Pour plus d'informations sur le modèle d'élément Page vierge, consultez la page https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace GestMontageComplet
{
    /// <summary>
    /// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        /// <summary>
        /// Initialisation de la page
        /// </summary>
        public MainPage()
        {
            this.InitializeComponent();
        }

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
        private DispatcherTimer timerRed;
        private DispatcherTimer timerGreen;
        private DispatcherTimer timerRedGreen;

        /// <summary>
        /// Exécuté au chargement de la page
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
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
            timerRed = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(200)
            };
            timerRed.Tick += TimerRed_Tick;
            timerGreen = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(400)
            };
            timerGreen.Tick += TimerGreen_Tick;
            timerRedGreen = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(600)
            };
            timerRedGreen.Tick += TimerRedGreen_Tick;
        }

        /// <summary>
        /// Appelé par le timer rouge
        /// Change la valeur de la LED rouge
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TimerRed_Tick(object sender, object e)
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
        /// Appelé par le timer vert
        /// Change la valeur de la LED verte
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TimerGreen_Tick(object sender, object e)
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

        /// <summary>
        /// Appelé par le timer rouge/vert
        /// Change les valeurs des LED rouge et verte
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TimerRedGreen_Tick(object sender, object e)
        {
            if (_green.Read() == GpioPinValue.Low)
            {
                _green.Write(GpioPinValue.High);
                _red.Write(GpioPinValue.Low);
            }
            else
            {
                _green.Write(GpioPinValue.Low);
                _red.Write(GpioPinValue.High);
            }
        }

        /// <summary>
        /// Changement d'état de SW1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        private void _sw1_ValueChanged(GpioPin sender, GpioPinValueChangedEventArgs args)
        {
            // A mettre en asynchrone, sinon ça plante le programme
            var task = Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
            {
                timerGreen.Stop();
                timerRedGreen.Stop();
                timerRed.Stop();
            });
            _red.Write(GpioPinValue.High);
            _green.Write(GpioPinValue.Low);
            Debug.WriteLine(DateTime.Now.Ticks.ToString() + " _sw1_ValueChanged");
         }

        /// <summary>
        /// Changement d'état de SW2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        private void _sw2_ValueChanged(GpioPin sender, GpioPinValueChangedEventArgs args)
        {
            // A mettre en asynchrone, sinon ça plante le programme
            var task = Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
            {
                timerGreen.Stop();
                timerRedGreen.Stop();
                timerRed.Stop();
            });
            _red.Write(GpioPinValue.Low);
            _green.Write(GpioPinValue.High);
            Debug.WriteLine(DateTime.Now.Ticks.ToString() + " _sw2_ValueChanged");
        }

        /// <summary>
        /// Clic sur le bouton On Red
        /// Allume la LED rouge
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnRedBTN_Click(object sender, RoutedEventArgs e)
        {
            timerGreen.Stop();
            timerRedGreen.Stop();
            timerRed.Stop();
             _red.Write(GpioPinValue.High);
            Debug.WriteLine(DateTime.Now.Ticks.ToString() + " OnRedBTN_Click");
        }

        /// <summary>
        /// Clic sur le bouton Off Red
        /// Eteint la LED rouge
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OffRedBTN_Click(object sender, RoutedEventArgs e)
        {
            timerGreen.Stop();
            timerRedGreen.Stop();
            timerRed.Stop();
            _red.Write(GpioPinValue.Low);
            Debug.WriteLine(DateTime.Now.Ticks.ToString() + " OffRedBTN_Click");
        }

        /// <summary>
        /// Clic sur le bouton On Green
        /// Allume la LED verte
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnGreenBTN_Click(object sender, RoutedEventArgs e)
        {
            timerGreen.Stop();
            timerRedGreen.Stop();
            timerRed.Stop();
            _green.Write(GpioPinValue.High);
            Debug.WriteLine(DateTime.Now.Ticks.ToString() + " OnGreenBTN_Click");
        }

        /// <summary>
        /// Clic sur le bouton Off Green
        /// Eteint la LED verte
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OffGreenBTN_Click(object sender, RoutedEventArgs e)
        {
            timerGreen.Stop();
            timerRedGreen.Stop();
            timerRed.Stop();
            _green.Write(GpioPinValue.Low);
            Debug.WriteLine(DateTime.Now.Ticks.ToString() + " OffGreenBTN_Click");
        }

        /// <summary>
        /// Clic sur le bouton Clign Red
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ClignRedBTN_Click(object sender, RoutedEventArgs e)
        {
            timerGreen.Stop();
            timerRedGreen.Stop();
            timerRed.Start();
            Debug.WriteLine(DateTime.Now.Ticks.ToString() + " ClignRedBTN_Click");
        }

        /// <summary>
        /// Clic sur le bouton Clign Green
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ClignGreenBTN_Click(object sender, RoutedEventArgs e)
        {
            timerRedGreen.Stop();
            timerRed.Stop();
            timerGreen.Start();
             Debug.WriteLine(DateTime.Now.Ticks.ToString() + " ClignGreenBTN_Click");
        }

        /// <summary>
        /// Clic sur le bouton Clign Red Green
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ClignRedGreenBTN_Click(object sender, RoutedEventArgs e)
        {
            timerGreen.Stop();
            timerRed.Stop();
            timerRedGreen.Start();
            Debug.WriteLine(DateTime.Now.Ticks.ToString() + " ClignRedGreenBTN_Click");
        }

        /// <summary>
        /// Déchargement de la page
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Page_Unloaded(object sender, RoutedEventArgs e)
        {
            // Arrêt timer
            timerGreen.Stop();
            timerGreen = null;
            timerRed.Stop();
            timerRed = null;
            timerRedGreen.Stop();
            timerRedGreen = null;

            // Désactive les broches
            _red.Dispose();
            _red = null;
            _green.Dispose(); ;
            _green = null;
            _sw1.Dispose(); ;
            _sw1 = null;
            _sw2.Dispose(); ;
            _sw2 = null;
        }
    }
}
