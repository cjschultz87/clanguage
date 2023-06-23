#include <stdlib.h>
#include <stdio.h>

#define Tchar		0 //character
#define Tshort		1 //short int
#define Tlong		2 //long int
#define Tlonglong	3 //long long
#define Tfloat		4 //floating point
#define Tdouble		5 //double
#define Tlongdouble	6 //long double
#define Tstr 		7 //string


typedef struct array
{
	long *loc;
	int Type;
	int Length;
} array;

typedef struct superArray
{
	array *AlphaLoc;
	int Type;
	int Length;
} superArray;

typedef struct stringArray
{
	char *loc;
	int Length;
} stringArray;

int typeVal(int T)
{
	int sizeT;
	
	switch (T)
	{
		case 0:
			sizeT = 8;
			break;
		case 1:
			sizeT = 16;
			break;
		case 2:
			sizeT = 32;
			break;
		case 3:
			sizeT = 64;
			break;
		case 4:
			sizeT = 32;
			break;
		case 5:
			sizeT = 64;
			break;
		case 6:
			sizeT = 128;
			break;
		default:
			sizeT = 0;
	}
	
	return sizeT;
}



//create a array from a string//
stringArray strA(char *SVar)
{
	int sizeT = typeVal(Tchar);
	
	int lengthS = 0;
	
	for (int i = 0; i >= 0; i++)
	{
		lengthS = i;
	
		if (!SVar[i])
		{
			break;
		}
	}
	
	char *Allocation = calloc(lengthS, sizeT);
	
	for (int i = 0; i < lengthS; i++)
	{
		Allocation[i] = SVar[i];
	}
	
	stringArray S = {Allocation, lengthS};
	
	return S;
}


//create a string from a string array//
char* strS(stringArray AVar)
{
	int sizeT = typeVal(Tchar);

	char *strVal = calloc(AVar.Length, sizeT);
	
	for (int i = 0; i < AVar.Length; i++)
	{
		strVal[i] = AVar.loc[i];
	}
	
	return strVal;
}


//create an array structure//
array arrayF(int T, long L)
{
	int sizeT = typeVal(T);
	
	long *Allocation = calloc(L, sizeT);
	
	array A = {Allocation, T, L};
	
	return A;
}


//transpose a string array to an array//
array strArray(stringArray AVar)
{
	array arrayVal = arrayF(Tchar, AVar.Length);
	
	for (int i = 0; i < AVar.Length; i++)
	{
		arrayVal.loc[i] = AVar.loc[i];
	}
	
	return arrayVal;
}


//compare arrays//
short arrayComp(array a0, array a1)
{
	short rVal = 0;
	
	if (a0.Length != a1.Length || (a0.Length == 0 | a1.Length == 0))
	{
		goto returnVal;
	}
	else
	{
		for (int i = 0; i < a0.Length; i++)
		{
			if (a0.loc[i] != a1.loc[i])
			{
				goto returnVal;
			}
		}
		
		rVal = 1;
	}
	
	returnVal:{};
	
	return rVal;
}


//cartography of elements in one array to a new array//
array arrayCart(int T, array aI)
{
	int sizeT = typeVal(T);
	
	long *Allocation = malloc(sizeof(aI.loc));
	
	Allocation = aI.loc;
	
	array aR = {Allocation, T, sizeof(aI.loc) / sizeT};
	
	return aR;
}


//create a super array of arrays//
superArray arrayS(int T, long aL, long sL)
{
	int sizeT = typeVal(T);
	
	long *alpha = calloc(aL, sizeT);
	
	array alphaArray = {alpha, T, aL};
	
	array *alphaAllocation = calloc(sL, sizeof(alphaArray));
	
	superArray Alpha = {alphaAllocation, T, sL};
	
	return Alpha;
}


// add an array to the super array
superArray arrayAppendS(array A, superArray Alpha)
{
	superArray Bravo = {calloc(Alpha.Length + 1, sizeof(A)),A.Type,Alpha.Length + 1};
	
	for (int i = 0; i < Alpha.Length; i++)
	{
		Bravo.AlphaLoc[i] = Alpha.AlphaLoc[i];
	}
	
	Bravo.AlphaLoc[Alpha.Length] = A;
	
	return Bravo;
}

