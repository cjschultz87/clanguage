#include "stdlib.h"
#include "stdio.h"
#include "array.h"
#include "strings.h"
#include "windows.h"
#include "process.h"
#include "time.h"


#define SyntaxError	sPrint("syntax error", "\n")


// pointer of directory entries stored as strings (pointer of pointers)

str* dirEntries;

// an array of arrays which are used as buffers for the bytes that are read

superArray Buffers;

// strings are initialised as blank by default

str Dir = "";
	
str fPath0 = "";
	
str fPath1 = "";

str fileVal = "";

// default block value is one
	
unsigned long blockVal = 1;

// size of the buffer

unsigned long blockVal1 = 0;

unsigned long long inSVal = 0;

unsigned long long outSVal = 0;

int outS = 0;

// number of blocks initialised as zero

unsigned long long NVal = 0;

//total file size defined

unsigned long long fileSize0;

int fCount = 0;

int textOut = 0;

int listOut = 0;

int modZero = 0;

// using blocks is initialised as zero (not in use)

int blockActive = 0;

// comparison is initialised as zero (not in use)

int compActive = 0;

// verbose is initialised as zero (not in use)

int verActive = 0;

int RVal = 1;

int AlphaIndex = 0;

int rc[14];

int txtBase = 10;



//file pointers

FILE *fPointer0, *fPointer0_1, *fPointer0_2, *fPointer0_3, *fPointer0_4, *fPointer0_5, *fPointer0_6, *fPointer0_7, *fPointer0_8, *fPointer0_9, *fPointer0_10, *fPointer0_11, *fPointer0_12, *fPointer0_13, *fPointer1, *fPointer1_1, *fPointer1_2, *fPointer1_3, *fPointer1_4, *fPointer1_5, *fPointer1_6, *fPointer1_7, *fPointer1_8, *fPointer1_9, *fPointer1_10, *fPointer1_11, *fPointer1_12, *fPointer1_13;

FILE **FP0, **FP1;



clock_t t0, *t1;




