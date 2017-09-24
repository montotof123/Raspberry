# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
LED_SOURCES = GestionLed.cpp GestionLedRGB.cpp
PCA9685_SOURCES = GestionPCA9685.cpp
PCA9685_LED_SOURCES = GestionLedRGBPCA9685.cpp GestionLedPCA9685.cpp
TCS34725_SOURCES = GestionTCS34725.cpp
TEST_SOURCES = tstTCS34725.cpp
TEST_LED_SOURCES = tstLed.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
LED_OBJECTS = $(LED_SOURCES:.cpp=.o)
PCA9685_OBJECTS = $(PCA9685_SOURCES:.cpp=.o)
PCA9685_LED_OBJECTS = $(PCA9685_LED_SOURCES:.cpp=.o)
TCS34725_OBJECTS = $(TCS34725_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_LED_OBJECTS = $(TEST_LED_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstTCS34725
TEST_LED_EXEC = tstLed

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target target_led clean

# Le programme 1
target: $(TEST_EXEC)

# Le programme 2
target_led: $(TEST_LED_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(I2C_OBJECTS) $(TCS34725_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 2 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_LED_EXEC): $(I2C_OBJECTS) $(PCA9685_OBJECTS) $(LED_OBJECTS) $(PCA9685_LED_OBJECTS) $(TCS34725_OBJECTS) $(TEST_LED_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
	@rm -f $(TEST_LED_EXEC)	
