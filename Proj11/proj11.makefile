proj11:	proj11.support.o /user/cse320/Projects/project11.driver.o 
		gcc proj11.support.o /user/cse320/Projects/project11.driver.o -o proj11

proj11.support.o: proj11.support.s
		gcc -c -Wall -march=native proj11.support.s

clean:
		-rm -f proj11.support.o proj11
