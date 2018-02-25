CC=g++
CFLAGS=-std=c++11
EXTRA_LIBS = -lbcm2835 -lwiringPi 
DIR_OBJ=obj/
EXEC=Read
EXECIRQ=ReadIrq
 
all: $(EXEC) $(EXECIRQ) clean
 
Read: MFRC522.o Read.o GestionPin.o GestionPinGPIO.o
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)
	
ReadIrq: MFRC522.o ReadIrq.o GestionPin.o GestionPinGPIO.o
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)
 
%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(EXTRA_LIBS)
	
clean:
	@rm -f *.o
