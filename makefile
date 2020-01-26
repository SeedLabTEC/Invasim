CC=g++
V=-std=c++11
SRC=src/
BIN=bin/
LIBS=libs/cpp/
CMAIN=main.cpp
CFILES=$(SRC)Environment.cpp $(SRC)ProcessingUnit.cpp $(SRC)Clock.cpp $(SRC)ILet.cpp $(SRC)Operation.cpp $(SRC)ManyCoreArch.cpp $(SRC)CacheMemory.cpp $(SRC)RandomAccessMemory.cpp $(SRC)ResourceAdmin.cpp $(SRC)Monitor.cpp $(SRC)SequenceIlet.cpp $(SRC)InterconnectionNetwork.cpp $(SRC)StateMachineMSIO.cpp $(SRC)CacheController.cpp  
CFLAGS=-Wall -lpthread -DNDEBUG
APP=invasive_simulator

$(APP):
	$(CC) -o $(BIN)$(APP) $(CFILES) $(V) $(CMAIN) $(CFLAGS)
clean:
	rm $(APP)
