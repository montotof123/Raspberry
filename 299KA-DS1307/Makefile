# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -Wall -lpthread -lwiringPi

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
DS1307_SOURCES = GestionDS1307.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
LOGGER_SOURCES = Logger.cpp
TEST_DS1307_SOURCES = tstDS1307.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
DS1307_OBJECTS = $(DS1307_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
LOGGER_OBJECTS = $(LOGGER_SOURCES:.cpp=.o)
TEST_DS1307_OBJECTS = $(TEST_DS1307_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_DS1307_EXEC = tstDS1307

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme 1
target: $(TEST_DS1307_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_DS1307_EXEC): $(I2C_OBJECTS) $(DS1307_OBJECTS) $(TEST_DS1307_OBJECTS) $(GPIO_OBJECTS) $(LOGGER_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_DS1307_EXEC)	
