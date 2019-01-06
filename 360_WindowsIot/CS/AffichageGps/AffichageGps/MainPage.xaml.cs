using AffichageGps.parseNMEA;
using System;
using System.Threading;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

// Pour plus d'informations sur le modèle d'élément Page vierge, consultez la page https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace AffichageGps
{
    /// <summary>
    /// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        /// <summary>
        /// Port série
        /// </summary>
        private SerialDevice UartPort;

        /// <summary>
        /// Reader port série
        /// </summary>
        private DataReader DataReaderObject = null;

        /// <summary>
        /// Writer port série
        /// </summary>
        private DataWriter DataWriterObject;

        /// <summary>
        /// Un token pour la lecture sur le port série
        /// </summary>
        private CancellationTokenSource ReadCancellationTokenSource;

        /// <summary>
        /// Initialisation de la page
        /// </summary>
        public MainPage()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// Event
        /// Chargement de la page
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            InitSerial();
        }

        /// <summary>
        /// Demande d'initialisation du port série
        /// </summary>
        private async void InitSerial()
        {
            await Page_LoadedAsync();
        }

        /// <summary>
        /// Initialisation port série
        /// </summary>
        /// <returns></returns>
        private async Task Page_LoadedAsync()
        {
            await Initialise(9600);

        }

        /// <summary>
        /// Initialisation du port série
        /// 9600, pas de parité, un bit de stop, 8bits
        /// début de réception
        /// </summary>
        /// <param name="BaudRate"></param>
        /// <returns></returns>
        public async Task Initialise(uint BaudRate)     //NOTE - THIS IS AN ASYNC METHOD!
        {
            try
            {
                // Recherche du port série
                string aqs = SerialDevice.GetDeviceSelector("UART0");
                var dis = await DeviceInformation.FindAllAsync(aqs);
                UartPort = await SerialDevice.FromIdAsync(dis[0].Id);

                //Configuration du port série
                //mS before a time-out occurs when a write operation does not finish (default=InfiniteTimeout).
                UartPort.WriteTimeout = TimeSpan.FromMilliseconds(10000);
                //mS before a time-out occurs when a read operation does not finish (default=InfiniteTimeout).
                UartPort.ReadTimeout = TimeSpan.FromMilliseconds(10000);
                UartPort.BaudRate = 9600;
                UartPort.Parity = SerialParity.None;
                UartPort.StopBits = SerialStopBitCount.One;
                UartPort.DataBits = 8;

                DataReaderObject = new DataReader(UartPort.InputStream);
                DataReaderObject.InputStreamOptions = InputStreamOptions.Partial;
                DataWriterObject = new DataWriter(UartPort.OutputStream);

                // Début de la réception
                StartReceive();
            }
            catch (Exception ex)
            {
                throw new Exception("Uart Initialise Error", ex);
            }
        }

        /// <summary>
        /// Réception du port série
        /// Mise en écoute du port
        /// </summary>
        public async void StartReceive()
        {
            ReadCancellationTokenSource = new CancellationTokenSource();
            while (true)
            {
                await Listen();
                if ((ReadCancellationTokenSource.Token.IsCancellationRequested) || (UartPort == null))
                    break;
            }
        }

        /// <summary>
        /// Réception d'un octet
        /// </summary>
        /// <returns></returns>
        private async Task Listen()
        {
            // Buffer de réception
            const int NUMBER_OF_BYTES_TO_RECEIVE = 1024;
            byte[] ReceiveData;
            UInt32 bytesRead;
            Affichage affichage = new Affichage();

            try
            {
                if (UartPort != null)
                {
                    while (true)
                    {
                        //###### WINDOWS IoT MEMORY LEAK BUG 2017-03 - USING CancellationToken WITH LoadAsync() CAUSES A BAD MEMORY LEAK.  WORKAROUND IS
                        //TO BUILD RELEASE WITHOUT USING THE .NET NATIVE TOOLCHAIN OR TO NOT USE A CancellationToken IN THE CALL #####
                        //bytesRead = await DataReaderObject.LoadAsync(NUMBER_OF_BYTES_TO_RECEIVE).AsTask(ReadCancellationTokenSource.Token);	//Wait until buffer is full
                        bytesRead = await DataReaderObject.LoadAsync(NUMBER_OF_BYTES_TO_RECEIVE).AsTask();  //Wait until buffer is full

                        if ((ReadCancellationTokenSource.Token.IsCancellationRequested) || (UartPort == null))
                            break;

                        if (bytesRead > 0)
                        {
                            ReceiveData = new byte[NUMBER_OF_BYTES_TO_RECEIVE];
                            DataReaderObject.ReadBytes(ReceiveData);

                            string message = "";
                            bool premiereTrame = true;
                            // Ecriture des données dans les zones de texte à l'écran
                            foreach (byte Data in ReceiveData)
                            {
                                // Décodage des trames pour récupérer les informations voules et les afficher
                                if (Convert.ToChar(Data).ToString() == "$")
                                {
                                    if (premiereTrame)
                                    {
                                        premiereTrame = false;
                                    }
                                    else
                                    {
                                        switch (message.Split(',')[0])
                                        {
                                            case "$GPGGA":
                                                affichage.setGPGGA(message);
                                                break;
                                            case "$GPGLL":
                                                affichage.setGPGLL(message);
                                                break;
                                            case "$GPGSA":
                                                affichage.setGPGSA(message);
                                                break;
                                            case "$GPGSV":
                                                affichage.setGPGSV(message);
                                                break;
                                            case "$GPVTG":
                                                affichage.setGPVTG(message);
                                                break;
                                            case "$GPRMC":
                                                affichage.setGPRMC(message);
                                                break;
                                        }
                                        heure.Text = affichage.getHeure();
                                        date.Text = affichage.getDate();
                                        latitude.Text = affichage.getLatitude();
                                        longitude.Text = affichage.getLongitude();
                                        vitesse.Text = affichage.getVitesse();
                                        cap.Text = affichage.getCap();
                                        distance.Text = affichage.getDistance();
                                        altitude.Text = affichage.getAltitude();
                                    }
                                    message = "$";
                                }
                                else
                                {
                                    message += Convert.ToChar(Data);
                                }
                            } // foreach (byte Data in ReceiveData)
                        } //if (bytesRead > 0)
                    } //  while (true)
                } //if (UartPort != null)
            }
            catch (Exception e)
            {
                //We will get here often if the USB serial cable is removed so reset ready for a new connection (otherwise a never ending error occurs)
                if (ReadCancellationTokenSource != null)
                    ReadCancellationTokenSource.Cancel();
                System.Diagnostics.Debug.WriteLine("UART ReadAsync Exception: {0}", e.Message);
            }
        }
    }
}

