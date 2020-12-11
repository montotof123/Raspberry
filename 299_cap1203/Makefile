# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++17
EXTRA_LIBS = -lrt -lpthread -lpigpio

# Groupes de fichiers sources
I2C_SOURCES = GestionI2C.cpp
CAP1203_SOURCES = GestionCAP1203.cpp
TEST_ACT_SOURCES = tstCAP1203Act.cpp
TEST_ACT_INT_SOURCES = tstCAP1203ActInt.cpp
TEST_MULT_INT_SOURCES = tstCAP1203MultInt.cpp
TEST_PWR_INT_SOURCES = tstCAP1203PwrInt.cpp
TEST_ACT_LOW_INT_SOURCES = tstCAP1203ActLowInt.cpp
TEST_ACT_MIN_SENS_INT_SOURCES = tstCAP1203ActMinSensInt.cpp
TEST_ACT_MAX_SENS_INT_SOURCES = tstCAP1203ActMaxSensInt.cpp
TEST_STBY_SOURCES = tstCAP1203Stby.cpp
LOGGER_SOURCES = Logger.cpp
BIG_AFF_SOURCES = GestionBigAffichage.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
I2C_OBJECTS = $(I2C_SOURCES:.cpp=.o)
CAP1203_OBJECTS = $(CAP1203_SOURCES:.cpp=.o)
TEST_ACT_OBJECTS = $(TEST_ACT_SOURCES:.cpp=.o)
TEST_ACT_INT_OBJECTS = $(TEST_ACT_INT_SOURCES:.cpp=.o)
TEST_MULT_INT_OBJECTS = $(TEST_MULT_INT_SOURCES:.cpp=.o)
TEST_PWR_INT_OBJECTS = $(TEST_PWR_INT_SOURCES:.cpp=.o)
TEST_ACT_MIN_SENS_INT_OBJECTS = $(TEST_ACT_MIN_SENS_INT_SOURCES:.cpp=.o)
TEST_ACT_MAX_SENS_INT_OBJECTS = $(TEST_ACT_MAX_SENS_INT_SOURCES:.cpp=.o)
TEST_ACT_LOW_INT_OBJECTS = $(TEST_ACT_LOW_INT_SOURCES:.cpp=.o)
TEST_STBY_OBJECTS = $(TEST_STBY_SOURCES:.cpp=.o)
LOGGER_OBJECTS = $(LOGGER_SOURCES:.cpp=.o)
BIG_AFF_OBJECTS = $(BIG_AFF_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)

# Les programmes a générer
TEST_ACT_EXEC = tstCAP1203Act
TEST_ACT_INT_EXEC = tstCAP1203ActInt
TEST_MULT_INT_EXEC = tstCAP1203MultInt
TEST_PWR_INT_EXEC = tstCAP1203PwrInt
TEST_ACT_MIN_SENS_INT_EXEC = tstCAP1203ActMinSensInt
TEST_ACT_MAX_SENS_INT_EXEC = tstCAP1203ActMaxSensInt
TEST_ACT_LOW_INT_EXEC = tstCAP1203ActLowInt
TEST_STBY_EXEC = tstCAP1203Stby

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les deux programmes cibles et enlève les fichiers objets à la fin
all: target_act target_mult_int target_pwr_int target_act_max_sens_int target_act_min_sens_int target_act_int target_act_low_int target_stby clean

# Le programme 1
target_act: $(TEST_ACT_EXEC)
target_act_int: $(TEST_ACT_INT_EXEC)
target_mult_int: $(TEST_MULT_INT_EXEC)
target_pwr_int: $(TEST_PWR_INT_EXEC)
target_act_max_sens_int: $(TEST_ACT_MAX_SENS_INT_EXEC)
target_act_min_sens_int: $(TEST_ACT_MIN_SENS_INT_EXEC)
target_act_low_int: $(TEST_ACT_LOW_INT_EXEC)
target_stby: $(TEST_STBY_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TEST_ACT_EXEC): $(TEST_ACT_OBJECTS) $(I2C_OBJECTS) $(CAP1203_OBJECTS) $(LOGGER_OBJECTS) 
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_ACT_INT_EXEC): $(TEST_ACT_INT_OBJECTS) $(I2C_OBJECTS) $(CAP1203_OBJECTS) $(LOGGER_OBJECTS) $(GPIO_SOURCES)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_MULT_INT_EXEC): $(TEST_MULT_INT_OBJECTS) $(I2C_OBJECTS) $(CAP1203_OBJECTS) $(LOGGER_OBJECTS) $(GPIO_SOURCES)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_PWR_INT_EXEC): $(TEST_PWR_INT_OBJECTS) $(I2C_OBJECTS) $(CAP1203_OBJECTS) $(LOGGER_OBJECTS) $(GPIO_SOURCES)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_ACT_MAX_SENS_INT_EXEC): $(TEST_ACT_MAX_SENS_INT_OBJECTS) $(I2C_OBJECTS) $(CAP1203_OBJECTS) $(LOGGER_OBJECTS) $(GPIO_SOURCES)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_ACT_MIN_SENS_INT_EXEC): $(TEST_ACT_MIN_SENS_INT_OBJECTS) $(I2C_OBJECTS) $(CAP1203_OBJECTS) $(LOGGER_OBJECTS) $(GPIO_SOURCES)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_ACT_LOW_INT_EXEC): $(TEST_ACT_LOW_INT_OBJECTS) $(I2C_OBJECTS) $(CAP1203_OBJECTS) $(LOGGER_OBJECTS) $(GPIO_SOURCES)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 
$(TEST_STBY_EXEC): $(TEST_STBY_OBJECTS) $(I2C_OBJECTS) $(CAP1203_OBJECTS) $(LOGGER_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(TEST_ACT_EXEC)	
	@rm -f $(TEST_ACT_INT_EXEC)	
	@rm -f $(TEST_MULT_INT_EXEC)	
	@rm -f $(TEST_PWR_INT_EXEC)	
	@rm -f $(TEST_ACT_MAX_SENS_INT_EXEC)	
	@rm -f $(TEST_ACT_MIN_SENS_INT_EXEC)	
	@rm -f $(TEST_ACT_LOW_INT_EXEC)	
	@rm -f $(TEST_STBY_EXEC)	
