# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
INA219_SOURCES = GestionINA219.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
TEST_SOURCES = MesureurSimple.cpp
OSCILLO_SOURCES = Oscillo.cpp
PILOTAGE_SOURCES = PilotageMoteur.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
INA219_OBJECTS = $(INA219_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
OSCILLO_OBJECTS = $(OSCILLO_SOURCES:.cpp=.o)
PILOTAGE_OBJECTS = $(PILOTAGE_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = MesureurSimple
OSCILLO_EXEC = Oscillo
PILOTAGE_EXEC = PilotageMoteur

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target target_oscillo target_pilotage clean

# Le programme 1
target: $(TEST_EXEC)
target_oscillo: $(OSCILLO_EXEC)
target_pilotage: $(PILOTAGE_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(I2C_OBJECTS) $(INA219_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(OSCILLO_EXEC): $(I2C_OBJECTS) $(INA219_OBJECTS) $(OSCILLO_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(PILOTAGE_EXEC): $(I2C_OBJECTS) $(INA219_OBJECTS) $(GPIO_OBJECTS) $(PILOTAGE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
	@rm -f $(OSCILLO_EXEC)	
	@rm -f $(PILOTAGE_EXEC)	
