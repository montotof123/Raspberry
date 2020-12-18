# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++17
EXTRA_LIBS = -lrt -lpthread -lpigpio

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
MCP45HVX1_SOURCES = GestionMCP45HVX1.cpp
TEST_SOURCES = tstMCP45HVX1.cpp
ALIM_SOURCES = alimMCP45HVX1.cpp
CURVE_SOURCES = curveMCP45HVX1.cpp
LOGGER_SOURCES = Logger.cpp
INA219_SOURCES = GestionINA219.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
MCP45HVX1_OBJECTS = $(MCP45HVX1_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
ALIM_OBJECTS = $(ALIM_SOURCES:.cpp=.o)
CURVE_OBJECTS = $(CURVE_SOURCES:.cpp=.o)
LOGGER_OBJECTS = $(LOGGER_SOURCES:.cpp=.o)
INA219_OBJECTS = $(INA219_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_EXEC = tstMCP45HVX1
ALIM_EXEC = alimMCP45HVX1
CURVE_EXEC = curveMCP45HVX1

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target alim curve clean

# Le programme 1
target: $(TEST_EXEC)
alim: $(ALIM_EXEC)
curve: $(CURVE_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC): $(TEST_OBJECTS) $(I2C_OBJECTS) $(MCP45HVX1_OBJECTS) $(LOGGER_OBJECTS) 
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(ALIM_EXEC): $(ALIM_OBJECTS) $(I2C_OBJECTS) $(MCP45HVX1_OBJECTS) $(LOGGER_OBJECTS) $(INA219_OBJECTS) 
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(CURVE_EXEC): $(CURVE_OBJECTS) $(I2C_OBJECTS) $(MCP45HVX1_OBJECTS) $(LOGGER_OBJECTS) $(INA219_OBJECTS) 
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC)	
	@rm -f $(ALIM_EXEC)	
	@rm -f $(CURVE_EXEC)	
