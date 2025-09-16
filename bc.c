#include "stdio.h"
#include "stdlib.h"
#include "array.h"
#include "strings.h"

long power(int base,int exp);

int sLen(str S);

char* select(char* C);

str cat_2(str a,str b);

str plus_d(str a,str b);

int stod(str sierra,int base);

str dtos(int d,int base);

str atod(str sierra,int base);

str divide_str(str sierra,int base,char mode);


/////////////////////////////////

void main(int argc, char** argv)
{
	if (argc != 4)
	{
		printf("bc \"d_0,...,d_n\" base_input base_output\n");
		
		goto endoffunction;
	}
	
	str digits = "0123456789";
	
	digits = select(digits);
	
	for (int i = 1; i < 3; i++)
	{
		int a_len = sLen(argv[i]);
		
		str arg = argv[i];
		
		for (int i_1 = 0; i_1 < a_len; i_1++)
		{
			if (arg[i_1] < digits[0] | arg[i_1] > digits[9])
			{
				if (i == 1)
				{
					if (arg[i_1] != ',')
					{
						printf("first argument must be a string of digit values in base 10 seperated by commas, e.g. to convert binary 101 to decimal arguments should be \"1,0,1\" 2 10");
					}
				}
				
				else
				{
					printf("base arguments must be base 10 integers\n");
					
					goto endoffunction;
				}
			}
			
			condition_0:{};
		}
	}
	
	str input_str = atod(argv[1],strToL(argv[2],10));
	
	if (strCompare(input_str,"badbase") == 1)
	{
		printf("digit values should be smaller than the input base");
		
		goto endoffunction;
	}
	
	int output_base = strToL(argv[3],10);
	
	array alpha_digits = arrayF(Tlong,0);
	
	while (1 > 0)
	{
		long digit = strToL(divide_str(input_str,output_base,0),10);
		
		alpha_digits = arrayAppend(digit,alpha_digits);
		
		input_str = divide_str(input_str,output_base,1);
		
		char boole = 1;
		
		for (int i = 0; i < sLen(input_str); i++)
		{	
			if (!(input_str[i] == '0') && !(input_str[i] == ','))
			{
				boole = 0;
			}
		}
		
		if (boole == 1)
		{
			break;
		}
	}
	
	for (int i = alpha_digits.Length - 1; i >= 0; i--)
	{
		printf("%d",alpha_digits.loc[i]);
		
		if (i > 0)
		{
			printf(",");
		}
	}
	
	printf("\n");
	
	
	
	
	
	endoffunction:{};
}

/////////////////////////////////

long power(int base,int exp)
{
	int rVal = 1;
	
	for (int i = 0; i < exp; i++)
	{
		rVal *= base;
	}
	
	return rVal;
}

int sLen(str S)
{
	int N = 0;
	
	for (N; S[N] != NULL; N++){}
	
	return N;
}

str select(str sierra)
{
	int N = sLen(sierra);
	
	double d_prime;
	
	char* digits = calloc(N,sizeof(char));
	
	for (int i = 0; i < N; i++)
	{
		digits[i] = sierra[i];
	}
	
	for (int i = 0; i < N - 1; i++)
	{
		for (int i_1 = i + 1; i_1 < N; i_1++)
		{
			if (digits[i_1] < digits[i])
			{
				d_prime = digits[i];
				
				digits[i] = digits[i_1];
				
				digits[i_1] = d_prime;
			}
		}
	}
	
	return digits;
}

str cat_2(str a, str b)
{
	int a_len = sLen(a);
	
	int b_len = sLen(b);
	
	int cat_len = a_len + b_len;
	
	str cat_return = calloc(cat_len + 1,sizeof(char));
	
	for (int i = 0; i < a_len; i++)
	{
		cat_return[i] = a[i];
	}
	
	for (int i = a_len; i < a_len + b_len; i++)
	{
		cat_return[i] = b[i - a_len];
	}
	
	cat_return[cat_len] = 0;
	
	return cat_return;
}

str plus_d(str a, str b)
{
	str rVal = "";
	
	int len_a = sLen(a);
	
	int len_b = sLen(b);
	
	str alpha = "";
	str bravo = "";
	
	if (len_a > len_b)
	{
		for (int i = 0; i < len_a; i++)
		{
			str a_c = calloc(1,sizeof(char));
			
			a_c[0] = a[i];
			
			alpha = cat_2(alpha,a_c);
			
			if (i < len_b)
			{
				str b_c = calloc(1,sizeof(char));
				
				b_c[0] = b[i];
				
				bravo = cat_2(bravo,b_c);
			}
			else
			{
				bravo = cat_2("0",bravo);
			}
		}
	}
	else
	{
		for (int i = 0; i < len_b; i++)
		{
			str b_c = calloc(1,sizeof(char));
			
			b_c[0] = b[i];
			
			alpha = cat_2(alpha,b_c);
			
			if (i < len_a)
			{
				str a_c = calloc(1,sizeof(char));
				
				a_c[0] = a[i];
				
				bravo = cat_2(bravo,a_c);
			}
			else
			{
				bravo = cat_2("0",bravo);
			}
		}
	}
	
	str carry = "0";
	
	char boole = 1;
	
	for (int i = sLen(alpha) - 1; boole == 1; i--)
	{
		str a_d = calloc(1,sizeof(char)); 
		
		str b_d = calloc(1,sizeof(char));
		
		if (i >= 0)
		{
			a_d[0] = alpha[i];
			b_d[0] = bravo[i];
		}
		else
		{
			a_d[0] = '0';
			b_d[0] = '0';
		}
		
		str digit = strToN((strToL(a_d,10) + strToL(b_d,10) + strToL(carry,10)),10);
		
		if (strToL(digit,10) > 9)
		{
			carry = "1";
		}
		else
		{
			carry = "0";
		}
		
		digit = strToN(strToL(digit,10) % 10,10);
		
		rVal = cat_2(digit,rVal);
		
		if (i == 0 && !(strToL(carry,10) > 0))
		{
			boole = 0;
		}
	}
	
	return rVal;
}

