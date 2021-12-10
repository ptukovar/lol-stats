all:
	gcc main.c fce.c head.h -o lol-elo -lm -fsanitize=address
exec:
	./lol-elo $g $n $o
clean:
	rm -rf ./lol-elo

