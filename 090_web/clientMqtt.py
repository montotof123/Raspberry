# Import des librairies MQTT et time pour les delais
import paho.mqtt.client as mqtt
import time

# Fonction appele lors de la reception d'un message
def messageFunction (client, userdata, message):
  topic = str(message.topic)
  message = str(message.payload.decode("utf-8"))
  print(topic + ' ' + message)
  tab = message.split(' - ')
  mesure = tab[0].split(' = ')
  unite = tab[1].split(' = ')
  print(mesure[0])
  print(mesure[1])
  print(unite[0])
  print(unite[1])
  
# Creation d'un client (Le nom n'est pas determinant)
ourClient = mqtt.Client("meteo_mqtt")
# Login et mot de passe
ourClient.username_pw_set(username="montotof",password="trucmuche")
# Connexion
ourClient.connect("192.168.1.27", 1883)
# Abonnement a un sujet
ourClient.subscribe("meteo") 
# Fonctione appelé lors de la reception d'un message
ourClient.on_message = messageFunction
# Demarrage du client
ourClient.loop_start()

# Boucle principale
while(1):
  # Message de vie toutes les 3 secondes
  ourClient.publish("meteo", "ok")
  time.sleep(10)
