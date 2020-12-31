# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++17
EXTRA_LIBS = -lrt -lpthread -lpigpio

# Groupes de fichiers sources
SPI_SOURCES = GestionSPI.cpp
I2C_SOURCES = GestionI2C.cpp
MAX7219_SOURCES = GestionMAX7219.cpp
MATRIX_SOURCES = GestionMatrix.cpp
DS1307_SOURCES = GestionDS1307.cpp
TEST_SOURCES = tstMAX7219.cpp
TEST_MATRIX_SOURCES = tstMatrix.cpp
HORLOGE_SOURCES = horloge.cpp
LOGGER_SOURCES = Logger.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
SPI_OBJECTS = $(SPI_SOURCES:.cpp=.o)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
MAX7219_OBJECTS = $(MAX7219_SOURCES:.cpp=.o)
MATRIX_OBJECTS = $(MATRIX_SOURCES:.cpp=.o)
DS1307_OBJECTS = $(DS1307_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_MATRIX_OBJECTS = $(TEST_MATRIX_SOURCES:.cpp=.o)
HORLOGE_OBJECTS = $(HORLOGE_SOURCES:.cpp=.o)
LOGGER_OBJECTS = $(LOGGER_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstMAX7219
TEST_MATRIX_EXEC = tstMatrix
HORLOGE_EXEC = horloge

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target target_matrix horloge clean

# Le programme
target: $(TEST_EXEC)
target_matrix: $(TEST_MATRIX_EXEC)
horloge: $(HORLOGE_EXEC)

# Compilation du programme $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(TEST_OBJECTS) $(SPI_OBJECTS) $(MAX7219_OBJECTS) $(LOGGER_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme $@ représente les fichiers objets et $^ le nom du programme
$(TEST_MATRIX_EXEC): $(TEST_MATRIX_OBJECTS) $(SPI_OBJECTS) $(MAX7219_OBJECTS) $(LOGGER_OBJECTS) $(MATRIX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme $@ représente les fichiers objets et $^ le nom du programme
$(HORLOGE_EXEC): $(HORLOGE_OBJECTS) $(SPI_OBJECTS) $(I2C_OBJECTS) $(MAX7219_OBJECTS) $(DS1307_OBJECTS) $(LOGGER_OBJECTS) $(MATRIX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
	@rm -f $(TEST_MATRIX_EXEC)	
	@rm -f $(HORLOGE_EXEC)	
