# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
TEST_SOURCES = tstADS1115.cpp
TEST_SINGLE_SOURCES = tstADS1115FullSingle.cpp
TEST_COMPARE_SOURCES = tstADS1115FullCompare.cpp
TEST_CONTINUOUS_SOURCES = tstADS1115FullContinuous.cpp
TEST_CONTINUOUS_INTR_SOURCES = tstADS1115FullContinuousIntr.cpp
ADS1115_SOURCES = GestionADS1115.cpp
ADS1115FULL_SOURCES = GestionADS1115Full.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
BIG_AFFICHAGE_SOURCES = GestionBigAffichage.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_SINGLE_OBJECTS = $(TEST_SINGLE_SOURCES:.cpp=.o)
TEST_COMPARE_OBJECTS = $(TEST_COMPARE_SOURCES:.cpp=.o)
TEST_CONTINUOUS_OBJECTS = $(TEST_CONTINUOUS_SOURCES:.cpp=.o)
TEST_CONTINUOUS_INTR_OBJECTS = $(TEST_CONTINUOUS_INTR_SOURCES:.cpp=.o)
ADS1115_OBJECTS = $(ADS1115_SOURCES:.cpp=.o)
ADS1115FULL_OBJECTS = $(ADS1115FULL_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
BIG_AFFICHAGE_OBJECTS = $(BIG_AFFICHAGE_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstADS1115
TEST_SINGLE_EXEC = tstADS1115FullSingle
TEST_COMPARE_EXEC = tstADS1115FullCompare
TEST_CONTINUOUS_EXEC = tstADS1115FullContinuous
TEST_CONTINUOUS_INTR_EXEC = tstADS1115FullContinuousIntr

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target target_single target_compare target_continuous target_continuous_intr clean

# Le programme 1
target: $(TEST_EXEC)
target_single: $(TEST_SINGLE_EXEC)
target_compare: $(TEST_COMPARE_EXEC)
target_continuous: $(TEST_CONTINUOUS_EXEC)
target_continuous_intr: $(TEST_CONTINUOUS_INTR_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(TEST_OBJECTS) $(ADS1115_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_SINGLE_EXEC): $(TEST_SINGLE_OBJECTS) $(ADS1115FULL_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_COMPARE_EXEC): $(TEST_COMPARE_OBJECTS) $(ADS1115FULL_OBJECTS) $(GPIO_OBJECTS) $(BIG_AFFICHAGE_OBJECTS) 
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_CONTINUOUS_EXEC): $(TEST_CONTINUOUS_OBJECTS) $(ADS1115FULL_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_CONTINUOUS_INTR_EXEC): $(TEST_CONTINUOUS_INTR_OBJECTS) $(ADS1115FULL_OBJECTS) $(GPIO_OBJECTS) $(BIG_AFFICHAGE_OBJECTS) 
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
	@rm -f $(TEST_SINGLE_EXEC)	
	@rm -f $(TEST_COMPARE_EXEC)	
	@rm -f $(TEST_CONTINUOUS_EXEC)	
	@rm -f $(TEST_CONTINUOUS_INTR_EXEC)	
