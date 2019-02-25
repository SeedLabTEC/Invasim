CC=g++
V=-std=c++11
SRC=src/
BIN=bin/
CMAIN=main.cpp
CFILES=
CFLAGS=-Wall -lpthread
APP=invasive_simulator

$(APP):
	$(CC) -o $(BIN)$(APP) $(CFILES) $(V) $(CMAIN) $(CFLAGS)
clean:
	rm $(APP)