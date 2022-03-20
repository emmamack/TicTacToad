main: main.c 20q.o tictactoe.o helpers.o game_chooser.o
	gcc -o gameserver main.c 20q.o tictactoe.o helpers.o game_chooser.o

helpers.o: helpers.c helpers.h
	gcc -c helpers.c

20q.o: 20q.c games.h
	gcc -c 20q.c

tictactoe.o: tictactoe.c games.h
	gcc -c tictactoe.c

game_chooser.o: game_chooser.c games.h helpers.h
	gcc -c game_chooser.c