void readerF(int readerCount)
{	
	
	if (blockActive == 1)
	{	
		// the allocation of buffers is an array of short integers of size blockVal + blockVal1
		Buffers.AlphaLoc[readerCount] = arrayF(Tshort, blockVal + blockVal1);
	}
	
	unsigned long long index = 0;
	
	int index_1 = 1;
	
	int index_2 = 1;
	
	int lVal = 0;
	
	if (textOut == 1)
	{
		index_1 =3;
	}
	
	if (listOut == 1)
	{
		index_2 = 3;
		
		lVal = 1;
	}
	
	
	for (unsigned long long i = fileSize0*index_1 - (index_1+ (readerCount*index_1*index_2)); index < ((fileSize0/(index_2*RVal)) - (inSVal + outSVal)); i -= blockVal * RVal*index_1*index_2)
	{
		
		if (outS == 0)
		{
			fseek(FP0[readerCount], i/index_1, 0);
		}
		else
		{
			fseek(FP0[readerCount ],index*RVal + readerCount,0);
		}
		
		fseek(FP1[readerCount], i/index_2, 0);
		
		
		if (blockActive == 1)
		{
			if (fileSize0 - i < blockVal)
			{
				blockVal = fileSize0 - i;
			}	

			fread(Buffers.AlphaLoc[readerCount].loc, 1, blockVal, FP0[readerCount]);
			
			if (verActive == 1)
			{
				sPrint("block ", strToN(i, 10), "\n");
			
				for (unsigned long i1 = 0; i1 < blockVal; i1++)
				{
					sPrint(strToN(Buffers.AlphaLoc[readerCount].loc[i1], 10), "\n");
				}
			}
			else
			{
				fwrite(Buffers.AlphaLoc[readerCount].loc, 1, blockVal, FP1[readerCount]);
			}
		}
		else
		{

			str digits = "0123456789abcdef";

			if (listOut == 1)
			{
				int foxByte = 0;
		
				for (int i3 = 0; i3 < 2; i3++)
				{
					lVal -= i3;
					
					fseek(FP0[readerCount],i - lVal, 0);
					
					int foxtrot = getc(FP0[readerCount]);
				
					int foxtrotPrime;
				
					for (int i4 = 0; i4 < 16; i4++)
					{
						if (foxtrot == digits[i4])
						{
							foxtrotPrime = i4;
							
							break;
						}
					}
				
					if (i3 == 0)
					{
						foxByte += 16 * foxtrotPrime;
					}
					else
					{
						foxByte += foxtrotPrime;
					}
				}
				
				putc(foxByte,FP1[readerCount]);
				
				lVal = 1;
				
			}
			
			if (textOut == 1)
			{	
				putc('\n',FP1[readerCount]);
				
				int alpha = getc(FP0[readerCount]);
				
				array digitsC = arrayF(Tshort,2);
				
				for (int i3 = 1; i3 >= 0; i3--)
				{
					int alphaPrime = alpha %16;
					
					for (int i4 = 0; i4 < 16; i4++)
					{
						if (i4 == alphaPrime)
						{
							digitsC.loc[i3] = digits[i4];
							
							break;
						}
					}
					
					alpha /= 16;
				}
				
				for (int i3 = 0; i3 < 2; i3++)
				{
					fseek(FP1[readerCount],i+1+i3,0);
					
					putc(digitsC.loc[i3],FP1[readerCount]);
				}
				
				
				
			}
				
			if (compActive == 1)
			{				
				str sVal0 = strToN(getc(FP0[readerCount]), 10);
					
				str sVal1 = strToN(getc(FP1[readerCount]), 10);
				
				if (strCompare(sVal0, sVal1) == 0)
				{
					sPrint("###","\t","###","\t","###","\t","###","\t","###","\n");
				}
					
				sPrint(strToN((i + 1), 10), "\t", sVal0, " !^ ", sVal1, "\033[3C\t", strToN(strCompare(sVal0, sVal1), 10), "\n");
				
				if (strCompare(sVal0, sVal1) == 0)
				{
					sPrint("###","\t","###","\t","###","\t","###","\t","###","\n");
				
					int c;
					
					putc(c, stdin);
					
					if (getc(stdin))
					{
					
					}
				}
				
			}
			
			if (!(textOut == 1 | listOut == 1 |compActive == 1))
			{
				int bVal = getc(FP0[readerCount]);
				
				if (verActive == 1)
				{
					sPrint(strToN(i, 10), "\t", strToN(bVal, 10), "\n");
				}
				
				putc(bVal, FP1[readerCount]);
			}
			
		}
		
		
		if (verActive == 1 & compActive == 0)
		{
			t1[readerCount] = clock();
					
			sPrint(strToN(readerCount, 10), "\t", strToN( ( (float)index / (inSVal + (float)fileSize0/((float)index_2*(float)RVal))) * 100, 10), "\%", "\t", strToN(((long)t1[readerCount] - (long)t0) / 1000, 10), ".", strToN(((long)t1[readerCount] - (long)t0) % 1000, 10), "\n");
			
		}
		
		
		index += 1;
		

	}
	
	
	fclose(FP0[readerCount]);
	
	fclose(FP1[readerCount]);
}


void readerLoop0(void *);
void readerLoop1(void *);
void readerLoop2(void *);
void readerLoop3(void *);
void readerLoop4(void *);
void readerLoop5(void *);
void readerLoop6(void *);
void readerLoop7(void *);
void readerLoop8(void *);
void readerLoop9(void *);
void readerLoop10(void *);
void readerLoop11(void *);
void readerLoop12(void *);
void readerLoop13(void *);


void readerLoop0(void *arg)
{
	int readerCount0 = fCount;
	
	readerF(readerCount0);
	
		_endthread();

}


void readerLoop1(void *arg)
{	
	int readerCount1 = fCount;
	
	readerF(readerCount1);
	
		_endthread();

}


void readerLoop2(void *arg)
{
	int readerCount2 = fCount;

	readerF(readerCount2);
	
		_endthread();

}


