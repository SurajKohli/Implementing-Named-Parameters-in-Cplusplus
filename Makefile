CC=g++ -std=c++14
CFLAGS=-Iinclude/ -I/usr/include/boost
OBJ=-c
OUT=-o

all : obj/matchfunctions.o obj/classattributes.o obj/functiondefinitions.o obj/insertparams.o obj/functionattributes.o obj/symboltable.o obj/main_final.o 
	$(CC) obj/matchfunctions.o obj/classattributes.o obj/functiondefinitions.o obj/insertparams.o obj/functionattributes.o obj/symboltable.o obj/main_final.o $(CFLAGS) $(OUT) bin/cnp
obj/main_final.o : src/main_final.cpp src/functiondefinitions.cpp include/functiondefinitions.hpp src/matchfunctions.cpp include/matchfunctions.hpp
	$(CC) src/main_final.cpp $(CFLAGS) $(OBJ) $(OUT) obj/main_final.o
obj/symboltable.o : src/symboltable.cpp include/symboltable.hpp src/functionattributes.cpp include/functionattributes.hpp src/classattributes.cpp include/classattributes.hpp
	$(CC) src/symboltable.cpp $(CFLAGS) $(OBJ) $(OUT) obj/symboltable.o
obj/functiondefinitions.o : src/functiondefinitions.cpp include/functiondefinitions.hpp src/insertparams.cpp include/insertparams.hpp src/functionattributes.cpp include/functionattributes.hpp src/matchfunctions.cpp include/matchfunctions.hpp
	$(CC) src/functiondefinitions.cpp $(CFLAGS) $(OBJ) $(OUT) obj/functiondefinitions.o
obj/matchfunctions.o : src/matchfunctions.cpp include/matchfunctions.hpp
	$(CC) src/matchfunctions.cpp $(CFLAGS) $(OBJ) $(OUT) obj/matchfunctions.o
obj/insertparams.o : src/functionattributes.cpp include/functionattributes.hpp src/insertparams.cpp include/insertparams.hpp
	$(CC) src/insertparams.cpp $(CFLAGS) $(OBJ) $(OUT) obj/insertparams.o
obj/classattributes.o : src/classattributes.cpp include/classattributes.hpp src/functionattributes.cpp include/functionattributes.hpp
	$(CC) src/classattributes.cpp $(CFLAGS) $(OBJ) $(OUT) obj/classattributes.o
obj/functionattributes.o : src/functionattributes.cpp include/functionattributes.hpp
	$(CC) src/functionattributes.cpp $(CFLAGS) $(OBJ) $(OUT) obj/functionattributes.o

clean : 
	rm -rf obj/*