int stod(str sierra,int base)
{
	int N = sLen(sierra);
	
	int rVal = 0;
	
	for (int i = N - 1; i >= 0; i--)
	{
		str str_digit = calloc(1,sizeof(char));
		
		str_digit[0] = sierra[N - (i + 1)];
		
		rVal += strToL(str_digit,10) * power(base,i);
	}
	
	return rVal;
}

str dtos(int d,int base)
{
	str rVal = "";
	
	str rVal_prime = "";
	
	int d_prime = d;
	
	str str_digit;
	
	while (d_prime > 0)
	{
		str_digit = calloc(1,sizeof(char));
		
		str_digit = strToN(d_prime % base,10);
		
		rVal_prime = cat_2(rVal_prime,str_digit);
		
		d_prime /= base;
		
		if (d_prime > 0)
		{
			rVal_prime = cat_2(rVal_prime,",");
		}
	}
	
	int N = sLen(rVal_prime);
	
	for (int i = 0; i < N; i++)
	{
		str_digit = calloc(1,sizeof(char));
		
		str_digit[0] = rVal_prime[N - (i + 1)];
		
		rVal = cat_2(rVal,str_digit);
	}
	
	str_digit = calloc(0,sizeof(char));
	
	return rVal;
}

str atod(str sierra,int base)
{
	int N = sLen(sierra);
	
	str rVal = "0";
	
	int exp_i = 0;
	
	int N_d = 1;
	
	for (int i = 0; i < N; i++)
	{
		if (sierra[i] == ',')
		{
			N_d++;
		}
	}
	
	for (int i = 0; i < N;)
	{
		int i_1 = i;
		
		while (sierra[i_1] != ',')
		{
			i_1++;
			
			if (i_1 >= N)
			{
				break;
			}
		}
		
		str digit = "";
		
		for (int i_2 = i; i_2 < i_1; i_2++)
		{
			str d_prime = calloc(1,sizeof(char));
			
			d_prime[0] = sierra[i_2];
			
			digit = cat_2(digit,d_prime);
		}
		
		long r_d = stod(digit,10);
		
		if (r_d > base)
		{
			return "badbase";
		}
		
		rVal = plus_d(rVal,strToN((long)(r_d * power(base,N_d - (exp_i + 1))),10));
		
		exp_i++;
		
		i = i_1 + 1;
	}
	
	int L = 2*sLen(rVal) - 1;
	
	str rVal_prime = calloc(L,sizeof(char));
	
	for (int i = 0; i < L; i++)
	{
		rVal_prime[i] = rVal[(i+1)/2];
		
		i++;
		
		if (i < L - 1)
		{
			rVal_prime[i] = ',';
		}
	}
	
	return rVal_prime;
}

str divide_str(str sierra,int base,char mode)
{	
	int sierra_len = sLen(sierra);
	
	str sierra_prime = "";
	
	str carry = "";
	
	str divisor;
	
	for (int i = 0; i < sierra_len;)
	{	
		int i_1 = i;
		
		while (i_1 < sierra_len)
		{
			if (sierra[i_1] != ',')
			{
				i_1++;
				
				break;
			}
		}
		
		divisor = "";
		
		for (int i_2 = i; i_2 < i_1; i_2++)
		{
			str sierra_iprime = calloc(1,sizeof(char));
			
			sierra_iprime[0] = sierra[i_2];
			
			divisor = cat_2(divisor,sierra_iprime);
		}
		
		divisor = cat_2(carry,divisor);
		
		int quotient = strToL(divisor,10) / base;
		
		if (quotient >= 0)
		{
			sierra_prime = cat_2(sierra_prime,strToN(quotient,10));
		}
		
		carry = strToN(strToL(divisor,10) % base,10);
		
		i = i_1 + 1;
		
		//if (i < sierra_len && quotient != 0)
		if (i < sierra_len)
		{
			sierra_prime = cat_2(sierra_prime,",");
		}
	}
	
	if (mode == 0)
	{
		return carry;
	}
	else
	{
		if (sLen(sierra_prime) < 1)
		{
			return strToN(0,10);
		}
		else
		{
			return sierra_prime;
		}
	}
}