void readerLoop3(void *arg)
{
	int readerCount3 = fCount;

	readerF(readerCount3);
	
		_endthread();

}


void readerLoop4(void *arg)
{
	int readerCount4 = fCount;

	readerF(readerCount4);
	
		_endthread();
	

}


void readerLoop5(void *arg)
{
	int readerCount5 = fCount;

	readerF(readerCount5);
	
		_endthread();
	

}


void readerLoop6(void *arg)
{
	int readerCount6 = fCount;

	readerF(readerCount6);
	
		_endthread();
	

}


void readerLoop7(void *arg)
{
	int readerCount7 = fCount;

	readerF(readerCount7);
	
		_endthread();
	

}


void readerLoop8(void *arg)
{
	int readerCount8 = fCount;

	readerF(readerCount8);
	
		_endthread();
	

}


void readerLoop9(void *arg)
{
	int readerCount9 = fCount;

	readerF(readerCount9);
	
		_endthread();
	

}


void readerLoop10(void *arg)
{
	int readerCount10 = fCount;

	readerF(readerCount10);
	
		_endthread();
	

}


void readerLoop11(void *arg)
{
	int readerCount11 = fCount;

	readerF(readerCount11);
	
		_endthread();
	

}


void readerLoop12(void *arg)
{
	int readerCount12 = fCount;

	readerF(readerCount12);
	
		_endthread();
	

}


void readerLoop13(void *arg)
{
	int readerCount13 = fCount;

	readerF(readerCount13);
	
		_endthread();
	

}


