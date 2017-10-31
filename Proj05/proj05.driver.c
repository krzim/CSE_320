#include <stdio.h>

int decode(int, const char[], char[]);
void change_base(int, int, char[]);

int main(void)
{
	char str[33];
	int flag;  // Dectects decoding error
	
	//Normal Operations Testing
	
	// Binary Testing
	printf("Binary test 0 to 19 alternating signs:\n\n");
	for(int i = 0; i < 20; i++)
	{
		flag = decode(i, "bin", str);
		printf("decode(%11d, \"bin\", str);  ==> str contains "
				   "\"%s\"\n",i, (flag == 1) ? str : "");
				   
		flag = decode(-i, "bin", str);
		printf("decode(%11d, \"bin\", str);  ==> str contains "
				   "\"%s\"\n",-i, (flag == 1) ? str : "");				   
	}
	
	// Octal Testing
	printf("\n\nOctal test 0 to 19 alternating signs:\n\n");
	for(int i = 0; i < 20; i++)
	{
		flag = decode(i, "oct", str);
		printf("decode(%11d, \"oct\", str);  ==> str contains "
				   "\"%s\"\n",i, (flag == 1) ? str : "");
				   
		flag = decode(-i, "oct", str);
		printf("decode(%11d, \"oct\", str);  ==> str contains "
				   "\"%s\"\n",-i, (flag == 1) ? str : "");	
	}
	
	// Decimal Testing
	printf("\n\nDecimal test 0 to 19 alternating signs:\n\n");	
	for(int i = 0; i < 20; i++)
	{
		flag = decode(i, "dec", str);
		printf("decode(%11d, \"dec\", str);  ==> str contains "
				   "\"%s\"\n",i, (flag == 1) ? str : "");
				   
		flag = decode(-i, "dec", str);
		printf("decode(%11d, \"dec\", str);  ==> str contains "
				   "\"%s\"\n",-i, (flag == 1) ? str : "");	
	}
	
	//Hexidecimal Testing
	printf("\n\nHexidecimal test 0 to 19 alternating signs:\n\n");
	for(int i = 0; i < 20; i++)
	{
		flag = decode(i, "hex", str);
		printf("decode(%11d, \"hex\", str);  ==> str contains "
				   "\"%s\"\n",i, (flag == 1) ? str : "");
				   
		flag = decode(-i, "hex", str);
		printf("decode(%11d, \"hex\", str);  ==> str contains "
				   "\"%s\"\n",-i, (flag == 1) ? str : "");	
	}
	
	//Edge case testing
	
	//Maximums
	flag = decode(2147483647, "bin", str);
	printf("decode(%11d, \"hex\", str);  ==> str contains "
				   "\"%s\"\n",2147483647, (flag == 1) ? str : "");	
	flag = decode(2147483647, "dec", str);
	printf("decode(%11d, \"hex\", str);  ==> str contains "
				   "\"%s\"\n",2147483647, (flag == 1) ? str : "");	
	flag = decode(2147483647, "oct", str);
	printf("decode(%11d, \"hex\", str);  ==> str contains "
				   "\"%s\"\n",2147483647, (flag == 1) ? str : "");	
	flag = decode(2147483647, "hex", str);
	printf("decode(%11d, \"hex\", str);  ==> str contains "
				   "\"%s\"\n",2147483647, (flag == 1) ? str : "");
				   
	//Minimums
	flag = decode(-2147483647, "bin", str);
	printf("decode(%11d, \"bin\", str);  ==> str contains "
				   "\"%s\"\n",-2147483647, (flag == 1) ? str : "");	
	flag = decode(-2147483647, "dec", str);
	printf("decode(%11d, \"dec\", str);  ==> str contains "
				   "\"%s\"\n",-2147483647, (flag == 1) ? str : "");	
	flag = decode(-2147483647, "oct", str);
	printf("decode(%11d, \"oct\", str);  ==> str contains "
				   "\"%s\"\n",-2147483647, (flag == 1) ? str : "");	
	flag = decode(-2147483647, "hex", str);
	printf("decode(%11d, \"hex\", str);  ==> str contains "
				   "\"%s\"\n",-2147483647, (flag == 1) ? str : "");
				   
	//Illegals
	flag = decode(-15, "bad", str);
	printf("decode(%11d, \"bad\", str);  ==> str contains "
				   "\"%s\"\n",-15, (flag == 1) ? str : "");
	
	//Char instead of int
	flag = decode('}', "hex", str);
	printf("decode(%11d, \"hex\", str);  ==> str contains "
				   "\"%s\"\n",'}', (flag == 1) ? str : "");
	return 0;
}
