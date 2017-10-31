#include <stdio.h>
#include "/user/cse320/Projects/project06.support.h"

int main(void)
{
    union sp_union prod;
    union sp_union flt1;
    union sp_union flt2;
    union sp_union actl;
    
    // Zero test against zero
    flt1.frep = 0;
    flt2.irep = 0;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // Zero test against denormal
    flt1.frep = 0;
    flt2.irep = 0x007ffff;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
	// Zero test against float
    flt1.frep = 0;
    flt2.frep = -1.5;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
	// inf test against negative float
    flt1.frep = INFINITY;
    flt2.frep = -1.5;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
	// inf test against positive float
    flt1.frep = INFINITY;
    flt2.frep = 1.5;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
	// inf test against zero
    flt1.frep = INFINITY;
    flt2.frep = -1.5;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
	// inf test against denormal
    flt1.frep = INFINITY;
    flt2.irep = 0x007ffff;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
	// nan test against denormal
    flt1.frep = NAN;
    flt2.irep = 0x007ffff;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);

	// nan test against positive float
    flt1.frep = NAN;
    flt2.frep = 1.5;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // nan test against positive float
    flt1.frep = NAN;
    flt2.frep = -1.5;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // nan test against inf
    flt1.frep = NAN;
    flt2.frep = INFINITY;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // denormal against denormal
    flt1.irep = 0x007ffff;
    flt2.irep = 0x007ffff;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // denormal against float
    flt1.irep = 0x007ffff;
    flt2.frep = 1.65;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // Float test against negative float
    flt1.frep = 195.12341234;
    flt2.frep = -1454.5;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // Float test against float
    flt1.frep = 123431341.1234;
    flt2.frep = 999.4314;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // Float less than one test against float greater than one
    flt1.frep = 0.003432;
    flt2.frep = 126634.56;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    // Float less than one test against float less than one
    flt1.frep = 0.0001234;
    flt2.frep = 0.0013043;
    prod.frep = mult(flt1.frep, flt2.frep);
    actl.frep = flt1.frep * flt2.frep;
	printf("flt1:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt1.frep, flt1.irep);
	printf("flt2:\n");
    printf( "Real: %f  Hex integer: %08x  \n", flt2.frep, flt2.irep);
	printf("Prod:\n");
    printf( "Real: %f  Hex integer: %08x  \n", prod.frep, prod.irep);  
    printf("Actual:\n");
    printf( "Real: %f  Hex integer: %08x  \n\n", actl.frep, actl.irep);
    
    return 0;

}
