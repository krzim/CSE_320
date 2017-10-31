proj06: proj06.support.o proj06.driver.o
		gcc -std=c99 proj06.support.o proj06.driver.o -o proj06

proj06.support.o: proj06.support.c
		gcc -std=c99 -Wall -c proj06.support.c

proj06.driver.o: proj06.driver.c
		gcc -std=c99 -Wall -c proj06.driver.c
