#include <stdio.h>
#include "/user/cse320/Projects/project09.support.h"


int negate( int N );
int absolute( int N );

int add( int A, int B );
int sub( int A, int B );
int mul( int A, int B );
int divide( int A, int B );
int remain( int A, int B );

int power( int N, int I );
int factorial( int N );

int main()
{
	int MAX = 0X7fffffff;
	int MIN = 0x80000000;
	
	printf("\n\n##########	Short Tests	##########\n");
	for(int i = -3; i < 4; i++)
	{
		printf("\nNeg(%d) = %d\n", i, negate(i));
		printf("Abs(%d) = %d\n", i, absolute(i));
		printf("Factorial(%d) = %d\n", i, factorial(i));
		printf("Power(%d, %d) = %d\n", i, i, power(i, i));
		printf("%d * %d = %d\n", i, i, mul(i, i));
	}
	
	//negation tests
	printf("\n\n##########	Negation Tests	##########\n");
	printf("\nNeg(%d) = %d\n", MIN, negate(MIN));
	printf("Neg(%d) = %d\n", MAX, negate(MAX));
	
	//absolute tests
	printf("\n\n##########	Absolute Value Tests	##########\n");
	printf("\nAbs(%d) = %d\n", MIN, absolute(MIN));
	printf("Abs(%d) = %d\n", MIN + 1, absolute(MIN + 1));
	printf("Abs(%d) = %d\n", MAX, absolute(MAX));
	printf("Abs(%d) = %d\n", 0, absolute(0));

	//add tests
	printf("\n\n##########	Addition Tests	##########\n");
	printf("\n%d + %d = %d\n", MAX, 1, add(MAX, 1));
	
	//sub tests
	printf("\n\n##########	Subtract Tests	##########\n");
	printf("\n%d - %d = %d\n", MIN, 1, sub(MIN, 1));
	printf("%d - %d = %d\n", 1, MIN, sub(1, MIN));
	
	//factorial tests
	printf("\n\n##########	Factorial Tests	##########\n");
	printf("\nFactorial(%d) = %d\n", 7, factorial(7));	
	printf("Factorial(%d) = %d\n", 13, factorial(13));
	printf("Factorial(%d) = %d\n", 15, factorial(15));
	printf("Factorial(%d) = %d\n", MIN, factorial(MIN));
	
	//power tests
	printf("\n\n##########	Power Tests	##########\n");
	printf("\nPower(%d, %d) = %d\n", 6, 4, power(6, 4));
	printf("Power(%d, %d) = %d\n", MAX, 2, power(MAX, 2));
	printf("Power(%d, %d) = %d\n", MAX, 0, power(MAX, 0));	
	printf("Power(%d, %d) = %d\n", MAX, 2, power(MIN, 2));
	printf("Power(%d, %d) = %d\n", MIN, 0, power(MIN, 0));
		
	//mul tests
	printf("\n##########	Multiply Tests	##########\n");
	printf("\n%d * %d = %d\n", 2, MAX, mul(2, MAX));
	printf("%d * %d = %d\n", 2, MIN, mul(2, MIN));
	printf("%d * %d = %d\n", 0, MAX, mul(0, MAX));
	printf("%d * %d = %d\n", 0, MIN, mul(0, MIN));
	printf("%d * %d = %d\n", 0, 6, mul(0, 6));
	
	//div tests
	printf("\n\n##########	Divide Tests	##########\n");
	printf("\n%d / %d = %d\n", 20, 2, divide(20, 2));
	printf("%d / %d = %d\n", 20, -2, divide(20, -2));	
	printf("%d / %d = %d\n", MAX, 2, divide(MAX, 2));	
	printf("%d / %d = %d\n", MAX, -2, divide(MAX, -2));
	printf("%d / %d = %d\n", MIN, 2, divide(MIN, 2));	
	printf("%d / %d = %d\n", MIN, -2, divide(MIN, -2));	
	printf("%d / %d = %d\n", MAX, MIN, divide(MAX, MIN));	
	printf("%d / %d = %d\n", MIN, MAX, divide(MIN, MAX));
	printf("%d / %d = %d\n", MIN, 0, divide(MIN, 0));	
	printf("%d / %d = %d\n", MIN, MIN, divide(MIN, MIN));
	printf("%d / %d = %d\n", MAX, MAX, divide(MAX, MAX));
	
	//remain tests
	printf("\n\n##########	Remain Tests	##########\n");
	printf("\n%d %% %d = %d\n", 10, 2, remain(10, 2));
	printf("%d %% %d = %d\n", 1, 2, remain(1, 2));
	printf("%d %% %d = %d\n", MAX, 2, remain(MAX, 2));
	printf("%d %% %d = %d\n", MIN, MAX, remain(MIN, MAX));
	printf("%d %% %d = %d\n", MAX, MIN, remain(MAX, MIN));
	printf("%d %% %d = %d\n", MIN, 2, remain(MIN, 2));
	printf("%d %% %d = %d\n", 51, 10, remain(51, 10));
	printf("%d %% %d = %d\n", -52, 10, remain(-52, 10));
	printf("%d %% %d = %d\n", 53, -10, remain(53, -10));
	printf("%d %% %d = %d\n", -54, -10, remain(-54, -10));
	
	return 0;
}
