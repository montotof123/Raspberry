# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
MPR121_SOURCES = GestionMPR121.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
TEST_SOURCES_T12 = tstMPR121_T12.cpp
TEST_SOURCES_T12AUTO = tstMPR121_T12Auto.cpp
TEST_SOURCES_IRQ = tstMPR121_T8P4AutoIrq.cpp
TEST_SOURCES_TPROX = tstMPR121_TProx.cpp
TEST_SOURCES_GPIO = tstMPR121_GPIO.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
MPR121_OBJECTS = $(MPR121_SOURCES:.cpp=.o)
TEST_OBJECTS_T12 = $(TEST_SOURCES_T12:.cpp=.o)
TEST_OBJECTS_T12AUTO = $(TEST_SOURCES_T12AUTO:.cpp=.o)
TEST_OBJECTS_IRQ = $(TEST_SOURCES_IRQ:.cpp=.o)
TEST_OBJECTS_TPROX = $(TEST_SOURCES_TPROX:.cpp=.o)
TEST_OBJECTS_GPIO = $(TEST_SOURCES_GPIO:.cpp=.o)

# Les programmes a générer
TEST_EXEC_T12 = tstMPR121_T12
TEST_EXEC_T12AUTO = tstMPR121_T12Auto
TEST_EXEC_IRQ = tstMPR121_T8P4AutoIrq
TEST_EXEC_TPROX = tstMPR121_TProx
TEST_EXEC_GPIO = tstMPR121_GPIO

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target_t12auto target_t12 target_gpio target_irq target_tprox clean

# Le programme 1
target_t12: $(TEST_EXEC_T12)
target_irq: $(TEST_EXEC_IRQ)
target_t12auto: $(TEST_EXEC_T12AUTO)
target_tprox: $(TEST_EXEC_TPROX)
target_gpio: $(TEST_EXEC_GPIO)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_EXEC_T12): $(I2C_OBJECTS) $(MPR121_OBJECTS) $(GPIO_OBJECTS) $(TEST_OBJECTS_T12)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_EXEC_T12AUTO): $(I2C_OBJECTS) $(MPR121_OBJECTS) $(GPIO_OBJECTS) $(TEST_OBJECTS_T12AUTO)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_EXEC_IRQ): $(I2C_OBJECTS) $(MPR121_OBJECTS) $(GPIO_OBJECTS) $(TEST_OBJECTS_IRQ)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_EXEC_TPROX): $(I2C_OBJECTS) $(MPR121_OBJECTS) $(GPIO_OBJECTS) $(TEST_OBJECTS_TPROX)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_EXEC_GPIO): $(I2C_OBJECTS) $(MPR121_OBJECTS) $(GPIO_OBJECTS) $(TEST_OBJECTS_GPIO)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_EXEC_T12)	
	@rm -f $(TEST_EXEC_IRQ)	
	@rm -f $(TEST_EXEC_T12AUTO)	
	@rm -f $(TEST_EXEC_TPROX)	
	@rm -f $(TEST_EXEC_GPIO)	
