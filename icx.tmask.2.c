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
	
	if (alphaN > 4)
	{
		printf("enter a string less than 5 characters in length\n");
		
		goto condition_1;
	}
	
	array A = arrayF(Tchar,alphaN);
	
	for (int i = 0; i < A.Length; i++)
	{
		A.loc[i] = arg[i];
	}
	
	int c = 0;

	int d = 1;
	
	int e = 0;
	
	int f = 4;
	
	int MAX = 26;
	
	int cycles = power(2,alphaN);
	
	array ECHO = arrayF(Tlong,cycles/4);
	
	for (int i = 0; i < ECHO.Length; i++)
	{
		ECHO.loc[i] = 2+i;
	}
	
	superArray ALPHA = arrayS(Tchar,alphaN,cycles);
	
	ALPHA.AlphaLoc[0] = A;
	
	A.loc = calloc(alphaN,Tchar);
	
	for (int i = 1; i < cycles; i++)
	{
		
		c = i % 2;
		
		if (i % 4 == 0)
		{
			if (i >= f)
			{
				d++;
				
				f *= 2;
			}
			
			if (e + 1 == d)
			{
				e = 0;
			}
			
			c = ECHO.loc[e];
			
			e++;
		}
		
		
		//printf("c = %d, d = %d, e = %d\n",c,d,e);
		
		if (i % 4 == 0)
		{
			for (int i_1 = 0; i_1 < c; i_1++)
			{
				if (en(ALPHA.AlphaLoc[0].loc[i_1],LOWER,MAX) < MAX)
				{	
					A.loc[i_1] = UPPER[en(ALPHA.AlphaLoc[0].loc[i_1],LOWER,MAX)];
				
					goto condition_2;
				}
		
				if (en(ALPHA.AlphaLoc[0].loc[i_1],UPPER,MAX) < MAX)
				{
					A.loc[i_1] = LOWER[en(ALPHA.AlphaLoc[0].loc[i_1],UPPER,MAX)];
				
					goto condition_2;
				}
				
				condition_2:{};
			}
			
			for (int i_1 = c; i_1 < alphaN; i_1++)
			{
				A.loc[i_1] = ALPHA.AlphaLoc[i-1].loc[i_1];
			}
		}
		
		else
		{
			for (int i_1 = 0; i_1 < alphaN; i_1++)
			{
				A.loc[i_1] = ALPHA.AlphaLoc[i-1].loc[i_1];
			}
		}
		
		ALPHA.AlphaLoc[i] = A;
		
		A.loc = calloc(alphaN,Tchar);
		
		for (int i_1 = 0; i_1 <= c; i_1++)
		{
			if (en(ALPHA.AlphaLoc[i].loc[i_1],LOWER,MAX) < MAX)
			{	
				ALPHA.AlphaLoc[i].loc[i_1] = UPPER[en(ALPHA.AlphaLoc[i].loc[i_1],LOWER,MAX)];
				
				goto condition_0;
			}
		
			if (en(ALPHA.AlphaLoc[i].loc[i_1],UPPER,MAX) < MAX)
			{
				ALPHA.AlphaLoc[i].loc[i_1] = LOWER[en(ALPHA.AlphaLoc[i].loc[i_1],UPPER,MAX)];
				
				goto condition_0;
			}
			
			condition_0:{};
		}
		
		//aPrint(ALPHA.AlphaLoc[i]);
	}
	
	int aN = 0;
	
	printf("number of permutations = %d\n",cycles);
	
	for (int i = 0; i < cycles; i++)
	{
		aPrint(ALPHA.AlphaLoc[i]);
		
		for (int i_1 = 0; i_1 < cycles; i_1++)
		{
			if (i_1 == i)
			{
				i_1++;
			}
			
			for (int i_2 = 0; i_2 < alphaN; i_2++)
			{
				if (ALPHA.AlphaLoc[i].loc[i_2] == ALPHA.AlphaLoc[i_1].loc[i_2])
				{
					aN++;
				}
			}
			
			if (aN == alphaN)
			{
				printf("COLLISION\n");
			}
			
			aN = 0;
		}
		
	}
	
	condition_1:{};
	
}