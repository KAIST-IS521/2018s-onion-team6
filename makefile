
#CC=gcc
RM=rm
CC=clang++-5.0
OBJ_OPT=-stdlib=libc++

#OPTION=-mllvm -sub -llvm -fla

SRC=src/
H="heartbeat"
O="onion_messenger"
C="shell"
S="socket"
U="user_info"
P="pgp"
default :
	$(CC) $(OBJ_OPT) -c $(SRC)$(O).cpp
	$(CC) $(OBJ_OPT) -c $(SRC)$(P).cpp
	$(CC) $(OBJ_OPT) -c $(SRC)$(C).cpp
	$(CC) $(OBJ_OPT) -c $(SRC)$(S).cpp
	$(CC) $(OBJ_OPT) -c $(SRC)$(H).cpp
	$(CC) $(OBJ_OPT) -c $(SRC)$(U).cpp
	$(CC) $(OPTION) -o ./CLIENT/onion src/main.cpp $(H).o $(O).o $(P).o $(C).o $(S).o $(U).o



clean:
	$(RM) $(H).o $(O).o $(C).o $(S).o $(U).o $(P).o
