int str_cmpr(const char str1[], const char str2[])
{
	// Function to replace strcmp() from STL
	int i = 0;
	
	while(str1[i] == str2[i])
	{ 
		// Check if end of str1 or str2 is reached  early
		if(str1[i] == '\0' || str2[i] == '\0')
		{
			break;
		}
		i++;
	}
	if(str1[i] == '\0' && str2[i] == '\0')
	{
		return 1;  // Strings match!
	}
	else
	{
		return 0;  // Strings don't match
	}
}

void change_base(int n, int base, char out_str[], int pos)
{
	int neg = n>>31 & 1;  // Checks if first bit is one
	char temp_str [32];  // Temp string to read remainders into
	

	if (base == 2)
	{
		if(neg)
		{
			out_str[0] = '-';
			n = 0 - n;  // Find positive n
		}
		else
		{
			out_str[0] = '+';
		}
		
		out_str[32] = '\0';  // NUL terminate the array for 32 bit bin
		for(int i = 1; i < 32; i++)
		{
			// Reads n off bit by bit
			out_str[i] = '0' + (1 & n>>(31 - i));  
		}
	}
	
	else if(base != 16)
	{
		if(n == 0)  // Treat 0 as special case. By definition it's positive
		{
			out_str[0] = '+';
			out_str[1] = '0';
			out_str[2] = '\0';
			return;
		}
		temp_str[0] = '\0';
		int i = 1;  // Counter for placing chars in temp_str
		int j = 0;  // Counter for placing chars in out_str
		
		if(neg)
		{
			out_str[0] = '-';
			j++;
			n = 0 - n;  // Find positive n
		}
		
		else
		{
			out_str[0] = '+';
			j++;
		}
		
		while(n > 0)
		{
			temp_str[i] = '0' + n % base;
			n /= base;
			i++;
		}
		
		i--;  // Set i to the position of the last char in temp_str
		
		while(temp_str[i] != '\0')
		{
			out_str[j] = temp_str[i];
			j++;
			i--;
		}
		out_str[j] = '\0';  // Ignore what comes after last digit
	}
	
	
	else if(base == 16)
	{
		if(n == 0)  // Treat 0 as special case. By definition it's positive
		{
			out_str[0] = '+';
			out_str[1] = '0';
			out_str[2] = '\0';
			return;
		}
		temp_str[0] = '\0';
		int i = 1;  // Counter for placing chars in temp_str
		int j = 0;  // Counter for placing chars in out_str
		
		if(neg)
		{
			n = 0 - n;  // Find positive n
		}
		
		while(n > 0)
		{
			if(n % base > 9)
			{
				temp_str[i] = 'A' + n % base - 10;
			}
			else
			{
				temp_str[i] = '0' + n % base;
			}
			n /= base;
			i++;
		}
		
		i--;  // Set i to the position of the last char in temp_str
		
		if(neg)
		{
			out_str[0] = '-';
			j++;
		}
		
		else
		{
			out_str[0] = '+';
			j++;
		}
		
		while(temp_str[i] != '\0')
		{
			out_str[j] = temp_str[i];
			j++;
			i--;
		}
		out_str[j] = '\0';  // Ignore what comes after last digit
	}
}

int decode(int n, const char base[] , char out_str[])
{
	int pos = 0;
	
	if(str_cmpr(base, "bin"))
	{
		change_base(n, 2, out_str, pos);
		return 1;
	}
	
	else if(str_cmpr(base, "oct"))
	{
		change_base(n, 8, out_str, pos);
		return 1;
	}
	
	else if(str_cmpr(base, "dec"))
	{
		change_base(n, 10, out_str, pos);
		return 1;
	}	
	
	else if(str_cmpr(base, "hex"))
	{
		change_base(n, 16, out_str, pos);
		return 1;
	}		
	
	else
	{
		out_str[0] = '\0';  // "Empties" char array if can't convert
	}			
	return 0;
	
}

