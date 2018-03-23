#CC=gcc
RM=rm
CC=clang++-5.0
#CC=g++
OBJ_OPT=-v -std=c++11

SRC=src/

OPTION= -lpthread -std=c++11
#OPTION=-mllvm -sub -llvm -fla
JSON_OPTION=-DJSON_IS_AMALGAMATION -I$(SRC)

H="heartbeat"
O="onion_messenger"
C="shell"
S="socket"
U="user_info"
P="pgp"
J="jsoncpp"
default :
	$(CC) $(OBJ_OPT) -c $(SRC)$(O).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(P).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(C).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(S).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(U).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(H).cpp $(JSON_OPTION)

	$(CC) $(OPTION) -o ./CLIENT/onion src/main.cpp $(H).o $(O).o $(P).o $(C).o $(S).o $(U).o $(SRC)$(J).cpp $(JSON_OPTION)


clean:
	$(RM) ./CLIENT/*
	$(RM)  $(H).o $(O).o $(C).o $(S).o $(U).o $(P).o
