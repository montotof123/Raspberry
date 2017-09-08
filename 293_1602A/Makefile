# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi -lwiringPiDev

# Groupes de fichiers sources
AD5220_SOURCES = GestionAD5220.cpp GestionPin.cpp GestionPinGPIO.cpp
AFF1602A_SOURCES = tstGestion1602A.cpp Gestion1602A.cpp


# Groupes de fichiers objets générés (un pour chaque fichier source)
AD5220_OBJECTS = $(AD5220_SOURCES:.cpp=.o)
AFF1602A_OBJECTS = $(AFF1602A_SOURCES:.cpp=.o)

# Les programmes a générer
AFF_EXEC = tstGestion1602A

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme de mesure
target: $(AFF_EXEC)

# Compilation du programme de mesure $@ représente les fichiers objets et $^ le nom du programme
$(AFF_EXEC): $(AD5220_OBJECTS) $(AFF1602A_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(AFF_EXEC)	
