#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

typedef char *str;



#define sPrint(...)	strPrint(strCat(__VA_ARGS__, NULL))





int strLength(str c)
{
	int length = 0;
	
	for (int i = 0; i >=0; i++)
	{
		length = i;
		
		if (!c[i])
		{
			break;
		}
	}
	
	return length;
}


// upper case
str strUpper(str c)
{
	int n = sizeof(c) / 4 + 1;
	
	int index;
	
	str cTranspose = (char*)calloc(strLength(c), 4);


	for (int i = 0; i <= n; i++)
	{
		index = (int)c[i];
		
		if (index >= 97 && index <= 122)
		{
			cTranspose[i] = (index - 32);
		}
	}
	
	return cTranspose;
}


// lower case
str strLower(str c)
{
	int n = sizeof(c) / sizeof(char);

	int index;
	
	str cTranspose = (char*)calloc(strLength(c), 4);

	for (int i = 0; i <= n; i++)
	{
		index = (int)c[i];
		
		if (index >= 65 && index <= 90)
		{
			cTranspose[i] = (index + 32);
		}
	}
	
	return cTranspose;
}


// return the value at the index number
str strI(int index, str S)
{
	char *sVal = (char*)calloc(1, 4);
	
	sVal[0] = S[index];
	
	return sVal;
}


// concatenate two strings
str strCat(str argN, ...)
{
	
	int SL = 0;
	
	str SierraVal, SIERRAVal, S, T;

	va_list VL;
	
	va_start(VL, argN);
	
	S = argN;
	
	T = va_arg(VL, str);
	

	catL:{};

		int sL;
					
		for (int i = 0; i >= 0; i++)
		{
			if (!S[i])
			{
				sL = i;
				
				break;
			}
		}		
		
		int tL;
	
		if (T == NULL)
		{
			return S;
		}
		else
		{
			for (int i = 0; i >= 0; i++)
			{
				if (!T[i])
				{
					tL = i;
			
					break;
				}
			}
		}
				
		char *SVal = calloc(sL + tL, 4);
	
		for (int i = 0; i < sL; i++)
		{
			SVal[i] = S[i];
		}
	
		for (int i = 0; i < tL; i++)
		{
			SVal[i + sL] = T[i];
		}

	
	SIERRAVal = calloc(SL, 4);	
	
	for (int i = 0; i < SL; i++)
	{
		SIERRAVal[i] = SierraVal[i];
	}

	SierraVal = calloc(SL + sL + tL, 4);
	
	for (int i = 0; i < SL; i++)
	{
		SierraVal[i] = SIERRAVal[i];
	}
		
	for (int i = 0; i < (sL + tL); i++)
	{
		SierraVal[i] = SVal[i];
	}
	
	free(SIERRAVal);
		

	S = SierraVal;

	
	T = va_arg(VL, str);
	
	if (T == NULL)
	{
		goto bL;
	}	
	else
	{
		for (int i = 0; i >= 0; i++)
		{
			if(!SierraVal[i])
			{
				SL = i;
				
				break;
			}
		}	
		
		goto catL;
	}
	
	bL:{};
	
	va_end(VL);
	
	return SierraVal;
}


// find the substring at the index number
str strSubI(int startIndex, int count, str S)
{
	char *sVal = calloc(sizeof(S) / 4, 1);
	
	//memcpy(sVal, S, sizeof(S) / sizeof(char));
	
	sVal = S;
	
	char *subVal = calloc(4, 1);
	
	for (int i = 0; i < count; i++)
	{
		subVal[i] = strI(i + startIndex, sVal)[0];
	}
	
	return subVal;
}


// in the string look for the first index of the substring
int strSubS(str s0, str s1)
{
	int index;
	
	for (int i = 0; i >= 0; i++)
	{
		if (!s0[i])
		{
			goto breakReturn;
		}
		
		index = i;
		
		for (int i1 = 0; i >= 0; i++)
		{
			if (!s1[i1])
			{
				break;
			}
			
			if (s1[i1 + 1] != s0[i + i1 + 1])
			{
				break;
			}
			
			goto breakReturn;
		}
	}
	
	breakReturn:{};
	
	return index - 1;
}


// console output
void strPrint(str S)
{
	for (int i = 0; i >= 0; i++)
	{
		if (!S[i])
		{
			goto finishedPrint;
		}
		putc(S[i], stdout);
	}
	
	finishedPrint:{};
}