//add an entry at an index with value of the array length//
array arrayAppend(long appendVal, array A)
{
	array B = arrayF(A.Type,A.Length + 1);
	
	for (int i = 0; i < A.Length; i++)
	{
		B.loc[i] = A.loc[i];
	}
	
	B.loc[A.Length] = appendVal;
	
	return B;
}


//remove all instances of the value//
array arrayDelete(long delVal, array A)
{
	array QE = arrayF(A.Type, A.Length);
	
	int typeBytes = typeVal(A.Type);
	
	int delCount = 0;
	
	for (int i = 0; i < A.Length; i++)
	{	
		if (QE.loc[i] != delVal)
		{
			QE.loc[i] = A.loc[i];
		}
		else
		{
			delCount++;
		}
	}
	
	free(A.loc);
	A.loc = calloc(QE.Length - delCount, typeBytes);
	A.Length = QE.Length - delCount;
	
	for (int i = 0; i < A.Length; i++)
	{
		A.loc[i] = QE.loc[i];
	}
	
	return A;
}


//remove the entry at the index value//
array arrayRemove(long delVal, array A)
{
	array QE = arrayF(A.Type, A.Length);
	
	int typeBytes = typeVal(A.Type);
	
	for (int i = 0; i < A.Length; i++)
	{	
		if (QE.loc[i] != A.loc[delVal])
		{
			QE.loc[i] = A.loc[i];
		}
	}
	
	free(A.loc);
	A.loc = calloc(QE.Length - 1, typeBytes);
	A.Length = QE.Length - 1;
	
	for (int i = 0; i < A.Length; i++)
	{
		A.loc[i] = QE.loc[i];
	}
	
	return A;
}


//resize the array//
array arrayResize(long startIndex, long newLength, array A)
{
	array QE = arrayF(A.Type, newLength);
	
	int typeBytes = sizeof(A.loc[0]);
	
	for (int i = startIndex; i < newLength; i++)
	{
		QE.loc[i] = A.loc[i];
	}
	
	A.Length = newLength;
	
	return QE;
	
	free(A.loc);
	free(QE.loc);
}


//empty the array//
array arrayClear(array A)
{
	free(A.loc);
	
	A.Length = 0;
	
	return A;
}


//return the first index of the value//
int arrayIndexFirst(long var, array A)
{
	int indexVal = 0 - 1;
	
	for (int i = 0; i < A.Length; i++)
	{
		if (A.loc[i] == var)
		{
			indexVal = i;
			break;
		}
	}
	
	return indexVal;
}


//return the last index of the value//
int arrayIndexLast(long var, array A)
{
	int indexVal = 0 - 1;
	
	for (int i = A.Length; i > 0; i--)
	{
		if (A.loc[i] == var)
		{
			indexVal = i;
			break;
		}
	}
	
	return indexVal;
}


//reverse the order of the array elements//
array arrayReverse(array A)
{
	array QE = arrayF(A.Type, A.Length);
	
	int typeBytes = typeVal(A.Type);
	
	for (int i = 0; i < A.Length; i++)
	{
		
		QE.loc[i] = A.loc[i];
	}
	
	free(A.loc);
	A.loc = calloc(QE.Length, typeBytes);
	A.Length = QE.Length;
	
	for (int i = 0; i < A.Length; i++)
	{
		A.loc[i] = QE.loc[QE.Length - i - 1];
	}
	
	return A;
}


//sort the array elements//
array arraySort(array A)
{
	array QE = arrayF(A.Type, A.Length);
	
	for (int i = 0; i >= 0; i++)
	{
		for (int ia = 0; ia < A.Length; ia++)
		{
			QE.loc[ia] = A.loc[ia];
		}
		
		for (int ia = 0; ia < A.Length; ia++)
		{
			if (QE.loc[ia + 1] < A.loc[ia])
			{
				int arrayQEIndexAVal = QE.loc[ia + 1];
				int arrayIndexAVal = A.loc[ia];
				
				QE.loc[ia + 1] = arrayIndexAVal;
				A.loc[ia] = arrayQEIndexAVal;
			}

			else
			{
				goto breakFor;
			}
		}
	}
	
	breakFor:
	
	return A;
}
