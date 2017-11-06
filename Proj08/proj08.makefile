proj08:	proj08.main.o
		gcc proj08.main.o -o proj08
proj08.main.o:	proj08.main.s
		gcc -Wall -c proj08.main.s

clean:
		-rm -f proj08.main.o proj07