// compare logical equivalence of two strings
int strCompare(str s0, str s1)
{
	int rVal = 1;
	
	for (int i = 0; i < strLength(s0); i++)
	{
		if (s0[i] != s1[i])
		{
			rVal = 0;
			
			break;
		}
	}
	
	return rVal;
}


// replace
str strRep(str s0, str s1, int index)
{
	int n0 = sizeof(s0) / 4 + 1;
	
	int n1 = sizeof(s1) / 4 + 1;
	
	str rS0;
	
	if (index + n1 > n0)
	{
		rS0 = malloc(sizeof(s0) + (index + n1 - sizeof(s0)));
	}
	
	else
	{
		rS0 = malloc(sizeof(s0));
	}
	
	for (int i = 0; i < sizeof(s0); i++)
	{
		rS0[i] = s0[i];
	}
	
	str rS1 = malloc(sizeof(s1));
	
	rS1 = s1;
	
	for (int i = index; i < sizeof(rS0); i++)
	{
		rS0[i] = rS1[i - index];
	}
	
	return rS0;
}


// insert
str strIns(str s0, str s1, int index)
{
	int n1 = sizeof(s1) / 4 + 1;

	str rS0 = malloc(sizeof(s0) + sizeof(s1));
	
	for (int i = 0; i < index; i++)
	{
		rS0[i] = s0[i];
	}
	
	for (int i = index; i < index + n1; i++)
	{
		rS0[i] = s1[i - index];
	}
	
	for (int i = index + n1; i < ((sizeof(s0) + sizeof(s1)) / sizeof(char)); i++)
	{
		rS0[i] = s0[i - n1];
	}
	
	return rS0;
}


// delete
str strDel(str s0, str s1)
{
	str rS0 = calloc(1,strLength(s0) - strLength(s1));
	
	for (int i = 0; i <= strSubS(s0, s1); i++)
	{
		rS0[i] = s0[i];
	}
	
	for (int i = strSubS(s0, s1) + strLength(s1); i < strLength(s0); i++)
	{
		rS0[i] = s0[i];
	}
	
	return rS0;
}


// reverse string
str strRev(str s)
{
	str sVal = "";
	
	str cVal = "";
	
	for (int i = 1; i <= strLength(s); i++)
	{
		cVal = (char*)calloc(1, 4);
		
		cVal[0] = s[strLength(s) - i];
		
		sVal = strCat(sVal, cVal, NULL);
		
		free(cVal);
	}
	
	return sVal;
}


// convert an int to an ascii string character
str strToC(int a)
{
	str c = (char*)malloc(4);

	c[0] = a;
	
	return c;
}


// convert an ascii string to an integer value
int* strToS(str s)
{
	int n = sizeof(s) / 4 + 1;
	
	int *iVals = calloc(n, sizeof(int));
	
	for (int i = 0; i <= n; i++)
	{
		iVals[i] = (int)s[i];
	}
	
	return iVals;
}


// convert string digits to int
long strToL(str s, int base)
{
	int digitsElemental = 0;

	if (base > 16)
	{
		goto return0;
	}

	long sVal = 0;

	char digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	
	
	for (int i = 0; i < strLength(s); i++)
	{
	
		for (int i1 = 0; i1 < 16; i1++)
		{
			str stringS = (char*)calloc(1, 4);
			
			str stringD = (char*)calloc(1, 4);
			
			stringS[0] = s[i];
			
			stringD[0] = digits[i1];
		
			if (strCompare(stringS, stringD) == 1)
			{

				digitsElemental = 1;
				
				long baseProduct = 1;
				
				for (int i2 = 1; i2 < strLength(s) - i; i2++)
				{
					baseProduct *= base;
				}
				
				sVal += i1 * baseProduct;
				
				goto endofloop0;
			}
		}
		
		endofloop0:{};
	}

	return sVal;
	
	
	return0:{};
	
	if (digitsElemental == 0)
	{
		return 0 - 1;
	}
	
}


// convert int to string digits
str strToN(long l, int base)
{
	str lVal = "";

	int divisor = 1;
	
	int modulo = 0;
	
	char digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	
	str mLoc = (char*)calloc(1, 4);
		
	while (divisor > 0)
	{
		divisor = l / base;
		
		modulo = l % base;
		
		for (int i = 0; i < base; i++)
		{
			if (modulo == i)
			{
				mLoc[0] = digits[i];
			}
		}
		
		lVal = strCat(lVal, mLoc, NULL);
		
		l = divisor;
	}
	
	lVal = strRev(lVal);
	
	return lVal;
}
