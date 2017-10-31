#include "/user/cse320/Projects/project07.hardware.h"


unsigned sub_carry(unsigned, unsigned);
unsigned add_carry(unsigned, unsigned);
unsigned sub_ovrflw(unsigned, unsigned);
unsigned add_ovrflw(unsigned, unsigned);

unsigned sub_carry(unsigned op1, unsigned op2)
{
	unsigned res_31 = (op1 - op2) & 1<<31;
	unsigned op1_31 = op1 & 1<<31;
	unsigned op2_31 = op2 & 1<<31;
	// Shamelessly stolen from Prof McCullen piazza #277
	return ((~op1_31 & op2_31) | (res_31 & (~op1_31 | op2_31))) >> 31;
}

unsigned add_carry(unsigned op1, unsigned op2)
{
	unsigned res_31 = (op1 + op2) & 1<<31;
	unsigned op1_31 = op1 & 1<<31;
	unsigned op2_31 = op2 & 1<<31;	
	// Shamelessly stolen from Prof McCullen piazza #277	
	return ((op1_31 & op2_31) | (~res_31 & (op1_31 | op2_31))) >> 31;	
}

unsigned sub_ovrflw(unsigned op1, unsigned op2)
{
	unsigned res_31 = (op1 - op2) & 1<<31;
	unsigned op1_31 = op1 & 1<<31;
	unsigned op2_31 = op2 & 1<<31;
	// Shamelessly stolen from Prof McCullen piazza #277	
	return ((op1_31 ^ op2_31) & (res_31 & op2_31)) >> 31;
}

