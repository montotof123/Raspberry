# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
MCP41XXX_SOURCES = GestionMCP41xxx.cpp
MCP41010_SOURCES = GestionMCP41010.cpp
MCP41050_SOURCES = GestionMCP41050.cpp
MCP41100_SOURCES = GestionMCP41100.cpp
MCP42XXX_SOURCES = GestionMCP42xxx.cpp
MCP42010_SOURCES = GestionMCP42010.cpp
MCP42050_SOURCES = GestionMCP42050.cpp
MCP42100_SOURCES = GestionMCP42100.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
SPI_SOURCES = GestionSPI16.cpp
TEST_MCP41010_SOURCES = tstGestion41010.cpp
TEST_MCP41050_SOURCES = tstGestion41050.cpp
TEST_MCP41100_SOURCES = tstGestion41100.cpp
TEST_MCP42010_SOURCES = tstGestion42010.cpp
TEST_MCP42050_SOURCES = tstGestion42050.cpp
TEST_MCP42100_SOURCES = tstGestion42100.cpp
ALIMPROG_SOURCES = alimProg.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
MCP41XXX_OBJECTS = $(MCP41XXX_SOURCES:.cpp=.o)
MCP41010_OBJECTS = $(MCP41010_SOURCES:.cpp=.o)
MCP41050_OBJECTS = $(MCP41050_SOURCES:.cpp=.o)
MCP41100_OBJECTS = $(MCP41100_SOURCES:.cpp=.o)
MCP42XXX_OBJECTS = $(MCP42XXX_SOURCES:.cpp=.o)
MCP42010_OBJECTS = $(MCP42010_SOURCES:.cpp=.o)
MCP42050_OBJECTS = $(MCP42050_SOURCES:.cpp=.o)
MCP42100_OBJECTS = $(MCP42100_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
SPI_OBJECTS = $(SPI_SOURCES:.cpp=.o)
TEST_MCP41010_OBJECTS = $(TEST_MCP41010_SOURCES:.cpp=.o)
TEST_MCP41050_OBJECTS = $(TEST_MCP41050_SOURCES:.cpp=.o)
TEST_MCP41100_OBJECTS = $(TEST_MCP41100_SOURCES:.cpp=.o)
TEST_MCP42010_OBJECTS = $(TEST_MCP42010_SOURCES:.cpp=.o)
TEST_MCP42050_OBJECTS = $(TEST_MCP42050_SOURCES:.cpp=.o)
TEST_MCP42100_OBJECTS = $(TEST_MCP42100_SOURCES:.cpp=.o)
ALIMPROG_OBJECTS = $(ALIMPROG_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_MCP41010_EXEC = tstGestion41010
TEST_MCP41050_EXEC = tstGestion41050
TEST_MCP41100_EXEC = tstGestion41100
TEST_MCP42010_EXEC = tstGestion42010
TEST_MCP42050_EXEC = tstGestion42050
TEST_MCP42100_EXEC = tstGestion42100
ALIMPROG_EXEC = alimProg

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target_mcp41010 target_mcp41050 target_mcp41100 target_mcp42010 target_mcp42050 target_mcp42100 target_alimprog clean

# Le programme 1
target_mcp41010: $(TEST_MCP41010_EXEC)
target_mcp41050: $(TEST_MCP41050_EXEC)
target_mcp41100: $(TEST_MCP41100_EXEC)
target_mcp42010: $(TEST_MCP42010_EXEC)
target_mcp42050: $(TEST_MCP42050_EXEC)
target_mcp42100: $(TEST_MCP42100_EXEC)
target_alimprog: $(ALIMPROG_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_MCP41010_EXEC): $(TEST_MCP41010_OBJECTS) $(SPI_OBJECTS) $(MCP41010_OBJECTS) $(MCP41XXX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_MCP41050_EXEC): $(TEST_MCP41050_OBJECTS) $(SPI_OBJECTS) $(MCP41050_OBJECTS) $(MCP41XXX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_MCP41100_EXEC): $(TEST_MCP41100_OBJECTS) $(SPI_OBJECTS) $(MCP41100_OBJECTS) $(MCP41XXX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_MCP42010_EXEC): $(TEST_MCP42010_OBJECTS) $(GPIO_OBJECTS) $(SPI_OBJECTS) $(MCP42010_OBJECTS) $(MCP42XXX_OBJECTS) $(MCP41XXX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_MCP42050_EXEC): $(TEST_MCP42050_OBJECTS) $(GPIO_OBJECTS) $(SPI_OBJECTS) $(MCP42050_OBJECTS) $(MCP42XXX_OBJECTS) $(MCP41XXX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_MCP42100_EXEC): $(TEST_MCP42100_OBJECTS) $(GPIO_OBJECTS) $(SPI_OBJECTS) $(MCP42100_OBJECTS) $(MCP42XXX_OBJECTS) $(MCP41XXX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(ALIMPROG_EXEC): $(ALIMPROG_OBJECTS) $(SPI_OBJECTS) $(MCP41010_OBJECTS) $(MCP41XXX_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_MCP41010_EXEC)	
	@rm -f $(TEST_MCP41050_EXEC)	
	@rm -f $(TEST_MCP41100_EXEC)	
	@rm -f $(TEST_MCP42010_EXEC)	
	@rm -f $(TEST_MCP42050_EXEC)	
	@rm -f $(TEST_MCP42100_EXEC)	
	@rm -f $(ALIMPROG_EXEC)	
