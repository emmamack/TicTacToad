main: main.c 20q.o tictactoe.o helpers.o
	gcc -o main main.c 20q.o tictactoe.o helpers.o

helpers.o: helpers.c helpers.h
	gcc -c helpers.c

20q.o: 20q.c games.h
	gcc -c 20q.c

tictactoe.o: tictactoe.c games.h
	gcc -c tictactoe.c