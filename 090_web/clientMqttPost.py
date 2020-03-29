#################################################
#
# Import 
#
#################################################
# MQTT
import paho.mqtt.client as mqtt
# Temporisation
import time
# PostgreSQL
import psycopg2
# Horloge
from datetime import datetime

#################################################
#
# Variables globales
#
#################################################
temperature = 0
pression = 0
pression_mer = 0
altitude = 0
humidite = 0
flagAll = False

#################################################
#
#                  Fonctions
#
#################################################
# Fonction appele lors de la reception d'un message
def messageFunction (client, userdata, message):
    global temperature
    global pression
    global pression_mer
    global altitude
    global humidite
    global flagAll
	
	# Message brute
    topic = str(message.topic)
    message = str(message.payload.decode("utf-8"))
	
	# Aiguillage message
    if topic == "alive":
        # Horloge
        now = datetime.now()
        current_time = now.strftime("%H:%M:%S")
        print(message, "at", current_time)           
    elif topic == "meteo":
        print(topic + ' ' + message)
	
	    # Decoupage du message
        tab = message.split(' - ')
        mesure = tab[0].split(' = ')
        unite = tab[1].split(' = ')
        print(mesure[0])
        print(mesure[1])
        print(unite[0])
        print(unite[1])
    
	    # Memorisation des mesures
        flagAll = False
        if mesure[0] == "Temperature":
            temperature = mesure[1]
        if mesure[0] == "Pression":
            pression = mesure[1]
        if mesure[0] == "Pression niveau mer":
            pression_mer = mesure[1]
        if mesure[0] == "Altitude approximative":
            altitude = mesure[1]
        if mesure[0] == "Humidite":
            humidite = mesure[1]
		    # Quand on arrive a humidite, on peut stocker une ligne dans la bdd
            flagAll = True		

#################################################
#
#                  Setup
#
#################################################
# Creation d'un client MQTT (Le nom n'est pas determinant)
ourClient = mqtt.Client("meteo_mqtt")
# Login et mot de passe
ourClient.username_pw_set(username="montotof",password="trucmuche")
# Connexion
ourClient.connect("192.168.1.27", 1883)
# Abonnement a un sujet
ourClient.subscribe("meteo") 
ourClient.subscribe("alive") 
# Fonction appelée lors de la reception d'un message
ourClient.on_message = messageFunction
# Demarrage du client
ourClient.loop_start()


#################################################
#
#                  Loop
#
#################################################
while(1):
    ourClient.publish("alive", "ok")
    if flagAll:
        try:
		    # Insersion d'une ligne dans la table
            connection = psycopg2.connect(user="postgres",
                                          password="trucmuche",
                                          host="127.0.0.1",
                                          port="5432",
                                          database="postgres")
            cursor = connection.cursor()
            postgres_insert_query = """ INSERT INTO raspberry.meteo (horaire, pression_brute, pression_niveau_mer, altitude, humidite, temperature) VALUES (current_timestamp, %s, %s, %s, %s, %s)"""
            record_to_insert = (pression, pression_mer, altitude, humidite, temperature)
            cursor.execute(postgres_insert_query, record_to_insert)
            connection.commit()
            count = cursor.rowcount

            # Horloge
            now = datetime.now()
            current_time = now.strftime("%H:%M:%S")
            print("Current Time =", current_time)           
            print (count, "Record inserted successfully into meteo table")
            flagAll = False

        except (Exception, psycopg2.Error) as error :
		    # Erreur
            if(connection):
                print("Failed to insert record into meteo table", error)

        finally:
            #closing database connection.
            if(connection):
                cursor.close()
                connection.close()
                print("PostgreSQL connection is closed")  

    time.sleep(3)
