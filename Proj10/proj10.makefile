proj10:	proj10.support.o /user/cse320/Projects/project10.driver.o
		gcc proj10.support.o /user/cse320/Projects/project10.driver.o -o proj10

proj10.support.o: proj10.support.s
		gcc -c -Wall proj10.support.s

clean:
		-rm -f proj10.support.o proj10
