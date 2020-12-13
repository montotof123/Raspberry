# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++17
EXTRA_LIBS = -lrt -lpthread -lpigpio

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
MCP3424_SOURCES = GestionMCP3424.cpp
TEST_SOURCES = tstMCP3424.cpp
LOGGER_SOURCES = Logger.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
MCP3424_OBJECTS = $(MCP3424_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
LOGGER_OBJECTS = $(LOGGER_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstMCP3424

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target clean

# Le programme 1
target: $(TEST_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(TEST_OBJECTS) $(I2C_OBJECTS) $(MCP3424_OBJECTS) $(LOGGER_OBJECTS) 
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