unsigned add_ovrflw(unsigned op1, unsigned op2)
{
	unsigned res_31 = (op1 + op2) & 1<<31;
	unsigned op1_31 = op1 & 1<<31;
	unsigned op2_31 = op2 & 1<<31;	
	// Shamelessly stolen from Prof McCullen piazza #277	
	return (op1_31 == op2_31) & (res_31 != op1_31);
}
void execute()
{
	// Instruction masks
	unsigned COND_MASK = 0xfc000000;
	unsigned I_MASK = 0x02000000;
	unsigned OP_MASK = 0x01e00000;	
	unsigned S_MASK = 0x00100000;
	unsigned RN_MASK = 0x000f0000;
	unsigned RD_MASK = 0x0000f000;
	unsigned ILGL_MASK = 0x00000f00;
	unsigned RM_MASK = 0x0000000f;
	unsigned IMVAL_MASK = 0x000000ff;
	
	// Mask Shifts
	unsigned COND_SHFT = 26;
	unsigned I_SHFT = 25;
	unsigned OP_SHFT = 21;
	unsigned S_SHFT = 20;
	unsigned RN_SHFT = 16;
	unsigned RD_SHFT = 12;
	unsigned ILGL_SHFT = 8;
	
	
	// Deconstructed instruction values
	unsigned cond;
	unsigned i_bit;
	unsigned op;
	unsigned s_bit;
	unsigned rn;
	unsigned rd;
	unsigned ilgl;
	unsigned rm;
	unsigned im_val;
	
	// Vars to store values in registers
	unsigned RN;
	unsigned RM;
	unsigned N;
	unsigned Z;
	unsigned C;
	unsigned V;
	
	//Other vars
	unsigned result;
	
	// Get values from instruction
	cond = (IR & COND_MASK) >> COND_SHFT;
	i_bit = (IR & I_MASK) >> I_SHFT;
	op = (IR & OP_MASK) >> OP_SHFT;
	s_bit = (IR & S_MASK) >> S_SHFT;
	rn = (IR & RN_MASK) >> RN_SHFT;
	rd = (IR & RD_MASK) >> RD_SHFT;
	ilgl = (IR & ILGL_MASK) >> ILGL_SHFT;
	rm = (IR & RM_MASK);
	im_val = (IR & IMVAL_MASK);
	
	
	// Prelim test if valid instruction
	// Each op handles its own special illegals
	if (cond != 56 || ilgl != 0 || (i_bit == 0 && im_val > 15))
	{ 
		CPSR = 1;
		return;
	}			
	
	switch (op)
	{
		case 0:  // and
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				write_reg_file(rd, RN & im_val);
				if (s_bit ==1)
				{
					Z = (RN & im_val ) == 0;
					CPSR = (Z << 30);  // im_val cannot be negative
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				write_reg_file(rd, RN & RM);
				if(s_bit == 1)
				{
					N = (RN & RM) >> 31 & 1 ;
					Z = (RN & RM ) == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			break;
			
		case 1:  // eor
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				write_reg_file(rd, RN ^ im_val);
				if(s_bit == 1)
				{
					N = (RN ^ im_val) >> 31 & 1 ;
					Z = (RN ^ im_val ) == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				write_reg_file(rd, RN ^ RM);
				if(s_bit == 1)
				{
					N = (RN ^ RM) >> 31 & 1 ;
					Z = (RN ^ RM ) == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			break;
			
		case 2:  // sub
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				result = RN - im_val;
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = sub_carry(RN, im_val);
					V = sub_ovrflw(RN, im_val);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				result = RN - RM;			
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = sub_carry(RN, RM);
					V = sub_ovrflw(RN, RM);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			break;
			
		case 3:  // rsub
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				result = im_val - RN;
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = sub_carry(im_val, RN);
					V = sub_ovrflw(im_val, RN);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				result = RM - RN;			
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = sub_carry(RM, RN);
					V = sub_ovrflw(RM, RN);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			break;
			
		case 4:  // add
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				result = RN + im_val;
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = add_carry(RN, im_val);
					V = add_ovrflw(RN, im_val);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				result = RN + RM;			
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = add_carry(RN, RM);
					V = add_ovrflw(RN, RM);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			break;
			
		case 5:  // adc
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				result = RN + im_val + add_carry(RN, im_val);
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = add_carry(RN, im_val);
					V = add_ovrflw(RN, im_val);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				result = RN + RM + add_carry(RN, RM);			
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = add_carry(RN, RM);
					V = add_ovrflw(RN, RM);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			break;
			
		case 6:  // sbc
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				result = RN - im_val - ~sub_carry(RN, im_val);
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = sub_carry(RN, im_val);
					V = sub_ovrflw(RN, im_val);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				result = RN - RM - ~sub_carry(RN, RM);			
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = sub_carry(RN, RM);
					V = sub_ovrflw(RN, RM);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}		
			break;	
			
		case 7:  // rsc
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				result = im_val - RN - ~sub_carry(im_val, RN);
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = sub_carry(im_val, RN);
					V = sub_ovrflw(im_val, RN);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				result = RM - RN - ~sub_carry(RM, RN);			
				write_reg_file(rd, result);
				
				if(s_bit == 1)
				{
					N = result >> 31 & 1;
					Z = result == 0;
					C = sub_carry(RM, RN);
					V = sub_ovrflw(RM, RN);
					CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
				}
			}
			break;
			
		case 8:  // tst
			// S bit must be set
			if (s_bit == 0)
			{
				CPSR = 1;
				return;
			}
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				Z = (RN & im_val ) == 0;
				CPSR = (Z << 30);  // im_val cannot be negative
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				N = (RN & RM) >> 31 & 1 ;
				Z = (RN & RM ) == 0;
				CPSR = N<<31 | Z<<30;
			}
			break;
			
		case 9:  // teq
			// S bit must be set
			if (s_bit == 0)
			{
				CPSR = 1;
				return;
			}
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				N = RN >> 31 & 1;  // im_val cannot be negative
				Z = (RN ^ im_val ) == 0;
				CPSR = N<<31 | Z<<30;
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				N = (RN ^ RM) >> 31 & 1;
				Z = (RN ^ RM ) == 0;
				CPSR = N<<31 | Z<<30;			
			}		
			break;
			
		case 10:  // cmp
			// S bit must be set
			if (s_bit == 0)
			{
				CPSR = 1;
				return;
			}		
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				result = RN - im_val;
				N = result >> 31 & 1;
				Z = result == 0;
				C = sub_carry(RN, im_val);
				V = sub_ovrflw(RN, im_val);
				CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				result = RN - RM;			
				N = result >> 31 & 1;
				Z = result == 0;
				C = sub_carry(RN, RM);
				V = sub_ovrflw(RN, RM);
				CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
			}
			break;
			
		case 11:  // cmn
			// S bit must be set
			if (s_bit == 0)
			{
				CPSR = 1;
				return;
			}		
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				result = RN + im_val;
				N = result >> 31 & 1;
				Z = result == 0;
				C = add_carry(RN, im_val);
				V = add_ovrflw(RN, im_val);
				CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				result = RN + RM;			
				N = result >> 31 & 1;
				Z = result == 0;
				C = add_carry(RN, RM);
				V = add_ovrflw(RN, RM);
				CPSR = (N<<31) | (Z<<30) | (C<<29) | (V<<28);
			}
			break;
			
		case 12:  // orr
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				write_reg_file(rd, RN | im_val);
				if(s_bit == 1)
				{
					N = (RN | im_val) >> 31 & 1 ;
					Z = (RN | im_val ) == 0;
					CPSR = N<<31 | Z<<30;
				}
				
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				write_reg_file(rd, RN | RM);
								if(s_bit == 1)
				{
					N = (RN | RM) >> 31 & 1 ;
					Z = (RN | RM ) == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			break;
			
		case 13:  // mov
			if(rn != 0)  // Only rd and rm or im_val are legal
			{
				CPSR = 1;
				return;
			}
			
			if(i_bit == 1)
			{
				write_reg_file(rd, im_val);
				if(s_bit == 1)
				{
					N = im_val >> 31 & 1 ;
					Z = im_val == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				write_reg_file(rd, RM);
				if(s_bit == 1)
				{
					N = RM >> 31 & 1 ;
					Z = RM == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			break;
			
		case 14:  // bic
			if(i_bit == 1)
			{
				read_reg_file(rn, rm, &RN, &RM); // rm & RM not used
				write_reg_file(rd, RN & ~im_val);
				if(s_bit == 1)
				{
					N = (RN & ~im_val) >> 31 & 1;
					Z = (RN & ~im_val ) == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				write_reg_file(rd, RN & ~RM);
				if(s_bit == 1)
				{
					N = (RN & ~RM) >> 31 & 1;
					Z = (RN & ~RM ) == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			break;
			
		case 15:  //mvn
			if(rn != 0)  // Only rd and rm or im_val are legal
			{
				CPSR = 1;
				return;
			}
			
			if(i_bit == 1)
			{
				write_reg_file(rd, ~im_val);
				if(s_bit == 1)
				{
					N = ~im_val >> 31 & 1 ;
					Z = ~im_val == 0;
					CPSR = N<<31 | Z<<30;
				}
			}
			else
			{
				read_reg_file(rn, rm, &RN, &RM);
				write_reg_file(rd, ~RM);
				if(s_bit == 1)
				{
					N = ~RM >> 31 & 1 ;
					Z = ~RM == 0;
					CPSR = N<<31 | Z<< 30;
				}
			}
			break;
			
		default:  // Shouldn't hit here...default to illegal instruction
			CPSR = 1;
			return;
			break;
	}
	return;
}
