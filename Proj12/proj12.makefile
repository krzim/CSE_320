proj12: proj12.driver.o proj12.support.o
		gcc -std=c99 proj12.driver.o proj12.support.o -o proj12

proj12.support.o: proj12.support.c
		gcc -std=c99 -c proj12.support.c

proj12.driver.o: proj12.driver.c 
		gcc -std=c99 -c proj12.driver.c

clean:
	-rm -f proj12.driver.o proj12.support.o proj12
