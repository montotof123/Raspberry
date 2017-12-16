# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
CIRCUIT_SOURCES = Gestion74HCT595.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
AFF7SEG_SOURCES = Affichage7seg.cpp
MATRIX_SOURCES = AffichageMatrix.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
CIRCUIT_OBJECTS = $(CIRCUIT_SOURCES:.cpp=.o)
AFF7SEG_OBJECTS = $(AFF7SEG_SOURCES:.cpp=.o)
MATRIX_OBJECTS = $(MATRIX_SOURCES:.cpp=.o)

# Les programmes a générer
AFF7SEG_EXEC = Affichage7seg
MATRIX_EXEC = AffichageMatrix

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target target_matrix clean

# Le programme 1
target: $(AFF7SEG_EXEC)
target_matrix: $(MATRIX_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(AFF7SEG_EXEC): $(CIRCUIT_OBJECTS) $(GPIO_OBJECTS) $(AFF7SEG_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(MATRIX_EXEC): $(CIRCUIT_OBJECTS) $(GPIO_OBJECTS) $(MATRIX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(AFF7SEG_EXEC)	
	@rm -f $(MATRIX_EXEC)	
