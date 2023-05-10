#include <stdlib.h>
#include <stdio.h>
#include <array.h>
#include <strings.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>


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

// number of blocks initialised as zero

unsigned long long NVal = 0;

//total file size defined

unsigned long long fileSize0;

int fCount = 0;

int textOut = 0;

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


// threads for multithread processing

int waitThread0, waitThread1, waitThread2, waitThread3, waitThread4, waitThread5, waitThread6, waitThread7, waitThread8, waitThread9, waitThread10, waitThread11, waitThread12, waitThread13;

pthread_t *thread;

//file pointers

FILE *fPointer0, *fPointer0_1, *fPointer0_2, *fPointer0_3, *fPointer0_4, *fPointer0_5, *fPointer0_6, *fPointer0_7, *fPointer0_8, *fPointer0_9, *fPointer0_10, *fPointer0_11, *fPointer0_12, *fPointer0_13, *fPointer1, *fPointer1_1, *fPointer1_2, *fPointer1_3, *fPointer1_4, *fPointer1_5, *fPointer1_6, *fPointer1_7, *fPointer1_8, *fPointer1_9, *fPointer1_10, *fPointer1_11, *fPointer1_12, *fPointer1_13;

FILE **FP0, **FP1;

DIR *dPointer0, *dPointer1;

clock_t t0, *t1;




