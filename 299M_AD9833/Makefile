# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
TEST_SOURCES = tstAD9833.cpp
AD9833_SOURCES = GestionAD9833.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
AD9833_OBJECTS = $(AD9833_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstAD9833

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme 1
target: $(TEST_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(TEST_OBJECTS) $(AD9833_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
