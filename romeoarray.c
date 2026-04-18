#include "stdio.h"
#include "stdlib.h"

#include "time.h"

#include "strings.h"

typedef char *str;
typedef unsigned long ULONG;

void main(int argc, str* argv)
{
	if (argc != 4)
	{
		printf("<minimum> <maximum> <seperator char>");
		
		goto endoffunction;
	}
	
	ULONG minimum = strToL(argv[1],10);
	
	ULONG maximum = strToL(argv[2],10);
	
	str separator = argv[3];
	
	ULONG aL = maximum - minimum + 1;
	
	ULONG *alpha = calloc(aL, sizeof(ULONG));
	
	ULONG *alpha_prime;
	
	for (int i = minimum; i <= maximum; i++)
	{
		alpha[i - minimum] = i;
	}
	
	ULONG aL_prime = aL;
	
	for (int i = 0; i < aL; i++)
	{
		srand(clock());
		
		ULONG iota = (ULONG)rand() % aL_prime;
		
		printf("%lu",alpha[iota]);
		
		aL_prime--;
		
		alpha_prime = calloc(aL_prime, sizeof(ULONG));
		
		ULONG iota_prime = 0;
		
		for (int i_0 = 0; i_0 < aL_prime + 1; i_0++)
		{
			if (i_0 == iota)
			{	
				iota_prime++;
				
				goto skipfor0;
			}
			
			alpha_prime[i_0 - iota_prime] = alpha[i_0];
			
			skipfor0:{};
		}
		
		alpha = calloc(aL_prime, sizeof(ULONG));
		
		for (int i_0 = 0; i_0 < aL_prime; i_0++)
		{
			alpha[i_0] = alpha_prime[i_0];
		}
		
		if (i < aL - 1)
		{
			printf("%s",separator);
		}
		
		srand(clock());
		
		ULONG sleep_val = (ULONG)rand() % 15000;
		
		for (int i_0 = 0; i_0 < sleep_val; i_0++)
		{
			
		}
	}
	
	endoffunction:{};
}
