#CC=gcc
RM=rm -rf
CC=clang++-5.0
MK=mkdir
#CC=g++
OBJ_OPT=-v -std=c++11

BUILD_DIR = ./BUILD/

SRC=src/

#OPTION=-mllvm -sub -llvm -fla
JSON_OPTION=-DJSON_IS_AMALGAMATION -I$(SRC)
OPTION= -lpthread -std=c++11 $(JSON_OPTION)

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
	$(RM) $(BUILD_DIR)
	$(MK) $(BUILD_DIR)
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

	$(CC) $(OPTION) -o $(BUILD_DIR)/onion src/main.cpp $(SRC)$(J).cpp *.o
clean:
	$(RM) .$(BUILD_DIR)/*
	$(RM)  *.o
