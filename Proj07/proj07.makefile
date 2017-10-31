proj07: proj07.support.o /user/cse320/Projects/project07.driver.o
		gcc -std=c99 proj07.support.o /user/cse320/Projects/project07.driver.o -o proj07

proj07.support.o: proj07.support.c
		gcc -std=c99 -Wall -c proj07.support.c

clean:
		-rm -f proj07.support.o proj07
