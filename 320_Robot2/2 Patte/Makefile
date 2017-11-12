# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -Wall -lpthread -lwiringPi

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
INA219_SOURCES = GestionINA219.cpp
LED_SOURCES = GestionLedRGB.cpp GestionLed.cpp
PCA9685_SOURCES = GestionPCA9685.cpp
PCA9685_LED_SOURCES = GestionLedRGBPCA9685.cpp
SERVO_SOURCES = GestionServo.cpp
PCA9685_SERVO_SOURCES = GestionServoPCA9685.cpp
PATTE_SOURCES = GestionPatte.cpp
INSECT_SOURCES = GestionInsecte.cpp
TEST_SOURCES = tstInsecteUnePatte.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
INA219_OBJECTS = $(INA219_SOURCES:.cpp=.o)
LED_OBJECTS = $(LED_SOURCES:.cpp=.o)
PCA9685_OBJECTS = $(PCA9685_SOURCES:.cpp=.o)
PCA9685_LED_OBJECTS = $(PCA9685_LED_SOURCES:.cpp=.o)
SERVO_OBJECTS = $(SERVO_SOURCES:.cpp=.o)
PCA9685_SERVO_OBJECTS = $(PCA9685_SERVO_SOURCES:.cpp=.o)
INSECT_OBJECTS = $(INSECT_SOURCES:.cpp=.o)
PATTE_OBJECTS = $(PATTE_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstInsecteUnePatte

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme 1
target: $(TEST_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(I2C_OBJECTS) $(INA219_OBJECTS) $(LED_OBJECTS) $(PCA9685_OBJECTS) $(PCA9685_LED_OBJECTS) $(SERVO_OBJECTS) $(PCA9685_SERVO_OBJECTS) $(INSECT_OBJECTS) $(PATTE_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
