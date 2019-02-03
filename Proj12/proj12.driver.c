#include <stdio.h>
#include "/user/cse320/Projects/project12.support.h"

int main()
{
	//Branch Cond Tests
	
	//equal tests
	printf("\nBranch equal tests\n");
	printf("PC: %08x\n",update(0x0, 0x0AFFFFFE, 0x40000000));//pass
	printf("PC: %08x\n",update(0x0, 0x0AFFFFFE, 0x00000000));//fail	
	
	//not equal tests
	printf("\nBranch not equal tests\n");
	printf("PC: %08x\n",update(0x4, 0x1AFFFFFD, 0x00000000));//pass
	printf("PC: %08x\n",update(0x4, 0x1AFFFFFD, 0x40000000));//fail
	
	//carry tests
	printf("\nBranch carry tests\n");	
	printf("PC: %08x\n",update(0x8, 0x2AFFFFFC, 0x20000000));//pass
	printf("PC: %08x\n",update(0x8, 0x2AFFFFFC, 0x00000000));//fail
	
	//not carry tests
	printf("\nBranch not carry tests\n");
	printf("PC: %08x\n",update(0xc, 0x3AFFFFFB, 0x00000000));//pass
	printf("PC: %08x\n",update(0xc, 0x3AFFFFFB, 0x20000000));//fail
	
	//negative tests
	printf("\nBranch negative tests\n");
	printf("PC: %08x\n",update(0x10, 0x4AFFFFFA, 0x80000000));//pass
	printf("PC: %08x\n",update(0x10, 0x4AFFFFFA, 0x00000000));//fail
	
	//not negative tests
	printf("\nBranch not negative tests\n");
	printf("PC: %08x\n",update(0x14, 0x5AFFFFF9, 0x00000000));//pass
	printf("PC: %08x\n",update(0x14, 0x5AFFFFF9, 0x80000000));//fail
	
	//overflow tests
	printf("\nBranch overflow tests\n");
	printf("PC: %08x\n",update(0x18, 0x6AFFFFF8, 0x10000000));//pass
	printf("PC: %08x\n",update(0x18, 0x6AFFFFF8, 0x00000000));//fail
	
	//not overflow tests
	printf("\nBranch not overflow tests\n");
	printf("PC: %08x\n",update(0x1c, 0x7AFFFFF7, 0x00000000));//pass
	printf("PC: %08x\n",update(0x1c, 0x7AFFFFF7, 0x10000000));//fail
	
	//unsigned greater than tests
	printf("\nBranch unsigned greather than tests\n");
	printf("PC: %08x\n",update(0x20, 0x8AFFFFF6, 0x20000000));//pass
	printf("PC: %08x\n",update(0x20, 0x8AFFFFF6, 0xa0000000));//pass
	printf("PC: %08x\n",update(0x20, 0x8AFFFFF6, 0xb0000000));//pass
	printf("PC: %08x\n",update(0x20, 0x8AFFFFF6, 0x30000000));//pass
	printf("PC: %08x\n",update(0x20, 0x8AFFFFF6, 0x00000000));//fail
	
	//unsigned less than or equal to tests
	printf("\nBranch unsigned less than or equal to tests\n");
	printf("PC: %08x\n",update(0x24, 0x9AFFFFF5, 0x0000000));//pass
	printf("PC: %08x\n",update(0x24, 0x9AFFFFF5, 0x40000000));//pass
	printf("PC: %08x\n",update(0x24, 0x9AFFFFF5, 0xc0000000));//pass
	printf("PC: %08x\n",update(0x24, 0x9AFFFFF5, 0xb0000000));//fail
	printf("PC: %08x\n",update(0x24, 0x9AFFFFF5, 0x20000000));//fail

	
	
	//signed greater than or equal to tests
	printf("\nBranch signed greater than or equal to tests\n");
	printf("PC: %08x\n",update(0x28, 0xAAFFFFF4, 0x00000000));//pass
	printf("PC: %08x\n",update(0x28, 0xAAFFFFF4, 0x90000000));//pass
	printf("PC: %08x\n",update(0x28, 0xAAFFFFF4, 0x10000000));//fail
	
	//signed less than tests
	printf("\nBranch signed less than tests\n");
	printf("PC: %08x\n",update(0x2c, 0xBAFFFFF3, 0x10000000));//pass
	printf("PC: %08x\n",update(0x2c, 0xBAFFFFF3, 0x80000000));//pass
	printf("PC: %08x\n",update(0x2c, 0xBAFFFFF3, 0x00000000));//fail
	
	//signed greater than tests
	printf("\nBranch signed greater than tests\n");
	printf("PC: %08x\n",update(0x30, 0xCAFFFFF2, 0x00000000));//pass
	printf("PC: %08x\n",update(0x30, 0xCAFFFFF2, 0x90000000));//pass
	printf("PC: %08x\n",update(0x30, 0xCAFFFFF2, 0x40000000));//fail
	
	//signed less than or equal to tests
	printf("\nBranch signed less than or equal to tests\n");
	printf("PC: %08x\n",update(0x34, 0xDAFFFFF1, 0x40000000));//pass
	printf("PC: %08x\n",update(0x34, 0xDAFFFFF1, 0x80000000));//pass
	printf("PC: %08x\n",update(0x34, 0xDAFFFFF1, 0x00000000));//fail
	
	//always tests
	printf("\nBranch always tests\n");
	printf("PC: %08x\n",update(0x38, 0xEAFFFFF0, 0x00000000));//pass
	printf("PC: %08x\n",update(0x3c, 0xEA000001, 0x00000000));//pass
	printf("PC: %08x\n",update(0x40, 0xEA000003, 0x00000000));//pass
	
	//illegal tests
	printf("\nBranch illegal tests\n");
	printf("PC: %08x\n",update(0x3c, 0xFAFFFFFE, 0x00000000));//error
	printf("PC: %08x\n",update(0x3c, 0xFAFFFFFE, 0x00000000));//error
	printf("PC: %08x\n",update(0x3c, 0xF8FFFFFE, 0x00000000));//error
	
	
	
	//Data Processing tests
	printf("\nData Processing tests\n");	
	printf("PC: %08x\n",update(0x44, 0xE0800001, 0x00000000));//pass
	
	//Data Movement tests
	printf("\nData Movement tests\n");	
	printf("PC: %08x\n",update(0x48, 0xE5910000, 0x00000000));//pass
	
	return 0;
}

		//Sample assembly code for branch instructions

		//1              	label:
		//2 0000 0AFFFFFE 			beq		label
		//3 0004 1AFFFFFD 			bne		label
		//4 0008 2AFFFFFC 			bcs		label
		//5 000c 3AFFFFFB 			bcc		label
		//6 0010 4AFFFFFA 			bmi		label
		//7 0014 5AFFFFF9 			bpl		label
		//8 0018 6AFFFFF8 			bvs		label
		//9 001c 7AFFFFF7 			bvc		label
		//10 0020 8AFFFFF6 			bhi		label
		//11 0024 9AFFFFF5 			bls		label
		//12 0028 AAFFFFF4 			bge		label
		//13 002c BAFFFFF3 			blt		label
		//14 0030 CAFFFFF2 			bgt		label
		//15 0034 DAFFFFF1 			ble		label
		//16 0038 EAFFFFF0 			b		label
		//17 003c EA000001 			b		ahead
		//18 0040 EA000003 			b		far
		//19 0044 E0800001 			add		r0, r1
		//20              	ahead:
		//21 0048 E5910000 			ldr		r0, [r1]
		//22 004c E1A00001 			mov		r0, r1
		//23 0050 01A00001 			moveq	r0, r1
		//24              	far:
		//25 0054 05910000 			ldreq	r0, [r1]