void main(int argc, char *argv[])
{

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			// initialize arg as a string corresponding to the characters in the argumented	
			str arg = argv[i];	
			
			// last two arguments are the file locations (or file names if use of common directory is active
			if (i < (argc - 2) && strCompare(arg, "block") == 1)
			{
					blockActive = 1;
			
					if (argv[i] > 0)
					{
						blockVal = strToL(argv[i+1], 10);

					}
					else
					{
						SyntaxError;
					}
					
					// if the following argument corresponds to one of the characters; x bytes * 100, 1000, 1000000 blocks 
					if (strCompare(argv[i + 2], "C") == 1)
					{
						blockVal *= 100;
						
						blockVal1 = 256;
					}
					
					if (strCompare(argv[i + 2], "K") == 1)
					{
						blockVal *= 1000;
						
						blockVal1 = 2560;
					}
					
					if (strCompare(argv[i + 2], "M") == 1)
					{
						blockVal *= 1000000;
						
						blockVal1 = 2560000;
					}
			}
				
			
			if (i < (argc - 2) && strCompare(arg, "directory") == 1)
			{
				// the next argument defines the directory
				Dir = (char*)argv[i+1];
			}
			
			
			if (i < (argc - 2) && strCompare(arg, "inS") == 1)
			{
				// the next argument is where input starts
				inSVal = strToL(argv[i+1], 10);
			}
			
			
			if (i < (argc - 2) && strCompare(arg, "outS") == 1)
			{
				// the next argument is where output starts
				outSVal = strToL(argv[i+1], 10);
				
				outS = 1;
			}
			
			
			if (i < (argc - 2) && strCompare(arg, "nVal") == 1)
			{
				// total value to read
				NVal = strToL(argv[i+1], 10);
			}
			
			
			if (i < (argc - 2) && strCompare(arg, "reads") == 1)
			{
				if (strCompare(argv[i+1],"max") == 1)
				{
					modZero = 1;
					
					goto maxSkip;
				}
				
				// number of reads refers to the number of simultaneous threads
				RVal = strToL(argv[i+1], 10);
				
				if (RVal > 13)
				{
					RVal = 13;
					
					sPrint("number of reads defaults to max\n");
				}
				
				maxSkip:{};
			}
			
			
			if (i < (argc - 2) && arg[0] == '+')
			{
				// +args [c]ompare [t]text-output [v]erbose
				for (int i1 = 1; i1 < strLength(arg); i1++)
				{
					char c = arg[i1];
					
					if (c == 'c')
					{
						textOut = 0;
						
						blockActive = 0;
				
						compActive = 1;
					}		
					
					if (c == 't')
					{
						textOut = 1;
						listOut = 0;
					}

					if (c == 'l')
					{
						listOut = 1;
						textOut = 0;
					}
							
					if (c == 'v')
					{
						verActive = 1;
					}

				}
			}
			else
			{
				if (i < (argc - 2) && strCompare(arg, "com") == 1)
				{	
					// compares every byte, does not output a text file			
					textOut = 0;
					
					blockActive = 0;
				
					compActive = 1;
				}
			
			
				if (i < (argc - 2) && strCompare(arg, "txt") == 1)
				{
					// outputs a text file
					textOut = 1;
					
					if (i + 1 < (argc - 2) && argv[i + 1] > 0)
					{
						txtBase = strToL(argv[i + 1], 10);
					}
				}
			
			
				if (i < (argc - 2) && strCompare(arg, "verbose") == 1)
				{
					// verbose output
					verActive = 1;
				}
			
			}
				
		}
	}
	else
	{
		SyntaxError;
		
		goto endoffunction;
	}
	
	endofloop0:{};
	
	
	// file of bytes origin
	fileVal = (char*)argv[argc - 2];
	
	// concatenate the origin path with a mandatory angle and the file name
	fPath0 = strCat(fPath0, Dir, fileVal, NULL);
	
	fileVal = (char*)argv[argc - 1];
	
	// destination path and file
	fPath1 = strCat(fPath1, Dir, fileVal, NULL);
	
	Dir, fileVal = NULL;
	
	if (textOut == 1)
	{
		// output defaults to a text file if text output is active
		fPath1 = strCat(fPath1, ".txt", NULL);
	}
	


	
	
	if (fopen(fPath0, "rb") != NULL)
	{
		// open the path with multiple pointers for multiple threads
		fPointer0 = fopen(fPath0, "rb");
		
		fPointer0_1 = fopen(fPath0, "rb");
		
		fPointer0_2 = fopen(fPath0, "rb");
		
		fPointer0_3 = fopen(fPath0, "rb");
		
		fPointer0_4 = fopen(fPath0, "rb");
		
		fPointer0_5 = fopen(fPath0, "rb");
		
		fPointer0_6 = fopen(fPath0, "rb");
		
		fPointer0_7 = fopen(fPath0, "rb");
		
		fPointer0_8 = fopen(fPath0, "rb");
		
		fPointer0_9 = fopen(fPath0, "rb");
		
		fPointer0_10 = fopen(fPath0, "rb");
		
		fPointer0_11 = fopen(fPath0, "rb");
		
		fPointer0_12 = fopen(fPath0, "rb");
		
		fPointer0_13 = fopen(fPath0, "rb");
	}
	else
	{
		sPrint("file does not exist", "\n");
		
		goto endoffunction;
	}
	
	
	if (fopen(fPath1, "rb") != NULL && compActive == 0)
	{
		sPrint("overwrite file?", "\n");
		
		int c;
		
		
			putc(c, stdin);
		
			switch (getc(stdin))
			{
				case 'y':
					// write binary for new file with multiple pointers for multiple threads
					
					if (outS == 0)
					{
						fPointer1 = fopen(fPath1, "wb");
					
						fPointer1_1 = fopen(fPath1, "wb");
					
						fPointer1_2 = fopen(fPath1, "wb");
					
						fPointer1_3 = fopen(fPath1, "wb");
					
						fPointer1_4 = fopen(fPath1, "wb");
					
						fPointer1_5 = fopen(fPath1, "wb");
					
						fPointer1_6 = fopen(fPath1, "wb");
					
						fPointer1_7 = fopen(fPath1, "wb");
					
						fPointer1_8 = fopen(fPath1, "wb");
					
						fPointer1_9 = fopen(fPath1, "wb");
					
						fPointer1_10 = fopen(fPath1, "wb");
					
						fPointer1_11 = fopen(fPath1, "wb");
					
						fPointer1_12 = fopen(fPath1, "wb");
					
						fPointer1_13 = fopen(fPath1, "wb");
					}
					else
					{
						fPointer1 = fopen(fPath1,"ab");
						
						fPointer1_1 = fopen(fPath1,"ab");
						
						fPointer1_2 = fopen(fPath1,"ab");
						
						fPointer1_3 = fopen(fPath1,"ab");
						
						fPointer1_4 = fopen(fPath1,"ab");
						
						fPointer1_5 = fopen(fPath1,"ab");
						
						fPointer1_6 = fopen(fPath1,"ab");
						
						fPointer1_7 = fopen(fPath1,"ab");
						
						fPointer1_8 = fopen(fPath1,"ab");
						
						fPointer1_9 = fopen(fPath1,"ab");
						
						fPointer1_10 = fopen(fPath1,"ab");
						
						fPointer1_11 = fopen(fPath1,"ab");
						
						fPointer1_12 = fopen(fPath1,"ab");
						
						fPointer1_13 = fopen(fPath1,"ab");
					}
					
					printf("\033[A\033[K\033[A");
					sPrint("file overwrite: ", fPath1, "\n"); 
					
					goto endofloop1;
					
				case 'n':
					printf("\033[A\033[K\033[A");
					
					if (NVal != 0)
					{
						fPointer1 = fopen(fPath1, "a");
						
						RVal = 1;
						
						sPrint("file append: ", fPath1, "\n"); 
					
						goto endofloop1;
					}
					else
					{
						goto endoffunction;
					}
					
					
				default:
					sPrint("invalid input", "\n");
					goto endoffunction;
			}
		
		
	}
	else
	{
		if (compActive == 0)
		{
			sPrint("file creation: ", fPath1, "\n");
		
			fPointer1 = fopen(fPath1, "wb");
		
			fPointer1_1 = fopen(fPath1, "wb");
					
			fPointer1_2 = fopen(fPath1, "wb");
					
			fPointer1_3 = fopen(fPath1, "wb");
						
			fPointer1_4 = fopen(fPath1, "wb");

			fPointer1_5 = fopen(fPath1, "wb");
					
			fPointer1_6 = fopen(fPath1, "wb");
					
			fPointer1_7 = fopen(fPath1, "wb");
					
			fPointer1_8 = fopen(fPath1, "wb");
					
			fPointer1_9 = fopen(fPath1, "wb");
					
			fPointer1_10 = fopen(fPath1, "wb");
					
			fPointer1_11 = fopen(fPath1, "wb");
					
			fPointer1_12 = fopen(fPath1, "wb");
					
			fPointer1_13 = fopen(fPath1, "wb");			


		}
		else
		{
			// read binary only for file comparison
			fPointer1 = fopen(fPath1, "rb");
			
			fPointer1_1 = fopen(fPath1, "rb");
					
			fPointer1_2 = fopen(fPath1, "rb");
					
			fPointer1_3 = fopen(fPath1, "rb");
						
			fPointer1_4 = fopen(fPath1, "rb");

			fPointer1_5 = fopen(fPath1, "rb");
					
			fPointer1_6 = fopen(fPath1, "rb");
					
			fPointer1_7 = fopen(fPath1, "rb");
					
			fPointer1_8 = fopen(fPath1, "rb");
					
			fPointer1_9 = fopen(fPath1, "rb");
					
			fPointer1_10 = fopen(fPath1, "rb");
					
			fPointer1_11 = fopen(fPath1, "rb");
					
			fPointer1_12 = fopen(fPath1, "rb");
					
			fPointer1_13 = fopen(fPath1, "rb");
		}
	}

	endofloop1:{};	 
	

	// gets the number of bytes
	fseek(fPointer0, 0, SEEK_END);
	
	fileSize0 = ftell(fPointer0);
	
	if (NVal < fileSize0 && NVal != 0)
	{
		fileSize0 = NVal * blockVal;
	}
	
	if (modZero == 1)
	{
		RVal = 14;
		
		modCheck:{};
		
		if (fileSize0%RVal > 0)
		{
			RVal--;
			
			goto modCheck;
		}
	}
	
	printf("%d reads\n",RVal);
	


	
	t0 = clock();
	
	t1 = calloc(15, sizeof(clock_t));
	
	//chmod(fPath1, 0777);
	
	blockVal1, fPath0, fPath1 = NULL;
	
	// initialise super array entries with origin file pointers
	FP0 = calloc(14, sizeof(fPointer0));
	
	FP0[0] = fPointer0;
	
	FP0[1] = fPointer0_1;
	
	FP0[2] = fPointer0_2;
	
	FP0[3] = fPointer0_3;
	
	FP0[4] = fPointer0_4;
	
	FP0[5] = fPointer0_5;
	
	FP0[6] = fPointer0_6;
	
	FP0[7] = fPointer0_7;
	
	FP0[8] = fPointer0_8;
	
	FP0[9] = fPointer0_9;
	
	FP0[10] = fPointer0_10;
	
	FP0[11] = fPointer0_11;
	
	FP0[12] = fPointer0_12;
	
	FP0[13] = fPointer0_13;
	
	// initialise super array entries with destination file pointers
	FP1 = calloc(14, sizeof(fPointer1));
	
	FP1[0] = fPointer1;
	
	FP1[1] = fPointer1_1;
	
	FP1[2] = fPointer1_2;
	
	FP1[3] = fPointer1_3;
	
	FP1[4] = fPointer1_4;
	
	FP1[5] = fPointer1_5;
	
	FP1[6] = fPointer1_6;
	
	FP1[7] = fPointer1_7;
	
	FP1[8] = fPointer1_8;
	
	FP1[9] = fPointer1_9;
	
	FP1[10] = fPointer1_10;
	
	FP1[11] = fPointer1_11;
	
	FP1[12] = fPointer1_12;
	
	FP1[13] = fPointer1_13;
	
	
	Buffers = arrayS(Tshort, blockVal + blockVal1, RVal);
	
	
	
	HANDLE tango_0, tango_1, tango_2, tango_3, tango_4, tango_5, tango_6, tango_7, tango_8, tango_9, tango_10, tango_11, tango_12, tango_13;
	
	
	for (int i = 0; i < RVal; i++)
	{		
		
		if (fCount == 0)
		{
			tango_0 = (HANDLE)_beginthread(readerLoop0,0,NULL);
			
			fCount++;
			
			WaitForSingleObject(tango_0,INFINITE);
			
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_1 = (HANDLE)_beginthread(readerLoop1,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_1,INFINITE);
					
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_2 = (HANDLE)_beginthread(readerLoop2,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_2,INFINITE);
								
				}
		}
				
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_3 = (HANDLE)_beginthread(readerLoop3,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_3,INFINITE);
										
				}
		}
				
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_4 = (HANDLE)_beginthread(readerLoop4,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_4,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_5 = (HANDLE)_beginthread(readerLoop5,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_5,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_6 = (HANDLE)_beginthread(readerLoop6,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_6,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_7 = (HANDLE)_beginthread(readerLoop7,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_7,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_8 = (HANDLE)_beginthread(readerLoop8,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_8,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_9 = (HANDLE)_beginthread(readerLoop9,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_9,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_9 = (HANDLE)_beginthread(readerLoop9,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_9,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_10 = (HANDLE)_beginthread(readerLoop10,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_10,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_11 = (HANDLE)_beginthread(readerLoop11,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_11,INFINITE);
										
				}
		}
		
		if (fCount == i)
		{
				if ((i * blockVal) < fileSize0)
				{
					tango_12 = (HANDLE)_beginthread(readerLoop12,0,NULL);
			
					fCount++;
			
					WaitForSingleObject(tango_12,INFINITE);
										
				}
		}
		

	}
	
	
	t1[13] = clock();
				
	sPrint("100\%", "\t", strToN(((long)t1[13] - (long)t0) / 1000, 10), ".", strToN(((long)t1[13] - (long)t0) % 1000, 10), " kilocycles", "\n");

	
	
	
	
	
	endoffunction:{};
	
}
