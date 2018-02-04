# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
FREQUENCEMETRE_SOURCES = frequencemetre.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
FREQUENCEMETRE_OBJECTS = $(FREQUENCEMETRE_SOURCES:.cpp=.o)

# Les programmes a générer
FREQUENCEMETRE_EXEC = frequencemetre

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme 1
target: $(FREQUENCEMETRE_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(FREQUENCEMETRE_EXEC): $(GPIO_OBJECTS) $(FREQUENCEMETRE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(FREQUENCEMETRE_EXEC)	
