# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
MCP4822_SOURCES = GestionMCP4822.cpp
GENERATEUR_SOURCES = generateur.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
MCP4822_OBJECTS = $(MCP4822_SOURCES:.cpp=.o)
GENERATEUR_OBJECTS = $(GENERATEUR_SOURCES:.cpp=.o)

# Les programmes a générer
GENERATEUR_EXEC = generateur

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme 1
target: $(GENERATEUR_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(GENERATEUR_EXEC): $(MCP4822_OBJECTS) $(GENERATEUR_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(GENERATEUR_EXEC)	
