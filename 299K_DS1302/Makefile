# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi -lwiringPiDev

# Groupes de fichiers sources
CIRCUIT_SOURCES = GestionDS1302.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
TEST_SOURCES = tstGestionDS1302.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
CIRCUIT_OBJECTS = $(CIRCUIT_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstGestionDS1302

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme 1
target: $(TEST_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(CIRCUIT_OBJECTS) $(GPIO_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
