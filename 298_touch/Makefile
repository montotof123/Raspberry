# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
SENSOR_SOURCES = Sensors.cpp
SENSOR4_SOURCES = Sensors4.cpp
SENSOR_INTERRUPT_SOURCES = SensorsInterrupt.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
SENSOR_OBJECTS = $(SENSOR_SOURCES:.cpp=.o)
SENSOR4_OBJECTS = $(SENSOR4_SOURCES:.cpp=.o)
SENSOR_INTERRUPT_OBJECTS = $(SENSOR_INTERRUPT_SOURCES:.cpp=.o)

# Les programmes a générer
SENSOR_EXEC = Sensors
SENSOR4_EXEC = Sensors4
SENSOR_INTERRUPT_EXEC = SensorsInterrupt

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target target4 target_interrupt clean

# Le programme 1
target: $(SENSOR_EXEC)
target4: $(SENSOR4_EXEC)
target_interrupt: $(SENSOR_INTERRUPT_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(SENSOR_EXEC): $(GPIO_OBJECTS) $(SENSOR_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(SENSOR4_EXEC): $(GPIO_OBJECTS) $(SENSOR4_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(SENSOR_INTERRUPT_EXEC): $(GPIO_OBJECTS) $(SENSOR_INTERRUPT_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(SENSOR_EXEC)	
	@rm -f $(SENSOR4_EXEC)	
	@rm -f $(SENSOR_INTERRUPT_EXEC)	
