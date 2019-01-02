using System;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.Spi;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

// Pour plus d'informations sur le modèle d'élément Page vierge, consultez la page https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Oscilloscope
{
    /// <summary>
    /// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        /// <summary>
        /// Interface SPI
        /// </summary>
        private SpiDevice SpiADC;

        /// <summary>
        /// Nombre de mesure du convertisseur pour un affichage
        /// Correspond au nombre de pixel de la zone de dessin
        /// </summary>
        private const int nbValeur = 1800;

        /// <summary>
        /// Tableaux des mesures du convertisseur
        /// </summary>
        private int[] tabValeur = new int[nbValeur];

        /// <summary>
        /// Tableau des lignes du dessin
        /// </summary>
        private Line[] tabLine = new Line[nbValeur];

        /// <summary>
        /// Indique si une courbe a été tracée
        /// </summary>
        private bool courbePresente = false;

        /// <summary>
        /// Temps du début des mesures
        /// </summary>
        private long tempsDebutMesure;

        /// <summary>
        /// Temps de la fin des mesures
        /// </summary>
        private long tempsFinMesure;

        /// <summary>
        /// Zomm d'affichage
        /// </summary>
        private int zoom = 1;
 
        /// <summary>
        /// Point de clic pour calcul de la fréquence
        /// </summary>
        private bool firstPoint = true;

        /// <summary>
        /// Buffer de lecture SPI
        /// </summary>
        private byte[] readBuffer = new byte[3];
 
        /// <summary>
        /// Buffer de commande SPI
        /// 00000110 00000000 00000000 configuration mode single canal 0
        /// http://ww1.microchip.com/downloads/en/DeviceDoc/21298e.pdf page 19 et 21
        /// </summary>
        private byte[] writeBuffer = new byte[] { 0x06, 0x00, 0x00 };

        /// <summary>
        /// Initialisation
        /// </summary>
        public MainPage()
        {
            this.InitializeComponent();
            InitAll();
        }

        /// <summary>
        /// Initialisation des interfaces
        /// doit être asynchrone car on a affaire à du matériel
        /// </summary>
        private async void InitAll()
        {
            await InitSPI();
        }

        /// <summary>
        /// Initialisation de l'interface SPI
        /// C'est une tache asynchrone pour bien initialiser le matériel
        /// </summary>
        /// <returns></returns>
        private async Task InitSPI()
        {
            try
            {
                var settings = new SpiConnectionSettings(0);
                settings.ClockFrequency = 6000000;   // Horloge 6MHz (maximum possible mesuré)
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
        /// Chargement de la page
        /// Dessin du cadrillage
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            SolidColorBrush brush = new SolidColorBrush(Windows.UI.Colors.LightGreen);
            Line myLine;
            for (int compteur = 0; compteur != 6; compteur++)
            {
                // Y = 5 colonnes de 180 pixels commençant à 50 et finissant à 950
                // Représente une echelle de 5V
                myLine = new Line();
                myLine.Stroke = brush;
                myLine.X1 = 50;
                myLine.Y1 = 50 + compteur * 180;
                myLine.X2 = 1850;
                myLine.Y2 = 50 + compteur * 180;
                myLine.HorizontalAlignment = HorizontalAlignment.Left;
                myLine.VerticalAlignment = VerticalAlignment.Top;
                myLine.StrokeThickness = 2;
                myGrid.Children.Add(myLine);
            }
            for (int compteur = 0; compteur != 11; compteur++)
            {
                // X = 10 colonnes de 180 pixels commençant à 50 et finissant à 1850
                myLine = new Line();
                myLine.Stroke = brush;
                myLine.X1 = 50 + compteur * 180;
                myLine.Y1 = 50;
                myLine.X2 = 50 + compteur * 180;
                myLine.Y2 = 950;
                myLine.HorizontalAlignment = HorizontalAlignment.Left;
                myLine.VerticalAlignment = VerticalAlignment.Top;
                myLine.StrokeThickness = 2;
                myGrid.Children.Add(myLine);
            }
        }

        /// <summary>
        /// Clic sur le bouton de demande de mesures
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            // Efface la courbe précédente si elle existe
            effaceCourbe();

            // Mémorise le temps de début des mesures
            tempsDebutMesure = DateTime.Now.Ticks;

            // Effectue les mesures
            for (int compteur = 0; compteur != nbValeur; compteur++)
            {
                tabValeur[compteur] = ReadFast();
            }

            // Mémorise le temps de fin des mesures
            tempsFinMesure = DateTime.Now.Ticks;

            // Trace la courbe des mesures
            traceCourbe();

            // Réinitialise le calcul de la fréquence
            Min.Text = "0";
            Max.Text = "0";
            Frequence.Text = "0 Hz";
        }

        /// <summary>
        /// Efface les élements de la courbe présent dans la grille
        /// </summary>
        private void effaceCourbe()
        {
            // On n'efface que si la courbe a déjà été dessinée
            if (courbePresente)
            {
                for (int compteur = 0; compteur != nbValeur; compteur++)
                {
                    myGrid.Children.Remove(tabLine[compteur]);
                }
            }
        }

        /// <summary>
        /// Trace la courbe représentant les mesures
        /// </summary>
        private void traceCourbe()
        {
            // Courbe en jaune
            SolidColorBrush brush = new SolidColorBrush(Windows.UI.Colors.Yellow);
            Line myLine;
            for (int compteur = 0; compteur != nbValeur - 1; compteur++)
            {
                myLine = new Line();
                myLine.Stroke = brush;
                myLine.X1 = 50 + compteur * zoom;
                myLine.Y1 = 950 - (tabValeur[compteur] * 900 / 4096);
                myLine.X2 = 50 + zoom + compteur * zoom;
                myLine.Y2 = 950 - (tabValeur[compteur + 1] * 900 / 4096);
                myLine.HorizontalAlignment = HorizontalAlignment.Left;
                myLine.VerticalAlignment = VerticalAlignment.Top;
                myLine.StrokeThickness = 2;
                myGrid.Children.Add(myLine);

                // Mémorisation des points pour effacement futur
                tabLine[compteur] = myLine;
            }
            // Une courbe a déjà été dessinée
            courbePresente = true;
        }

        /// <summary>
        /// Effectue une mesure sur le convertisseur MCP3208
        /// </summary>
        /// <returns></returns>
        private int ReadFast()
        {
            SpiADC.TransferFullDuplex(writeBuffer, readBuffer); // Lecture MCP3208
            return convertToIntMCP3208(readBuffer); // Conversion des octets reçu en entier
        }

        /// <summary>
        /// Désactivation du SPI à l'effacement de la page
        /// Le garbage collector s'occupera du reste
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Page_Unloaded(object sender, RoutedEventArgs e)
        {
            if (SpiADC != null)
            {
                SpiADC.Dispose();
            }
        }

        /// <summary>
        /// Clic sur un point de la grille pour calcul de la fréquence
        /// En cliquant sur deux points identiques de la courbe séparés par une alternance,
        /// on obtient la fréquence
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MyGrid_PointerPressed(object sender, Windows.UI.Xaml.Input.PointerRoutedEventArgs e)
        {
            // Récupération des coordonnées X des deux clic
            Windows.UI.Input.PointerPoint pt = e.GetCurrentPoint(myGrid);
            if (firstPoint)
            {
                Min.Text = Math.Round(pt.Position.X, 0).ToString();
                Max.Text = "0";
                Frequence.Text = "0 Hz";
            }
            else
            {
                // Si le min est bien inférieur au max alors le max est valide
                if (float.Parse(Min.Text) < pt.Position.X)
                {
                    Max.Text = Math.Round(pt.Position.X, 0).ToString();
                } else
                {
                    firstPoint = true;
                }
            }

            // calcul de la fréquence si on a cliqué sur deux point
            if (!firstPoint)
            {
                float min = float.Parse(Min.Text);
                float max = float.Parse(Max.Text);
                long nbNanoseconde = tempsFinMesure - tempsDebutMesure;
                float nbNanoSecondeParMesure = nbNanoseconde / nbValeur;
                double frequence = 1 / (nbNanoSecondeParMesure * (max - min) * Math.Pow(10, -7));
                frequence *= zoom;
                frequence = Math.Round(frequence, 2);
                Frequence.Text = frequence.ToString() + " Hz";
            }
            firstPoint = !firstPoint;
        }

        /// <summary>
        /// Demande de changement de zoom avec nouveau dessin de la courbe
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Zoom_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string zoomSelect = (e.AddedItems[0] as ComboBoxItem).Content as string;
            switch (zoomSelect)
            {
                case "zoom x 1":
                    zoom = 1;
                    break;

                case "zoom x 10":
                    zoom = 10;
                    break;

                case "zoom x 100":
                    zoom = 100;
                    break;
            }
            effaceCourbe();
            traceCourbe();
        }
    }
}
