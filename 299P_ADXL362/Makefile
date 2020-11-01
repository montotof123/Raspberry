# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++17
EXTRA_LIBS = -lrt -lpthread -lpigpio

# Groupes de fichiers sources
SPI_SOURCES = GestionSPI.cpp
ADXL362_SOURCES = GestionADXL362.cpp
TEST_SOURCES = tstADXL362.cpp
LOGGER_SOURCES = Logger.cpp
BIG_AFF_SOURCES = GestionBigAffichage.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
TEST_INT_SOURCES = tstIntADXL362.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
SPI_OBJECTS = $(SPI_SOURCES:.cpp=.o)
ADXL362_OBJECTS = $(ADXL362_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
LOGGER_OBJECTS = $(LOGGER_SOURCES:.cpp=.o)
BIG_AFF_OBJECTS = $(BIG_AFF_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
TEST_INT_OBJECTS = $(TEST_INT_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstADXL362
TEST_INT_EXEC = tstIntADXL362

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target target_int clean

# Le programme 1
target: $(TEST_EXEC)
target_int: $(TEST_INT_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(TEST_OBJECTS) $(SPI_OBJECTS) $(ADXL362_OBJECTS) $(LOGGER_OBJECTS) $(BIG_AFF_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

$(TEST_INT_EXEC): $(TEST_INT_OBJECTS) $(SPI_OBJECTS) $(ADXL362_OBJECTS) $(LOGGER_OBJECTS) $(GPIO_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
	@rm -f $(TEST_INT_EXEC)	
