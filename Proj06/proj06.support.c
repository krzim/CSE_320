#include "/user/cse320/Projects/project06.support.h"

int round_frac(unsigned);
unsigned normalize(long long, unsigned*);
unsigned find_msb(long long);

unsigned find_msb(long long num)
{
	// Finds loc of MSB in num. Bits range from 63:0 with 63 being MSB
	int shifts = 0;
	long long mask = 1ULL << 63;
	while ((num & mask) == 0)
	{
		mask >>= 1;
		shifts++;
	}
	return 63 - shifts;
}

unsigned normalize(long long prod_raw, unsigned *exp)
{
	unsigned prod_norm = 0;
	unsigned lfb = 0;
	long long LFB_MASK;  // Left of binary point mask
	LFB_MASK = 3ULL << 46;
	
	lfb = (prod_raw & LFB_MASK) >> (46);
	
	if (lfb == 1 || lfb == 0) // Denormal case
	{
		prod_norm = prod_raw >> 23;
	}
	else
	{
		prod_norm = prod_raw >> 24;
		*exp += 1;
		if (*exp == 0xFF)  // Returns all zero frac to represent inf
		{
			return 0;
		}
	}
	return prod_norm;
}

float mult( float flt1, float flt2 )
{
	// Masks
	unsigned SIGN_MASK = 0x80000000;
	unsigned EXP_MASK = 0x7F800000; 
	unsigned FRAC_MASK = 0x007FFFFF;
	unsigned EXP_SHFT = 23;
	unsigned EXP_BIAS = 0x7F;
	
	// Pieces of floats
	union sp_union prod;
	union sp_union flt1_un;
	union sp_union flt2_un;
	unsigned prod_sign;
	unsigned prod_exp;
	unsigned prod_norm;
	unsigned flt2_exp;
	unsigned flt1_exp;
	long long flt1_frac;
	long long flt2_frac;
	long long flt1_significand;
	long long flt2_significand;
	long long prod_raw;
	
			
	flt1_un.frep = flt1;
	flt2_un.frep = flt2;
	
	flt1_frac = flt1_un.irep & FRAC_MASK;
	flt2_frac = flt2_un.irep & FRAC_MASK;
	
	prod_sign = (flt1_un.irep & SIGN_MASK)
				^ (flt2_un.irep & SIGN_MASK);
	
	flt1_exp = (flt1_un.irep & EXP_MASK) >> EXP_SHFT;
	flt2_exp = (flt2_un.irep & EXP_MASK) >> EXP_SHFT;
	
	flt1_significand = flt1_frac | 1ULL << 23;
	flt2_significand = flt2_frac | 1ULL << 23;
	
	
	// Catch infs and NaNs. inf * 0 = nan, nan * anything = nan
	// +/-inf * +/-anything = +/-inf
	if (flt1_exp == 0xFF || flt2_exp == 0xFF)
	{
		if (flt1_frac == 0 && flt2_frac ==0)
		{
			if(flt1_exp == 0 || flt2_exp == 0)
			{
				return NAN;
			}

			else if(flt2_frac == 0 && flt2_exp == 0)
			{
				return  prod_sign ? -INFINITY : INFINITY;
			}
		}
		
		if ((flt1_exp == 0xFF && flt1_frac != 0)
			|| (flt2_exp == 0xFF && flt2_frac != 0))
			{
				return NAN;
			}
		return prod_sign ? -INFINITY : INFINITY;
	}
	
	// Handle zeros and denormals. Denormal * denormal = 0, 0 * flt = 0
	if (flt1_exp == 0)
	{
		if(flt1_frac == 0)
		{
			return prod_sign ? -0.0 : 0;
		}
		flt1_significand = flt1_frac;
		flt1_exp = 1;
	}
	
	if (flt2_exp == 0)
	{
		if(flt2_frac == 0)
		{
			return prod_sign ? -0.0 : 0;
		}
		flt2_significand = flt2_frac;
		flt2_exp = 1;
		
		if(flt1_exp == 1)
		{
			return prod_sign ? -0.0 : 0;  // Two denormals gives 0
		}
	}			
	
	prod_exp = flt1_exp + flt2_exp - EXP_BIAS;
			   
	prod_raw = flt1_significand * flt2_significand;
	
	prod_norm = normalize(prod_raw, &prod_exp);
	
	prod.irep = prod_sign | (prod_norm ^ 1ULL << 23)
				| (prod_exp << EXP_SHFT);
	return prod.frep;
}
