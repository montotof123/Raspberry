# Compilateur, flags et librairies
CC = g++
CXXFLAGS=-std=c++11
EXTRA_LIBS = -lwiringPi

# Groupes de fichiers sources
PCF8591_SOURCES = GestionPCF8591.cpp
GPIO_SOURCES = GestionPin.cpp GestionPinGPIO.cpp
TEST_PCF8591_SOURCES = tstPCF8591.cpp
TEST_DETFIRE_SOURCES = tstDetFire.cpp
TEST_DETSON_SOURCES = tstDetSon.cpp
TEST_JOYSTICK_SOURCES = tstJoystick.cpp
TEST_BUZZER_SOURCES = tstBuzzer.cpp
TEST_INTER_SOURCES = tstInter.cpp
TEST_TIMESIGIR_SOURCES = tstTimeSigIR.cpp
DECODE_TELECOMMANDE_SOURCES = decTelecommande.cpp

# Groupes de fichiers objets générés (un pour chaque fichier source)
PCF8591_OBJECTS = $(PCF8591_SOURCES:.cpp=.o)
GPIO_OBJECTS = $(GPIO_SOURCES:.cpp=.o)
TEST_PCF8591_OBJECTS = $(TEST_PCF8591_SOURCES:.cpp=.o)
TEST_DETFIRE_OBJECTS = $(TEST_DETFIRE_SOURCES:.cpp=.o)
TEST_DETSON_OBJECTS = $(TEST_DETSON_SOURCES:.cpp=.o)
TEST_JOYSTICK_OBJECTS = $(TEST_JOYSTICK_SOURCES:.cpp=.o)
TEST_BUZZER_OBJECTS = $(TEST_BUZZER_SOURCES:.cpp=.o)
TEST_INTER_OBJECTS = $(TEST_INTER_SOURCES:.cpp=.o)
TEST_TIMESIGIR_OBJECTS = $(TEST_TIMESIGIR_SOURCES:.cpp=.o)
DECODE_TELECOMMANDE_OBJECTS = $(DECODE_TELECOMMANDE_SOURCES:.cpp=.o)

# Les programmes a générer
PCF8591_EXEC = tstPCF8591
DET_FIRE_EXEC = tstDetFire
DET_FUMEE_EXEC = tstDetFumee
DET_HALL_EXEC = tstHallEffect
DET_PLUIE_EXEC = tstDetPluie
DET_SON_EXEC = tstDetSon
JOYSTICK_EXEC = tstJoystick
BUZZER_EXEC = tstBuzzer
INTER_EXEC = tstInter
TIMESIGIR_EXEC = tstTimeSigIR
DECODE_TELECOMMANDE_EXEC = decTelecommande

# Cible particulière pour éviter des conflits de nom (inutile ici)
.PHONY: mrproper clean

# Cible par défaut si on demande seulement make
# Construit les programmes cibles et enlève les fichiers objets à la fin
all: target_pcf8591 target_detfire target_detfumee target_dethall target_detpluie target_detson target_joystick target_buzzer target_inter target_timesigir target_decTelecommande clean

# Le programme 1
target_pcf8591: $(PCF8591_EXEC)
target_detfire: $(DET_FIRE_EXEC)
target_detfumee: $(DET_FUMEE_EXEC)
target_dethall: $(DET_HALL_EXEC)
target_detpluie: $(DET_PLUIE_EXEC)
target_detson: $(DET_SON_EXEC)
target_joystick: $(JOYSTICK_EXEC)
target_buzzer: $(BUZZER_EXEC)
target_inter: $(INTER_EXEC)
target_timesigir: $(TIMESIGIR_EXEC)
target_decTelecommande: $(DECODE_TELECOMMANDE_EXEC)

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(PCF8591_EXEC): $(PCF8591_OBJECTS) $(TEST_PCF8591_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(DET_FIRE_EXEC): $(PCF8591_OBJECTS) $(GPIO_OBJECTS) $(TEST_DETFIRE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(DET_FUMEE_EXEC): $(PCF8591_OBJECTS) $(GPIO_OBJECTS) $(TEST_DETFIRE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(DET_HALL_EXEC): $(PCF8591_OBJECTS) $(GPIO_OBJECTS) $(TEST_DETFIRE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(DET_PLUIE_EXEC): $(PCF8591_OBJECTS) $(GPIO_OBJECTS) $(TEST_DETFIRE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(JOYSTICK_EXEC): $(PCF8591_OBJECTS) $(TEST_JOYSTICK_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(DET_SON_EXEC): $(PCF8591_OBJECTS) $(TEST_DETSON_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(BUZZER_EXEC): $(GPIO_OBJECTS) $(TEST_BUZZER_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(INTER_EXEC): $(GPIO_OBJECTS) $(TEST_INTER_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(TIMESIGIR_EXEC): $(GPIO_OBJECTS) $(TEST_TIMESIGIR_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Compilation du programme 1 $@ représente les fichiers objets et $^ le nom du programme
$(DECODE_TELECOMMANDE_EXEC): $(GPIO_OBJECTS) $(DECODE_TELECOMMANDE_OBJECTS)
	$(CC) $(CXXFLAGS) $(EXTRA_LIBS) -o $@ $^ 

# Suppression des fichiers objets si ils existent
clean:
	@rm -f *.o

# Suppression des fichiers objets et des programmes si ils existent
mrproper:
	@rm -f *.o
	@rm -f $(PCF8591_EXEC)	
	@rm -f $(DET_FIRE_EXEC)	
	@rm -f $(DET_FUMEE_EXEC)	
	@rm -f $(DET_HALL_EXEC)	
	@rm -f $(DET_PLUIE_EXEC)	
	@rm -f $(DET_SON_EXEC)	
	@rm -f $(JOYSTICK_EXEC)	
	@rm -f $(BUZZER_EXEC)	
	@rm -f $(INTER_EXEC)	
	@rm -f $(TIMESIGIR_EXEC)	
	@rm -f $(DECODE_TELECOMMANDE_EXEC)	
