# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
MCP6S2x_SOURCES = GestionMCP6S21.cpp GestionMCP6S22.cpp GestionMCP6S26.cpp GestionMCP6S28.cpp
SETG10C0_SOURCES = setG10C0.cpp
SETG8C7_SOURCES = setG8C7.cpp
SETGAINCANAL_SOURCES = setGainCanal.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
MCP6S2x_OBJECTS = $(MCP6S2x_SOURCES:.cpp=.o)
SETG10C0_OBJECTS = $(SETG10C0_SOURCES:.cpp=.o)
SETG8C7_OBJECTS = $(SETG8C7_SOURCES:.cpp=.o)
SETGAINCANAL_OBJECTS = $(SETGAINCANAL_SOURCES:.cpp=.o)

# Les programmes a générer
SETG10C0_EXEC = setG10C0
SETG8C7_EXEC = setG8C7
SETGAINCANAL_EXEC = setGainCanal

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target_setG10C0 target_setG8C7 target_setGainCanal clean

# Le programme 1
target_setG10C0: $(SETG10C0_EXEC)
target_setG8C7: $(SETG8C7_EXEC)
target_setGainCanal: $(SETGAINCANAL_EXEC)

## Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(SETG10C0_EXEC): $(MCP6S2x_OBJECTS) $(SETG10C0_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

## Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(SETG8C7_EXEC): $(MCP6S2x_OBJECTS) $(SETG8C7_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

## Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(SETGAINCANAL_EXEC): $(MCP6S2x_OBJECTS) $(SETGAINCANAL_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(SETG10C0_EXEC)	
	@rm -f $(SETG8C7_EXEC)	
	@rm -f $(SETGAINCANAL_EXEC)	
