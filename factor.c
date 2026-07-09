#include "stdio.h"
#include "stdlib.h"

#include "string.h"

#include "windows.h"

#include "process.h"

#pragma comment(lib, "C:\\Program Files (x86)\\Intel\\oneAPI\\2025.3\\lib\\libirc.lib")

typedef unsigned char bool;

#define true	1
#define false	0

bool isPrime = true;

/////////////////////////////////////////////

unsigned int power(unsigned int N, unsigned int E)
{
	unsigned int rVal = 1;
	
	for (int i = 0; i < E; i++)
	{
		rVal *= N;
	}
	
	return rVal;
}


/////////////////////////////////////////////


unsigned int charAdd(char* C)
{
	unsigned int N = 0;
	
	int sN = 0;
	
	while (*(C + sN) != NULL)
	{
		sN++;
	}
	
	sN--;
	
	while (sN >= 0)
	{
		unsigned char digit = *C;
		
		if (digit >= '0' && digit <= '9')
		{
			N += (digit - '0') * power(10, sN);
		}
		
		C++;
		sN--;
	}
	
	return N;
}


/////////////////////////////////////////////

void multiLoop(void* arg)
{
	typedef struct multiPar{
		unsigned int index;
		unsigned int cN;
		unsigned int N;
	}multiPar;
	
	struct multiPar *voidPar;

	voidPar = arg;
	
	unsigned int minI = voidPar->index;
	
	while ((float)voidPar->index < (float)voidPar->N / (float)minI)
	{
		if (voidPar->N % voidPar->index == 0)
		{
			if (isPrime == true)
			{
				isPrime = false;
			}
			
			unsigned int factor = voidPar->N / voidPar->index;
			
			printf("%u, %u\n", voidPar->index, factor);
		}
		
		voidPar->index += voidPar->cN;
	}
		
	_endthread();
}


/////////////////////////////////////////////


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		return -1;
	}
	
	unsigned int N = charAdd(argv[1]);
	
	unsigned int coreN = charAdd(argv[2]);
	
	if (N == 0 || coreN == 0)
	{
		return -1;
	}
	
	if (N < 4)
	{
		printf("%u is prime\n", N);
		
		return 0;
	}
	
	typedef struct multiVar{
		unsigned int index;
		unsigned int cN;
		unsigned int N;
	}multiVar;
	
	unsigned int divisor = 2;
	
	HANDLE* hotel = calloc(coreN, sizeof(HANDLE));
	
	unsigned int multiVarL = sizeof(multiVar);
	
	struct multiVar *voidArg = calloc(coreN, multiVarL);
	
	for (unsigned int i = divisor; i < coreN + divisor; i++)
	{	
		voidArg->index = i;
		voidArg->cN = coreN;
		voidArg->N = N;
		
		hotel[i - divisor] = (HANDLE)_beginthread(multiLoop,1000,(void*)voidArg);
		
		voidArg++;
		
		WaitForSingleObject(hotel[i - divisor],1);
	}
	
	for (int i = 0; i < coreN; i++)
	{
		WaitForSingleObject(hotel[i],INFINITE);
	}
	
	if (isPrime == true)
	{
		printf("%u is prime\n", N);
	}
	
	return 0;
}
