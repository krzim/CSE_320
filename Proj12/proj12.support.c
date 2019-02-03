#include "/user/cse320/Projects/project12.support.h"

unsigned OP_MASK = 0x0c000000;
unsigned COND_MASK = 0xf0000000;
unsigned SIMM24_MASK = 0x00ffffff;

unsigned sign_extend(unsigned);

unsigned sign_extend(unsigned simm24)
{
	unsigned sign = simm24 & 0x00800000;
	if(sign)
	{
		return (int)(simm24 + 0xff000000);  //cast as signed
	}
	return simm24;
}

unsigned update(unsigned PC, unsigned IR, unsigned CPSR)
{
	unsigned simm24 = IR & SIMM24_MASK;
	unsigned op = IR & OP_MASK;
	unsigned cond_IR = (IR & COND_MASK) >> 28;
	unsigned NZCV = (CPSR & COND_MASK) >> 28;
	unsigned cond_flag = 0;
	
	switch(cond_IR)
	{
		case 0x0:  //equal
			if(NZCV & 4) // Z set
			{
				cond_flag = 1;
			}
		break;
		
		case 0x1:  //not equal
			if(~NZCV & 4) // Z not set
			{
				cond_flag = 1;
			}
		break;
		
		case 0x2:  //carry
			if(NZCV & 2) // C set
			{
				cond_flag = 1;
			}
		break;
		
		case 0x3:  //not carry
			if(~NZCV & 2) // C not set
			{
				cond_flag = 1;
			}
		break;
		
		case 0x4:  //negative"
			if(NZCV & 8) // N set
			{
				cond_flag = 1;
			}
		break;
		
		case 0x5:  //not negative
			if(~NZCV & 8) // N not set
			{
				cond_flag = 1;
			}
		break;
		
		case 0x6:  //overflow
			if(NZCV & 1) // V set
			{
				cond_flag = 1;
			}
		break;
		
		case 0x7:  //not overflow
			if(~NZCV & 1) // V not set
			{
				cond_flag = 1;
			}
		break;
		
		case 0x8:  // unsigned greater than
			if((NZCV & 2) && (~NZCV & 4))  // C set and Z clear
			{
				cond_flag = 1;
			}
		break;
		
		case 0x9:  //unsigned less than or equal to
			if((~NZCV & 2) || (NZCV & 4)) // C clear or Z set
			{
				cond_flag = 1;
			}
		break;
		
		case 0xa:  //signed greater than or equal to
			if(((NZCV & 8) >> 3) == (NZCV & 1)) // N == V
			{
				cond_flag = 1;
			}
		break;
		
		case 0xb:  //signed less than
			if(((NZCV & 8) >> 3) != (NZCV & 1)) // N != V
			{
				cond_flag = 1;
			}
		break;
		
		case 0xc:  // signed greater than
			if((~NZCV & 4) && ((NZCV & 8) >> 3) == (NZCV & 1)) // Z clear and N == V
			{
				cond_flag = 1;
			}
		break;
		
		case 0xd:  // signed less than or equal to
			if((NZCV & 4) || ((NZCV & 8) >> 3) != (NZCV & 1)) // Z set or N != V
			{
				cond_flag = 1;
			}
		break;
		
		case 0xe:  // always
			cond_flag = 1;
		break;
		
		case 0xf: // illegal instruction
			return 0;  
		
		default:
			return 0; // shouldn't reach this...something went wrong
	}
	
	if(cond_flag)
	{
		switch(op)
		{
			case 0x00000000:
				return PC + 4;  // Data processing ops move to next instr
				
			case 0x04000000:
				return PC + 4;  // Data movement ops move to next instr
				
			case 0x08000000:
				if(~IR & 0x02000000)  //bit 25 not set, illegal
				{
					return 0;
				}
				return PC + (sign_extend(simm24) << 2);
			
			case 0x0c000000:
				return 0;
				
			default:
				return 0;  //If reached, something went wrong...
		}
	}

	return PC + 4;  //condition not met, move to next instruction
}
