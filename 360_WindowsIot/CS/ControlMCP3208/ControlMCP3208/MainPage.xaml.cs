using System;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.Spi;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

// Pour plus d'informations sur le modèle d'élément Page vierge, consultez la page https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace ControlMCP3208
{
    /// <summary>
    /// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private SpiDevice SpiADC;
        private DispatcherTimer timerMesure;

        /// <summary>
        /// Page principale, initialisations
        /// </summary>
        public MainPage()
        {
            this.InitializeComponent();
            InitAll();
        }

        /// <summary>
        /// Initialisation SPI avec message si ok
        /// </summary>
        private async void InitAll()
        {
            await InitSPI();
            Initialisation.Text = "Initialisation OK";
        }

        /// <summary>
        /// Initialisation du SPI et du MCP3208
        /// </summary>
        /// <returns></returns>
        private async Task InitSPI()
        {
            try
            {
                var settings = new SpiConnectionSettings(0);
                settings.ClockFrequency = 500000;   // Horloge 0.5MHz
                settings.Mode = SpiMode.Mode0;      // Mode0 compatible avec le MCP3208

                string spiAqs = SpiDevice.GetDeviceSelector("SPI0");
                var deviceInfo = await DeviceInformation.FindAllAsync(spiAqs); // Recherche du module sur le SPI0
                SpiADC = await SpiDevice.FromIdAsync(deviceInfo[0].Id, settings); // MCP3208
            }
            catch (Exception ex)
            {
                throw new Exception("Erreur initialisation SPI", ex);
            }
        }

        /// <summary>
        /// Conversion des 3 octets reçus du MCP3208 en valeur entière
        /// http://ww1.microchip.com/downloads/en/DeviceDoc/21298e.pdf page 22
        /// </summary>
        /// <param name="data"></param>
        /// <returns> La valeur entière </returns>
        public int convertToIntMCP3208(byte[] data)
        {
            int result = data[1] & 0x0F;
            result <<= 8;
            result += data[2];
            return result;
        }

        /// <summary>
        /// Arrêt de la page, remise à disposition du SPI
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Page_Unloaded(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            if (SpiADC != null)
            {
                SpiADC.Dispose();
            }
        }

        /// <summary>
        /// Lecture du MCP3208 canal0
        /// </summary>
        /// <returns> La valeur lue </returns>
        private int ReadFast()
        {
            byte[] readBuffer = new byte[3]; // Buffer de lecture
            // 00000110 00000000 00000000 configuration mode single canal 0
            // http://ww1.microchip.com/downloads/en/DeviceDoc/21298e.pdf page 19 et 21
            byte[] writeBuffer = new byte[] { 0x06, 0x00, 0x00 }; 
            SpiADC.TransferFullDuplex(writeBuffer, readBuffer); // Lecture MCP3208
            return convertToIntMCP3208(readBuffer); // Conversion des octets reçu en entier
         }

        /// <summary>
        /// Chargement de la page, création et démarrage timer
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Page_Loaded(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            timerMesure = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(200)
            };
            timerMesure.Tick += TimerMesure_Tick;
            timerMesure.Start();

        }

        /// <summary>
        /// Lecture de la valeur du MCP3208 par le timer
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TimerMesure_Tick(object sender, object e)
        {
            Valeur.Text = ReadFast().ToString();
        }
    }
}
