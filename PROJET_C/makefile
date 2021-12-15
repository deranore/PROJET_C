OBJS	= projet.o AND1.o BUFFER1.o COMB.o decoupage.o GATE.o MUX1.o NAND1.o NET.o NOR1.o OR1.o SIMULATEUR.o XNOR1.o XOR1.o NOT1.o
SOURCE	= projet.cpp AND1.cpp BUFFER1.cpp COMB.cpp decoupage.cpp GATE.cpp MUX1.cpp NAND1.cpp NET.cpp NOR1.cpp OR1.cpp SIMULATEUR.cpp XNOR1.cpp XOR1.cpp NOT1.cpp
HEADER	= AND1.h BUFFER1.h COMB.h DECOUPAGE.h GATE.h MUX1.h NAND1.h NET.h NOR1.h OR1.h SIMULATEUR.h XNOR1.h XOR1.h NOT1.h
OUT	= projet
CC	 = g++
FLAGS	 = --std=c++11 -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

projet.o: projet.cpp
	$(CC) $(FLAGS) projet.cpp

AND1.o: AND1.cpp
	$(CC) $(FLAGS) AND1.cpp

BUFFER1.o: BUFFER1.cpp
	$(CC) $(FLAGS) BUFFER1.cpp

COMB.o: COMB.cpp
	$(CC) $(FLAGS) COMB.cpp

decoupage.o: decoupage.cpp
	$(CC) $(FLAGS) decoupage.cpp

GATE.o: GATE.cpp
	$(CC) $(FLAGS) GATE.cpp

MUX1.o: MUX1.cpp
	$(CC) $(FLAGS) MUX1.cpp

NAND1.o: NAND1.cpp
	$(CC) $(FLAGS) NAND1.cpp

NET.o: NET.cpp
	$(CC) $(FLAGS) NET.cpp

NOR1.o: NOR1.cpp
	$(CC) $(FLAGS) NOR1.cpp

OR1.o: OR1.cpp
	$(CC) $(FLAGS) OR1.cpp

SIMULATEUR.o: SIMULATEUR.cpp
	$(CC) $(FLAGS) SIMULATEUR.cpp

XNOR1.o: XNOR1.cpp
	$(CC) $(FLAGS) XNOR1.cpp

XOR1.o: XOR1.cpp
	$(CC) $(FLAGS) XOR1.cpp

NOT1.o: NOT1.cpp
	$(CC) $(FLAGS) NOT1.cpp


clean:
	rm -f $(OBJS) $(OUT)
