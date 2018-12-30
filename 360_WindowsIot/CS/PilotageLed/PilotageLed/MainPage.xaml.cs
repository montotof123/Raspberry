using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Devices.Gpio;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// Pour plus d'informations sur le modèle d'élément Page vierge, consultez la page https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace PilotageLed
{
    /// <summary>
    /// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        // Les GPIO
        private GpioController _gpc;
        private GpioPin _red;
        private GpioPin _green;

        // Au chargement de la page
        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            // Initialisation des GPIO 
            _gpc = GpioController.GetDefault();

            // LED rouge
            _red = _gpc.OpenPin(27);
            _red.SetDriveMode(GpioPinDriveMode.Output);

            // LED verte
            _green = _gpc.OpenPin(17);
            _green.SetDriveMode(GpioPinDriveMode.Output);
        }

        private void OnBTN_Click(object sender, RoutedEventArgs e)
        {
            _red.Write(GpioPinValue.High);
        }

        private void OffBTN_Click(object sender, RoutedEventArgs e)
        {
            _red.Write(GpioPinValue.Low);
        }
    }
}

