# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
SERVO_SOURCES = GestionServo.cpp
PCA9685_SOURCES = GestionPCA9685.cpp
PCA9685_SERVO_SOURCES = GestionServoPCA9685.cpp
TEST_SOURCES = tstServoPCA9685.cpp
PARAMETRAGE_SOURCES = parametrageServoPCA9685.cpp
TEST_PARAMETRE_SOURCES = tstParametreServoPCA9685.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
SERVO_OBJECTS = $(SERVO_SOURCES:.cpp=.o)
PCA9685_OBJECTS = $(PCA9685_SOURCES:.cpp=.o)
PCA9685_SERVO_OBJECTS = $(PCA9685_SERVO_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
PARAMETRAGE_OBJECTS = $(PARAMETRAGE_SOURCES:.cpp=.o)
TEST_PARAMETRE_OBJECTS = $(TEST_PARAMETRE_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstServoPCA9685
PARAMETRAGE_EXEC = parametrageServoPCA9685
TEST_PARAMETRE_EXEC = tstParametreServoPCA9685

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target target_parametrage target_test_parametre clean

# Le programme 1
target: $(TEST_EXEC)

# Le programme 2
target_parametrage: $(PARAMETRAGE_EXEC)

# Le programme 3
target_test_parametre: $(TEST_PARAMETRE_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(I2C_OBJECTS) $(SERVO_OBJECTS) $(PCA9685_OBJECTS) $(PCA9685_SERVO_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 2 $@ représente les fichiers objets et $^ le nom du programme
$(PARAMETRAGE_EXEC): $(I2C_OBJECTS) $(PCA9685_OBJECTS) $(PARAMETRAGE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 2 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_PARAMETRE_EXEC): $(I2C_OBJECTS) $(SERVO_OBJECTS) $(PCA9685_OBJECTS) $(PCA9685_SERVO_OBJECTS) $(TEST_PARAMETRE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
	@rm -f $(PARAMETRAGE_EXEC)	
	@rm -f $(TEST_PARAMETRE_EXEC)	
