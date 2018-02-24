# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
MESURE_SOURCES = mesures.cpp
MCP3208_SOURCES = GestionMCP3208.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
MESURE_OBJECTS = $(MESURE_SOURCES:.cpp=.o)
MCP3208_OBJECTS = $(MCP3208_SOURCES:.cpp=.o)

# Les programmes a générer
MESURE_EXEC = mesures

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme 1
target: $(MESURE_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(MESURE_EXEC): $(MESURE_OBJECTS) $(MCP3208_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(MESURE_EXEC)	