void readerF(int readerCount)
{
	if (blockActive == 1)
	{
		// the allocation of buffers is an array of short integers of size blockVal + blockVal1
		Buffers.AlphaLoc[readerCount] = arrayF(Tshort, blockVal + blockVal1);
	}


	for (unsigned long long i = (fileSize0 / RVal) * readerCount; (float)i < (((float)fileSize0 / (float)RVal)) * (float)(readerCount + 1); i += blockVal )
	{	
		fseek(FP0[readerCount], inSVal + i, 0);
		
		fseek(FP1[readerCount], outSVal + i, 0);

		
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
			if (textOut == 1 | verActive == 1)
			{				
						
					if (textOut == 1 && i != 0)
					{
			
						putc('\n', FP1[readerCount]);
						
						outSVal++;
					
					}
						
					if (verActive == 1)
					{
						sPrint(strToN(i, 10), "\t");
					}
						
			
						long long numberVal = i;
						
						int digit;
		
						int arrayLength = 0;
		
						for (int iConv = 0; iConv >= 0; iConv++)
						{
							numberVal /= 16;
							
							if (numberVal == 0)
							{
								arrayLength = iConv;
				
								goto arrayLengthComputed0;
							}
						}
		
							arrayLengthComputed0:{};
		
							array digitsArray = arrayF(Tshort, arrayLength);
		
						numberVal = i;
		
						for (int iConv = 0; iConv >= 0; iConv++)
						{
							digit = numberVal % 16;
			
							digitsArray.loc[iConv] = digit;
			
							numberVal /= 16;
			
							if (numberVal == 0)
							{
								goto hexConverted0;
							}
						}
		
						hexConverted0:{};
		
						for (int d = digitsArray.Length; d >= 0; d--)
						{
							if (digitsArray.loc[d] < 10)
							{
								if (verActive == 1)
								{
									sPrint(strToN(digitsArray.loc[d], 10));
								}
								
								
								if (textOut == 1)
								{
									putc(strToN(digitsArray.loc[d], 10)[0], FP1[readerCount]);
								
									outSVal++;
								}
							}
							else
							{
								char digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
							
								if (verActive == 1)
								{
									printf("%c", digits[digitsArray.loc[d]]);
								}
								
								if (textOut == 1)
								{
									putc(digits[digitsArray.loc[d]], FP1[readerCount]);
								
									outSVal++;
								}
							}
						}
						
						if (verActive == 1)
						{
							sPrint("\t");
							
						}
						
						if (textOut == 1)
						{
							putc('\t', FP1[readerCount]);
						
							outSVal++;
						}
					
					
					
					
					str sVal0 = strToN(getc(FP0[readerCount]), txtBase);
					
					if (verActive == 1)
					{
						sPrint(sVal0, "\t");
					}
					
					if (textOut == 1)
					{
						for (long i1 = 0; i1 < strLength(sVal0); i1++)
						{
							putc(sVal0[i1], FP1[readerCount]);
					
							outSVal++;
						}
					
						putc('\t', FP1[readerCount]);
						
						outSVal++;
					}
							
						numberVal = strToL(sVal0, 10);
		
						arrayLength = 0;
		
						for (int iConv = 0; iConv >= 0; iConv++)
						{
							numberVal /= 16;
							
							if (numberVal == 0)
							{
								arrayLength = iConv;
				
								goto arrayLengthComputed1;
							}
						}
		
							arrayLengthComputed1:{};
		
							digitsArray = arrayF(Tshort, arrayLength);
		
						numberVal = strToL(sVal0, 10);
		
						for (int iConv = 0; iConv >= 0; iConv++)
						{
							digit = numberVal % 16;
			
							digitsArray.loc[iConv] = digit;
			
							numberVal /= 16;
			
							if (numberVal == 0)
							{
								goto hexConverted1;
							}
						}
		
						hexConverted1:{};
		
						for (int d = digitsArray.Length; d >= 0; d--)
						{
							if (digitsArray.loc[d] < 10)
							{
								if (verActive == 1)
								{
									sPrint(strToN(digitsArray.loc[d], 10));
								}
								
								if(textOut == 1)
								{
									putc(strToN(digitsArray.loc[d], 10)[0], FP1[readerCount]);
								
									outSVal++;
								}
							}
							else
							{
								char digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
								
								if (verActive == 1)
								{
									printf("%c", digits[digitsArray.loc[d]]);
								}

								if (textOut == 1)
								{								
									putc(digits[digitsArray.loc[d]], FP1[readerCount]);
								
									outSVal++;
								}
							}
						}
						
						if (verActive == 1)
						{
							sPrint("\t");
						}
						
						
						if (textOut == 1)
						{
							putc('\t', FP1[readerCount]);
						
							outSVal++;
						}
						
						
						
						numberVal = strToL(sVal0, 10);
		
						arrayLength = 0;
		
						for (int iConv = 0; iConv >= 0; iConv++)
						{
							numberVal /= 2;
							
							if (numberVal == 0)
							{
								arrayLength = iConv;
				
								goto arrayLengthComputed2;
							}
						}
		
							arrayLengthComputed2:{};
		
							digitsArray = arrayF(Tshort, arrayLength);
		
						numberVal = strToL(sVal0, 10);
		
						for (int iConv = 0; iConv >= 0; iConv++)
						{
							digit = numberVal % 2;
			
							digitsArray.loc[iConv] = digit;
			
							numberVal /= 2;
			
							if (numberVal == 0)
							{
								goto binaryConverted;
							}
						}
		
						binaryConverted:{};
						
						for (int lz = 7; lz > digitsArray.Length; lz--)
						{
							if (verActive == 1)
							{
								sPrint("0");
							}
						
							if (textOut == 1)
							{
								putc('0', FP1[readerCount]);
							
								outSVal++;
							}
						}
		
						for (int d = digitsArray.Length; d >= 0; d--)
						{
								if (verActive == 1)
								{
									sPrint(strToN(digitsArray.loc[d], 10));
								}
								
								if (textOut == 1)
								{
									putc(strToN(digitsArray.loc[d], 10)[0], FP1[readerCount]);
								
									outSVal++;
								}
						}
						
						if (verActive == 1)
						{
							sPrint("\n");
						}
					
						if (textOut == 1)
						{
							putc('\t', FP1[readerCount]);
						
							putc(getc(FP0[readerCount]), FP1[readerCount]);
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
			
			if (!(textOut == 1 | compActive == 1))
			{
				int bVal = getc(FP0[readerCount]);
				
				if (verActive == 1)
				{
					sPrint(strToN(i, 10), "\t", strToN(bVal, 10), "\n");
				}
				
				putc(bVal, FP1[readerCount]);
			}
			
		}
		
		
		if (verActive == 0 & compActive == 0)
		{
			t1[readerCount] = clock();
					
			sPrint(strToN(readerCount, 10), "\t", strToN( ( (float)i / ((float)fileSize0)) * 100, 10), "\%", "\t", strToN(((long)t1[readerCount] - (long)t0) / 1000, 10), ".", strToN(((long)t1[readerCount] - (long)t0) % 1000, 10), "\n");
			
		}
		

	}
	
	
	fclose(FP0[readerCount]);
	
	fclose(FP1[readerCount]);
}




void* readerLoop0(void *arg)
{
	int readerCount0 = fCount;
		
		waitThread0 = 0;
	
	readerF(readerCount0);
	
		pthread_exit(NULL);

}


void* readerLoop1(void *arg)
{	
	int readerCount1 = fCount;
	
		waitThread1 = 0;
	
	readerF(readerCount1);
	
		pthread_exit(NULL);

}


void* readerLoop2(void *arg)
{
	int readerCount2 = fCount;
		
		waitThread2 = 0;

	readerF(readerCount2);
	
		pthread_exit(NULL);

}


void* readerLoop3(void *arg)
{
	int readerCount3 = fCount;
	
		waitThread3 = 0;

	readerF(readerCount3);
	
		pthread_exit(NULL);

}


void* readerLoop4(void *arg)
{
	int readerCount4 = fCount;

	readerF(readerCount4);
	
	waitThread4 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop5(void *arg)
{
	int readerCount5 = fCount;

	readerF(readerCount5);
	
	waitThread5 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop6(void *arg)
{
	int readerCount6 = fCount;

	readerF(readerCount6);
	
	waitThread6 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop7(void *arg)
{
	int readerCount7 = fCount;

	readerF(readerCount7);
	
	waitThread7 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop8(void *arg)
{
	int readerCount8 = fCount;

	readerF(readerCount8);
	
	waitThread8 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop9(void *arg)
{
	int readerCount9 = fCount;

	readerF(readerCount9);
	
	waitThread9 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop10(void *arg)
{
	int readerCount10 = fCount;

	readerF(readerCount10);
	
	waitThread10 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop11(void *arg)
{
	int readerCount11 = fCount;

	readerF(readerCount11);
	
	waitThread11 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop12(void *arg)
{
	int readerCount12 = fCount;

	readerF(readerCount12);
	
	waitThread12 = 0;
	
		pthread_exit(NULL);
	

}


void* readerLoop13(void *arg)
{
	int readerCount13 = fCount;

	readerF(readerCount13);
	
	waitThread13 = 0;
	
		pthread_exit(NULL);
	

}



str* dirEntriesF(str fPath, DIR *dirPointer)
{
	int dirLength;

	
	for (int i = 0; 1 > 0; i++)
	{

		if (readdir(dirPointer) == NULL)
		{
			dirLength = i;
			
			goto dir0;
		}
	}
	
	dir0:{};
	
	rewinddir(dirPointer);

	str *entriesArray = calloc(Tlong, dirLength);
	
	str dirEntry;
	
	struct dirent *dirVals;
	
	for (int i = 0; i < dirLength; i++)
	{		
		dirVals = readdir(dirPointer);

		dirEntry = dirVals->d_name;
		
		entriesArray[i] = dirEntry;

	}
	
	dir1:{};
	
	return entriesArray;
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
			}
			
			
			if (i < (argc - 2) && strCompare(arg, "nVal") == 1)
			{
				// total value to read
				NVal = strToL(argv[i+1], 10);
			}
			
			
			if (i < (argc - 2) && strCompare(arg, "reads") == 1)
			{
				// number of reads refers to the number of simultaneous threads
				RVal = strToL(argv[i+1], 10);
				
				if (RVal > 14)
				{
					RVal = 14;
					
					sPrint("number of reads defaults to max\n");
				}
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
	
	if (Dir[1] != '/')
	{
		// angle refers to a directory value
		Dir = strCat(Dir, "/", NULL);
	}
	
	
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
	
	
	
	
	
	// check if the origin directory exists
	if (opendir(fPath0) != NULL)
	{
		int dirIndex = 0;

		// if the origin directory exists then check if the destination directory exists
		if (!(opendir(fPath1) != NULL))
		{
			if (textOut == 0)
			{
				sPrint("cannot write directory to regular file\n");
				
				goto endoffunction;
			}
		}
		
		// origin file pointer
		dPointer0 = opendir(fPath0);
		
		// destination file pointer
		dPointer1 = opendir(fPath1);

	
		dir0:{};
	
		
		if (dirIndex == 0);
		{
			mkdir(fPath1, 0777);
		}
		
		// if there aren't any directory entries
		if (dirEntries[0] == NULL)
		{
			// stores the first directory as a string
			dirEntries = dirEntriesF(fPath0, dPointer0);
		}
		
		dir1:{};
	
		dirIndex++;
		
		if(dirEntries[dirIndex] == NULL)
		{
			goto dir2;
		}
		
		if (opendir(fPath0) != NULL)
		{
			goto dir0;
		}
		else
		{
			goto dir1;
		}
	}
	
	dir2:{};
	
	
	// if the path doesn't exist
	if (opendir(fPath0) != NULL)
	{
		if (AlphaIndex > 0)
		{
			fPath0 = strDel(fPath0, dirEntries[AlphaIndex - 1]);
			
			fPath1 = strDel(fPath1, dirEntries[AlphaIndex - 1]);
		}
	
		fPath0 = strCat(fPath0, dirEntries[AlphaIndex]);
		
		fPath1 = strCat(fPath1, dirEntries[AlphaIndex]);
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
	
	t0 = clock();
	
	t1 = calloc(15, sizeof(clock_t));
	
	chmod(fPath1, 0777);
	
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
	
	// create a super array for file buffers with the given block value
	Buffers = arrayS(Tshort, blockVal, 14);
	
	thread = calloc(RVal, sizeof(pthread_t));
	
	
	for (int i = 0; i < RVal; i++)
	{		
		
		if (fCount == 0)
		{
			rc[i] = pthread_create(&thread[i], NULL, readerLoop0, NULL);
			
			waitThread0 = 1;
			
			while (waitThread0 == 1)
			{
			
			}
			
			fCount++;
			
		}
		
		if (fCount == i && waitThread0 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop1, NULL);
					
					waitThread1 = 1;

					while (waitThread1 == 1)
					{
			
					}
					
					fCount++;
					
				}
		}
		
		if (fCount == i && waitThread1 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop2, NULL);
					
					waitThread2 = 1;

					while (waitThread2 == 1)
					{
			
					}	
									
					fCount++;
								
				}
		}
				
		if (fCount == i && waitThread2 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop3, NULL);
					
					waitThread3 = 1;

					while (waitThread3 == 1)
					{
			
					}	
									
					fCount++;
										
				}
		}
				
		if (fCount == i && waitThread3 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop4, NULL);
					
					waitThread4 = 1;

					while (waitThread4 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread4 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop5, NULL);
					
					waitThread5 = 1;

					while (waitThread5 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread5 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop6, NULL);
					
					waitThread6 = 1;

					while (waitThread6 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread6 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop7, NULL);
					
					waitThread7 = 1;

					while (waitThread7 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread7 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop8, NULL);
					
					waitThread8 = 1;

					while (waitThread8 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread8 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop9, NULL);
					
					waitThread9 = 1;

					while (waitThread9 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread9 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop10, NULL);
					
					waitThread10 = 1;

					while (waitThread10 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread10 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop11, NULL);
					
					waitThread11 = 1;

					while (waitThread11 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread11 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop12, NULL);
					
					waitThread12 = 1;

					while (waitThread12 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		
		if (fCount == i && waitThread12 == 0)
		{
				if ((i * blockVal) < fileSize0)
				{
					rc[i] = pthread_create(&thread[i], NULL, readerLoop13, NULL);
					
					waitThread13 = 1;

					while (waitThread13 == 1)
					{
			
					}
											
					fCount++;
										
				}
		}
		

	}	

	for (int i = 0; i < fCount; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	
	t1[13] = clock();
				
	sPrint("100\%", "\t", strToN(((long)t1[13] - (long)t0) / 1000, 10), ".", strToN(((long)t1[13] - (long)t0) % 1000, 10), " kilocycles", "\n");

	
	
	
	
	
	endoffunction:{};
	
}
