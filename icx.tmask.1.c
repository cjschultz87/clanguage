// this version does not check for collisions of permutations

#include "stdio.h"
#include "stdlib.h"
#include "array.h"

typedef char *str;

int power(int base, int n)
{
	int romeo = 1;
	
	for (int i = 0; i < n; i++)
	{
		romeo *= base;
	}
	
	return romeo;
}

int strLen(str alpha)
{
	int N = 0;
	
	for (; alpha[N] != NULL; N++){}
	
	return N;
}

void aPrint(array alpha)
{
	for (int i = 0; i < alpha.Length; i++)
	{
		printf("%c",alpha.loc[i]);
	}
	
	printf("\n");
}

int en(char a, str alpha, int MAX)
{	
	int N = 0;
	
	while (N <= MAX)
	{	
		if (a == alpha[N])
		{
			break;
		}
		
		N++;
	}

	return N;
}

void main(int argc, char** argv)
{
	str LOWER = "abcdefghijklmnopqrstuvwxyz";
	
	str UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	str arg = argv[1];
	
	int alphaN = strLen(arg);
	
	array A = arrayF(Tchar,alphaN);
	
	for (int i = 0; i < A.Length; i++)
	{
		A.loc[i] = arg[i];
	}
	
	int c = 0;

	int d = 1;
	
	int MAX = 26;
	
	int cycles = power(2,alphaN);
	
	aPrint(A);
	
	for (int i = 1; i < cycles; i++)
	{
		c++;
		
		if (c > d)
		{
			c = 0;
			d++;
		}
		
		if (i%d == alphaN - 1)
		{
			d = 1;
		}
		
		for (int i_1 = 0; i_1 <= c; i_1++)
		{
			if (en(A.loc[i_1],LOWER,MAX) < MAX)
			{	
				A.loc[i_1] = UPPER[en(A.loc[i_1],LOWER,MAX)];
				
				goto condition_0;
			}
		
			if (en(A.loc[i_1],UPPER,MAX) < MAX)
			{
				A.loc[i_1] = LOWER[en(A.loc[i_1],UPPER,MAX)];
				
				goto condition_0;
			}
		
			cycles--;
			
			condition_0:{};
		}
		
		aPrint(A);
	}
}
