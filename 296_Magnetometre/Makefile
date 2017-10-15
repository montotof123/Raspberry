# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
HMC5883_SOURCES = GestionHMC5883.cpp
HMC5983_SOURCES = GestionHMC5983.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
STEPPER_SOURCES = GestionStepper.cpp
TEST_HMC5883_SOURCES = tstHMC5883.cpp
TEST_HMC5983_SOURCES = tstHMC5983.cpp
CALIBRATION_POSITIVE_HMC5883_SOURCES = calibrationPositiveHMC5883.cpp
CALIBRATION_NEGATIVE_HMC5883_SOURCES = calibrationNegativeHMC5883.cpp
SEARCH_NORTH_SOURCES = searchNorth.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
HMC5883_OBJECTS = $(HMC5883_SOURCES:.cpp=.o)
HMC5983_OBJECTS = $(HMC5983_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
STEPPER_OBJECTS = $(STEPPER_SOURCES:.cpp=.o)
TEST_HMC5883_OBJECTS = $(TEST_HMC5883_SOURCES:.cpp=.o)
TEST_HMC5983_OBJECTS = $(TEST_HMC5983_SOURCES:.cpp=.o)
CALIBRATION_POSITIVE_HMC5883_OBJECTS = $(CALIBRATION_POSITIVE_HMC5883_SOURCES:.cpp=.o)
CALIBRATION_NEGATIVE_HMC5883_OBJECTS = $(CALIBRATION_NEGATIVE_HMC5883_SOURCES:.cpp=.o)
SEARCH_NORTH_OBJECTS = $(SEARCH_NORTH_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_HMC5883_EXEC = tstHMC5883
TEST_HMC5983_EXEC = tstHMC5983
CALIBRATION_POSITIVE_HMC5883_EXEC = calibrationPositiveHMC5883
CALIBRATION_NEGATIVE_HMC5883_EXEC = calibrationNegativeHMC5883
SEARCH_NORTH_EXEC = searchNorth

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target_hmc5883 target_hmc5983 target_calibration_positive_hmc5983  target_calibration_negative_hmc5983 target_search_north clean

# Le programme 1
target_hmc5883: $(TEST_HMC5883_EXEC)
target_hmc5983: $(TEST_HMC5983_EXEC)
target_calibration_positive_hmc5983: $(CALIBRATION_POSITIVE_HMC5883_EXEC)
target_calibration_negative_hmc5983: $(CALIBRATION_NEGATIVE_HMC5883_EXEC)
target_search_north: $(SEARCH_NORTH_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_HMC5883_EXEC): $(I2C_OBJECTS) $(HMC5883_OBJECTS) $(TEST_HMC5883_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_HMC5983_EXEC): $(I2C_OBJECTS) $(HMC5883_OBJECTS) $(HMC5983_OBJECTS) $(TEST_HMC5983_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(CALIBRATION_POSITIVE_HMC5883_EXEC): $(I2C_OBJECTS) $(HMC5883_OBJECTS) $(HMC5983_OBJECTS) $(CALIBRATION_POSITIVE_HMC5883_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(CALIBRATION_NEGATIVE_HMC5883_EXEC): $(I2C_OBJECTS) $(HMC5883_OBJECTS) $(HMC5983_OBJECTS) $(CALIBRATION_NEGATIVE_HMC5883_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(SEARCH_NORTH_EXEC): $(I2C_OBJECTS) $(HMC5883_OBJECTS) $(HMC5983_OBJECTS) $(GPIO_OBJECTS) $(STEPPER_OBJECTS) $(SEARCH_NORTH_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_HMC5883_EXEC)	
	@rm -f $(TEST_HMC5983_EXEC)	
	@rm -f $(CALIBRATION_POSITIVE_HMC5883_EXEC)	
	@rm -f $(CALIBRATION_NEGATIVE_HMC5883_EXEC)	
	@rm -f $(SEARCH_NORTH_EXEC)	
