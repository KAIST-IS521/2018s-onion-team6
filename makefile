#CC=gcc
RM=rm
CC=clang++-5.0
MK=mkdir
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
SS="serversocket"
SA="socketaddress"
TA="clientsocket"
MS="msgserver"
MC="msgclient"
default :
	$(CC) $(OBJ_OPT) -c $(SRC)$(O).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(P).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(C).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(S).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(U).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(H).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(SS).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(SA).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(TA).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(MS).cpp $(JSON_OPTION)
	$(CC) $(OBJ_OPT) -c $(SRC)$(MC).cpp $(JSON_OPTION)

	$(CC) $(OPTION) -o ./CLIENT/onion src/main.cpp $(H).o $(O).o $(P).o $(C).o $(S).o $(U).o $(SRC)$(J).cpp $(SS).o $(SA).o $(TA).o $(MS).o $(MC).o  $(JSON_OPTION)


clean:
	$(RM) ./CLIENT/*
	$(RM)  *.o
