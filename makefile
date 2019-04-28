CC=g++
V=-std=c++11
SRC=src/
BIN=bin/
CMAIN=main.cpp
CFILES=$(SRC)Environment.cpp $(SRC)ProcessingUnit.cpp $(SRC)Clock.cpp $(SRC)ILet.cpp $(SRC)Operation.cpp $(SRC)ManyCoreArch.cpp $(SRC)CacheMemory.cpp $(SRC)RandomAccessMemory.cpp $(SRC)ResourceAdmin.cpp $(SRC)Monitor.cpp $(SRC)SequenceIlet.cpp
CFLAGS=-Wall -lpthread -DNDEBUG -DTEST
APP=invasive_simulator

$(APP):
	$(CC) -o $(BIN)$(APP) $(CFILES) $(V) $(CMAIN) $(CFLAGS)
clean:
	rm $(APP)
