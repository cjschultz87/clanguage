#include <array.h>
#include <strings.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct trine
{
	int *loc;
	int Length;
} trine;


typedef struct sTrine
{
	trine *AlphaLoc;
	int Length;
	int AlphaLength;
} sTrine;


int max(int argN, ...)
{
	int k0, k1, L;
	
	va_list VL;
	
	va_start(VL,argN);
	
	k0 = argN;
	
	k1 = va_arg(VL, int);
	
	vStart:{};
	
	if (k0 > k1)
	{
		L = k0;
	}
	else
	{
		L = k1;
	}
	
	k0 = L;
	
	k1 = va_arg(VL, int);
	
	if (k1 == NULL)
	{
		goto vEnd;
	}
	else
	{
		goto vStart;
	}
	
	vEnd:{};
	
	va_end(VL);
	
	return L;
}

int min(int argN, ...)
{
	int k0, k1, L;
	
	va_list VL;
	
	va_start(VL, argN);
	
	k0 = argN;
	
	k1 = va_arg(VL, int);
	
	vStart:{};
	
	if (k0 < k1)
	{
		L = k0;
	}
	else
	{
		L = k1;
	}
	
	k0 = L;
	
	k1 = va_arg(VL, int);
	
	if (k1 == NULL)
	{
		goto vEnd;
	}
	else
	{
		goto vStart;
	}
	
	vEnd:{};
	
	va_end(VL);
	
	return L;
}


// create a trine with NULL allocation
trine NTrine()
{
	int *alloc = calloc(0,0);
	
	trine NT = {alloc, 0};
	
	return NT;
}


// create a trine object
trine tri(int a)
{
	int aDiv = 0;
	
	int aPrime = a;
	
	for (int i = 0; 1 > 0; i++)
	{
		if (aPrime == 0)
		{
			goto endloop;
		}
		
		aDiv = i;
		
		aPrime /= 3;
	}
	
	endloop:{};
	
	aDiv++;
	
	array digitsArray = arrayF(Tshort, aDiv);
	
	
	for (int i = 0; i < aDiv; i++)
	{
		digitsArray.loc[i] = a % 3;
		
		a /= 3;
	}
	
	digitsArray = arrayReverse(digitsArray);
	
	trine T = {calloc(aDiv, sizeof(int)), aDiv};
	
	for (int i = 0; i < aDiv; i++)
	{
		T.loc[i] = (int)digitsArray.loc[i];
	}
	
	return T;
}


// return the maximum trine
trine tMax(trine T, ...)
{
	int tVal0, tVal1;
	
	trine T0, T1, Tango;
	
	va_list VL;
	
	va_start(VL, T);
	
	T0 = T;
	
	T1 = va_arg(VL, trine);
	
	vStart:{};
	
	tVal0 = 0;
	
	tVal1 = 0;
	
	for (int i = 0; i < T0.Length; i++)
	{
		int power = 1;
		
		for (int i1 = 0; i1 < T0.Length - (i + 1); i1++)
		{
			power *= 3;
		}
		
		tVal0 += T0.loc[i] * power;
	}
	
	for (int i = 0; i < T1.Length; i++)
	{
		int power = 1;
		
		for (int i1 = 0; i1 < T1.Length - (i + 1); i1++)
		{
			power *= 3;
		}
		
		tVal1 += T1.loc[i] * power;
	}
	
	if (tVal0 > tVal1)
	{
		Tango = T0;
	}
	else
	{
		Tango = T1;
	}
	
	T0 = Tango;
	
	T1 = va_arg(VL, trine);
	
	if (T1.loc == NULL)
	{
		goto vEnd;
	}
	else
	{
		goto vStart;
	}
	
	vEnd:{};
	
	va_end(VL);
	
	return Tango;
}


// return the minimum trine
trine tMin(trine T, ...)
{
	int tVal0, tVal1;
	
	trine T0, T1, Tango;
	
	va_list VL;
	
	va_start(VL, T);
	
	T0 = T;
	
	T1 = va_arg(VL, trine);
	
	vStart:{};
	
	tVal0 = 0;
	
	tVal1 = 0;
	
	for (int i = 0; i < T0.Length; i++)
	{
		int power = 1;
		
		for (int i1 = 0; i1 < T0.Length - (i + 1); i1++)
		{
			power *= 3;
		}
		
		tVal0 += T0.loc[i] * power;
	}
	
	for (int i = 0; i < T1.Length; i++)
	{
		int power = 1;
		
		for (int i1 = 0; i1 < T1.Length - (i + 1); i1++)
		{
			power *= 3;
		}
		
		tVal1 += T1.loc[i] * power;
	}
	
	if (tVal0 < tVal1)
	{
		Tango = T0;
	}
	else
	{
		Tango = T1;
	}
	
	T0 = Tango;
	
	T1 = va_arg(VL, trine);
	
	if (T1.loc == NULL)
	{
		goto vEnd;
	}
	else
	{
		goto vStart;
	}
	
	vEnd:{};
	
	va_end(VL);
	
	return Tango;	
}


