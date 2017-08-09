# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
DS18B20_SOURCES = Gestion1Wire.cpp GestionSlave1Wire.cpp GestionDS18B20.cpp MesureDS18B20.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
AFFICHAGE_SOURCES = GestionHP50827300.cpp GestionAffichage.cpp
HCSR04_SOURCES = GestionHCSR04.cpp
MESURE_SOURCES = mesureHCSR04.cpp
MESURES_AFF_SOURCES = startAffHCSR04.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
DS18B20_OBJECTS = $(DS18B20_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
AFFICHAGE_OBJECTS = $(AFFICHAGE_SOURCES:.cpp=.o)
HCSR04_OBJECTS = $(HCSR04_SOURCES:.cpp=.o)
MESURE_OBJECTS = $(MESURE_SOURCES:.cpp=.o)
MESURES_AFF_OBJECTS = $(MESURES_AFF_SOURCES:.cpp=.o)

# Les programmes a générer
MESURE_EXEC = mesureHCSR04
MESURES_AFF_EXEC = startAffHCSR04

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target target_aff clean

# Le programme de mesure
target: $(MESURE_EXEC)

# Le programme d'affichage
target_aff: $(MESURES_AFF_EXEC)

# Compilation du programme de mesure $@ représente les fichiers objets et $^ le nom du programme
$(MESURE_EXEC): $(DS18B20_OBJECTS) $(GPIO_OBJECTS) $(HCSR04_OBJECTS) $(MESURE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme d'affichage
$(MESURES_AFF_EXEC): $(AFFICHAGE_OBJECTS) $(GPIO_OBJECTS) $(MESURES_AFF_OBJECTS)
	$(CC) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(MESURE_EXEC)	
	@rm -f $(MESURES_AFF_EXEC)
