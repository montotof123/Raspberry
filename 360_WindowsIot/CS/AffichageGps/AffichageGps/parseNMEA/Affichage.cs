using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AffichageGps.parseNMEA
{
    class Affichage
    {
        /// <summary>
        /// Heure du GPS
        /// </summary>
        private string heure = "000000";

        /// <summary>
        /// Date du GPS
        /// </summary>
        private string date = "000000";

        /// <summary>
        /// Ancienne latitude du GPS pour calcul distance
        /// </summary>
        private string oldLatitude = "0";

        /// <summary>
        /// Ancienne Longitude du GPS pour calcul distance
        /// </summary>
        private string oldLongitude = "0";

        /// <summary>
        /// Latitude du GPS
        /// </summary>
        private string latitude = "0";

        /// <summary>
        /// Longitude du GPS
        /// </summary>
        private string longitude = "0";

        /// <summary>
        /// Vitesse du GPS
        /// </summary>
        private string vitesse = "0";

        /// <summary>
        /// Distance du GPS
        /// </summary>
        private double distance = 0;

        /// <summary>
        /// Altitude du GPS
        /// </summary>
        private string altitude = "0";

        /// <summary>
        /// Cap du GPS
        /// </summary>
        private string cap = "0";

        /// <summary>
        /// Getter heure
        /// </summary>
        /// <returns></returns>
        public string getHeure()
        {
            return heure.Substring(0, 2) + ":" + heure.Substring(2, 2) + ":" + heure.Substring(4, 2);
        }

        /// <summary>
        /// Getter date
        /// </summary>
        /// <returns></returns>
        public string getDate()
        {
            return date.Substring(0, 2) + "/" + date.Substring(2, 2) + "/20" + date.Substring(4, 2);
        }

        /// <summary>
        /// Getter latitude
        /// </summary>
        /// <returns></returns>
        public string getLatitude()
        {
            return latitude;
        }

        /// <summary>
        /// Getter longitude
        /// </summary>
        /// <returns></returns>
        public string getLongitude()
        {
            return longitude;
        }

        /// <summary>
        /// Getter vitesse
        /// </summary>
        /// <returns></returns>
        public string getVitesse()
        {
            return vitesse + " m/s";
        }

        /// <summary>
        /// Getter distance
        /// </summary>
        /// <returns></returns>
        public string getDistance()
        {
            return Math.Round(distance, 2).ToString() + " m";
        }

        /// <summary>
        ///  Getter altitude
        /// </summary>
        /// <returns></returns>
        public string getAltitude()
        {
            return altitude + " m";
        }

        /// <summary>
        /// Getter cap
        /// </summary>
        /// <returns></returns>
        public string getCap()
        {
            return cap + "°";
        }

        /// <summary>
        /// Découpe une trame GGA
        /// $GPGGA,112556.00,4316.56763,N,00532.08137,E,1,07,1.21,122.2,M,47.7,M,,*52
        /// 0      1         2          3 4           5 6 7  8    9     10 11  12 13 14
        /// </summary>
        /// <param name="message"></param>
        public void setGPGGA(string message)
        {
            string[] items = message.Split(',');
            heure = items[1];
            oldLatitude = latitude;
            latitude = items[2] + items[3];
            oldLongitude = longitude;
            longitude = items[4] + items[5];
            if (oldLatitude != "0")
            {
                setDistance();
            }
            altitude = items[9];
        }

        /// <summary>
        /// Découpe une trame GLL
        /// $GPGLL,4316.56763,N,00532.08137,E,112556.00,A,A*65
        /// 0      1          2 3           4 5         6 7
        /// </summary>
        /// <param name="message"></param>
        public void setGPGLL(string message)
        {
            string[] items = message.Split(',');
            oldLatitude = latitude;
            latitude = items[1] + items[2];
            oldLongitude = longitude;
            longitude = items[3] + items[4];
            if (oldLatitude != "0")
            {
                setDistance();
            }
            heure = items[5];
        }

        /// <summary>
        /// Découpe une trame GSA
        /// $GPGSA,A,3,23,09,06,05,07,02,30,,,,,,2.05,1.21,1.65*08
        /// (Pas d'info pour le programme)
        /// </summary>
        /// <param name="message"></param>
        public void setGPGSA(string message)
        {
            string[] items = message.Split(',');
        }

        /// <summary>
        /// Découpe une trame GSV
        /// $GPGSV,3,1,10,02,37,253,25,05,41,308,31,06,25,205,22,07,68,074,25*7D
        /// (Pas d'info pour le programme)
        /// </summary>
        /// <param name="message"></param>
        public void setGPGSV(string message)
        {
            string[] items = message.Split(',');
        }

        /// <summary>
        /// Découpe une trame VTG
        /// $GPVTG,,T,,M,0.086,N,0.160,K,A*2A
        /// 0     1 2 34 5     6 7     8 9
        /// </summary>
        /// <param name="message"></param>
        public void setGPVTG(string message)
        {
            string[] items = message.Split(',');
            cap = items[1];
            vitesse = items[7];
        }

        /// <summary>
        /// Découpe une trame RMC
        /// $GPRMC,112557.00,A,4316.56760,N,00532.08143,E,0.086,,050119,,,A*7F
        /// 0      1         2 3          4 5           6 7    8 9
        /// </summary>
        /// <param name="message"></param>
        public void setGPRMC(string message)
        {
            string[] items = message.Split(',');
            oldLatitude = latitude;
            latitude = items[3] + items[4];
            oldLongitude = longitude;
            longitude = items[5] + items[6];
            if(oldLatitude != "0")
            {
                setDistance();
            }
            cap = items[8];
            date = items[9];
        }

        /// <summary>
        /// Calcul de la distance entre deux points GPS
        /// </summary>
        private void setDistance()
        {
            double oldLatRad = ConvertToRadians(ConvLat(oldLatitude));
            double oldLongRad = ConvertToRadians(ConvLong(oldLongitude));
            double newLatRad = ConvertToRadians(ConvLat(latitude));
            double newLongRad = ConvertToRadians(ConvLong(longitude));

            double deltaDistance = Math.Acos(Math.Sin(oldLatRad) * Math.Sin(newLatRad) + Math.Cos(oldLatRad) * Math.Cos(newLatRad) * Math.Cos(oldLongRad - newLongRad)) * 6371000;
            // cas de coordonnéées strictement identiques
            if(Double.IsNaN(deltaDistance))
            {
                deltaDistance = 0;
            }
            distance += deltaDistance;

        }

        /// <summary>
        /// Conversion de la latitude GPS en latitude fractionnaire
        /// </summary>
        /// <param name="latit"></param>
        /// <returns></returns>
        private double ConvLat(string latit)
        {
            double valEntiere = Convert.ToDouble(latit.Substring(0, 2));
             double valFract = Convert.ToDouble(latit.Substring(2, 8).Replace('.', ','));
            valFract /= 60;
            double valLat = valEntiere + valFract;
            if (latit.Substring(9) == "S")
            {
                valLat = -valLat;
            }
            return valLat;
        }

        /// <summary>
        /// Conversion de la longitude GPS en longitude fractionnaire
        /// </summary>
        /// <param name="latit"></param>
        /// <returns></returns>
        private double ConvLong(string longit)
        {
            double valEntiere = Convert.ToDouble(longit.Substring(0, 3));
            double valFract = Convert.ToDouble(longit.Substring(3, 8).Replace('.', ','));
            valFract /= 60;
            double valLong = valEntiere + valFract;
            if (longit.Substring(10) == "W")
            {
                valLong = -valLong;
            }
            return valLong;
        }

        /// <summary>
        /// Conversion degré en radian
        /// </summary>
        /// <param name="angle"></param>
        /// <returns></returns>
        public double ConvertToRadians(double angle)
        {
            return (Math.PI / 180) * angle;
        }
    }
}
