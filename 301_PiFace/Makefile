# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
CIRCUIT_SOURCES = GestionMCP23x17.cpp GestionMCP23S17.cpp
CHENILLARD_SOURCES = PiFaceChenillard.cpp
READ_SWITCH_SOURCES = PiFaceReadSwitch.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
CIRCUIT_OBJECTS = $(CIRCUIT_SOURCES:.cpp=.o)
CHENILLARD_OBJECTS = $(CHENILLARD_SOURCES:.cpp=.o)
READ_SWITCH_OBJECTS = $(READ_SWITCH_SOURCES:.cpp=.o)

# Les programmes a générer
CHENILLARD_EXEC = PiFaceChenillard
READ_SWITCH_EXEC = PiFaceReadSwitch

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target_chenillard target_read_switch clean

# Le programme 1
target_chenillard: $(CHENILLARD_EXEC)
target_read_switch: $(READ_SWITCH_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(CHENILLARD_EXEC): $(CIRCUIT_OBJECTS) $(CHENILLARD_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
	
$(READ_SWITCH_EXEC): $(CIRCUIT_OBJECTS) $(READ_SWITCH_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(CHENILLARD_EXEC)	
	@rm -f $(READ_SWITCH_EXEC)	