// create a super trine object
sTrine sTri(trine T, ...)
{
	int n, L;
	
	trine T0, T1, Tango;
	
	va_list VL;
	
	va_start(VL, T);
	
	T0 = T;
	
	T1 = va_arg(VL, trine);
	
	n = 2;
	
	vStart:{};
	
	if (T0.Length > T1.Length)
	{
		L = T0.Length;
		Tango = T0;
	}
	else
	{
		L = T1.Length;
		Tango = T1;
	}

	T0 = Tango;
	
	T1 = va_arg(VL, trine);
	
	if (T1.loc == NULL)
	{
		goto vEnd;
	}
	else
	{
		n++;
		
		goto vStart;
	}
	
	vEnd:{};
	
	va_end(VL);

	
	int *alpha = calloc(L, sizeof(int));
	
	trine talloc = {alpha, L};
	
	trine *alphaTrine = calloc(n, sizeof(talloc));
	
	sTrine sierraTrine = {alphaTrine, L, n};
	
	int i = 0;
	
	va_start(VL, T);
	
	T0 = T;
	
	vStart1:{};
	
	sierraTrine.AlphaLoc[sierraTrine.AlphaLength - (1 + i)] = T0;
	
	int deltaL = sierraTrine.Length - T0.Length;
	
	if (deltaL > 0)
	{
		for (int i1 = sierraTrine.Length - 1; i1 > deltaL - 1; i1--)
		{
			sierraTrine.AlphaLoc[sierraTrine.AlphaLength - (1 + i)].loc[i1] = sierraTrine.AlphaLoc[sierraTrine.AlphaLength - (1 + i)].loc[i1 - 1];
			
			if (i1 - 1 < deltaL)
			{
				for (int i2 = 0; i2 < deltaL; i2++)
				{
					sierraTrine.AlphaLoc[sierraTrine.AlphaLength - (1 + i)].loc[i2] = 0;
				}
			}
		}
	}
	
	T0 = va_arg(VL, trine);
	
	if (T0.loc == NULL)
	{
		goto vEnd1;
	}
	else
	{
		i++;
		
		goto vStart1;
	}
	
	vEnd1:{};
	
	va_end(VL);
	
	int *bravo = calloc(L, sizeof(int));
	
	trine tallocB = {bravo, L};
	
	trine *bravoTrine = calloc(n, sizeof(talloc));
	
	sTrine sierraTrinePrime = {bravoTrine, L, n};
	
	for (int i1 = 0; i1 < sierraTrinePrime.AlphaLength; i1++)
	{
		sierraTrinePrime.AlphaLoc[i1] = sierraTrine.AlphaLoc[sierraTrine.AlphaLength - (1 + i1)];
	}
	
	return sierraTrinePrime;
}


// trinary xor
trine tXor(sTrine S)
{
	int *alloc = calloc(S.Length, sizeof(int));
	
	for (int i = 0; i <= S.Length; i++)
	{
		for (int i1 = 1; i1 < S.AlphaLength; i1++)
		{
			alloc[i] = min(max(S.AlphaLoc[i1].loc[i],S.AlphaLoc[i1-1].loc[i]),2-(min(S.AlphaLoc[i1].loc[i],S.AlphaLoc[i1-1].loc[i])));
		}
	}
	
	trine rTrine = {alloc, S.Length};
	
	return rTrine;
}

// trinary xand
trine tXand(sTrine S)
{
	int *alloc = calloc(S.Length, sizeof(int));
	
	for (int i = 0; i <= S.Length; i++)
	{
		for (int i1 = 1; i1 < S.AlphaLength; i1++)
		{
			alloc[i] = max(min(S.AlphaLoc[i1].loc[i],S.AlphaLoc[i1-1].loc[i]),2-max(S.AlphaLoc[i1].loc[i],S.AlphaLoc[i1-1].loc[i]));
		}
	}
}
