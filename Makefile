# Project: League of Legends ELO rating
# Author:  Marek Pukowiec
# Date:    12/10/2021
all:
	gcc main.c fce.c head.h -o lol-elo -lm -fsanitize=address
exec:
	./lol-elo $g $n $o
clean:
	rm -rf ./lol-elo

