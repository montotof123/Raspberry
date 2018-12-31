using System;
using Windows.Devices.Enumeration;
using Windows.Devices.I2c;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;


// Pour plus d'informations sur le modèle d'élément Page vierge, consultez la page https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace ControlPCF8591
{
    /// <summary>
    /// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        /// <summary>
        /// Adresse I2C du convertisseur
        /// </summary>
        private const byte I2C_ADDR_PCF8591 = 0x48;

        /// <summary>
        /// Commande pour une conversion D/A
        /// </summary>
        private const byte ConvDA = 0x40;
        /// <summary>
        /// Commande pour une conversion A/D sur l'entrée 0 avec maintient de la tension du convertisseur D/A sur AOUT
        /// </summary>
        private const byte ConvAIN0 = 0x40;
        /// <summary>
        /// Commande pour une conversion A/D sur l'entrée 1 avec maintient de la tension du convertisseur D/A sur AOUT
        /// </summary>
        private const byte ConvAIN1 = 0x41;
        /// <summary>
        /// Commande pour une conversion A/D sur l'entrée 2 avec maintient de la tension du convertisseur D/A sur AOUT
        /// </summary>
        private const byte ConvAIN2 = 0x42;
        /// <summary>
        /// Commande pour une conversion A/D sur l'entrée 3 avec maintient de la tension du convertisseur D/A sur AOUT
        /// </summary>
        private const byte ConvAIN3 = 0x43;

        /// <summary>
        /// Module PCF8591
        /// </summary>
        I2cDevice i2cPCF8591 = null;

        /// <summary>
        /// Recherche des modules I2C puis activation du module PCF8591
        /// Doit être fait dans un module asynchrone pour attendre l'initialisation des modules
        /// </summary>
        private async void InitI2C()
        {
            string deviceSelector = I2cDevice.GetDeviceSelector();
            var i2cDeviceControllers = await DeviceInformation.FindAllAsync(deviceSelector);
            if (i2cDeviceControllers.Count == 0)
            {
                InformationI2C.Text = "Aucun périphérique I2C détecté";
                return;
            }
            var i2cSettings = new I2cConnectionSettings(I2C_ADDR_PCF8591);
            i2cPCF8591 = await I2cDevice.FromIdAsync(i2cDeviceControllers[0].Id, i2cSettings);
            if (i2cPCF8591 == null)
            {
                InformationI2C.Text = "PCF8591 non détecté";
                return;
            }
            InformationI2C.Text = "PCF8591 détecté";
        }

        /// <summary>
        /// Initialisation de la page et de l'I2C
        /// </summary>
        public MainPage()
        {
            this.InitializeComponent();
            InitI2C();
        }

        /// <summary>
        /// Récupération de la valeur du slider pour programmer l'interface D/A
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Slider_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            i2cPCF8591.Write(new byte[] { ConvDA, (byte)e.NewValue });
        }

        /// <summary>
        /// Lecture d'une interface A/D en fonction de la sélection du bouton radio
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AIN_Check(object sender, RoutedEventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            // Il faut lire deux octets car le module envoie en premier la mesure précédente 
            //  avant de faire une nouvelle mesure et de l'envoyer.
            // On a donc la conversion précédente dans le byte[0] et la bonne mesure dans le byte[1]
            // Voir page 8 du datasheet https://www.nxp.com/docs/en/data-sheet/PCF8591.pdf
            byte[] i2CReadPCF8591 = new byte[2];
            switch (rb.Name)
            {
                case "AIN0":
                    i2cPCF8591.WriteRead(new byte[] { ConvAIN0 }, i2CReadPCF8591);
                    break;
                case "AIN1":
                    i2cPCF8591.WriteRead(new byte[] { ConvAIN1 }, i2CReadPCF8591);
                    break;
                case "AIN2":
                    i2cPCF8591.WriteRead(new byte[] { ConvAIN2 }, i2CReadPCF8591);
                    break;
                case "AIN3":
                    i2cPCF8591.WriteRead(new byte[] { ConvAIN3 }, i2CReadPCF8591);
                    break;
            }
            ValeurAIN.Text = i2CReadPCF8591[1].ToString();
        }
    }
}
