# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
LED_SOURCES = GestionLed.cpp GestionLedRGB.cpp
PCA9685_SOURCES = GestionPCA9685.cpp
PCA9685_LED_SOURCES = GestionLedPCA9685.cpp GestionLedRGBPCA9685.cpp
TEST_SOURCES = tstPCA9685.cpp
TEST_FULL_SOURCES = tstFullPCA9685.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
LED_OBJECTS = $(LED_SOURCES:.cpp=.o)
PCA9685_OBJECTS = $(PCA9685_SOURCES:.cpp=.o)
PCA9685_LED_OBJECTS = $(PCA9685_LED_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_FULL_OBJECTS = $(TEST_FULL_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstPCA9685
TEST_FULL_EXEC = tstFullPCA9685

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target target_full clean

# Le programme 1
target: $(TEST_EXEC)

# Le programme 2
target_full: $(TEST_FULL_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(I2C_OBJECTS) $(LED_OBJECTS) $(PCA9685_OBJECTS) $(PCA9685_LED_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 2 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_FULL_EXEC): $(I2C_OBJECTS) $(PCA9685_OBJECTS) $(TEST_FULL_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
	@rm -f $(TEST_FULL_EXEC)	
