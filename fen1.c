#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <array.h>
#include <strings.h>
#include <time.h>

str Dir_in = NULL;

str Dir_out = NULL;

str file = NULL;

int fEncryption = 0;

str fKey = NULL;

array fK;

array fKilo;

superArray SIERRA;

int seed(clock_t c)
{
	int rVal = c % 258;
	
	return rVal;
}

void main(int argc, char *argv[])
{
	if (argc > 2)
	{
		if (argc > 4)
		{
			if (strCompare(argv[3],"o") == 1 && argc == 5)
			{
				Dir_in = argv[1];
				
				file = argv[2];
				
				Dir_out = argv[4];
				
				fKey = argv[5];
			}
			else
			{
				sPrint("Excessive arguments", "\n");
			}
		}
		else
		{
			Dir_in = argv[1];
			
			file = argv[2];
			
			fKey = argv[3];
		}
	}
	else
	{
		sPrint("Insufficient arguments", "\n");
		
		goto endoffunction;
	}

	if (Dir_out == NULL)
	{
		Dir_out = Dir_in;
	}

	str fPath0 = strCat(Dir_in,"/",file, NULL);
	str fPath1 = NULL;
	
	if (strCompare(strSubI(strLength(fPath0)-3,3,fPath0),".fe") == 1)
	{
		fEncryption = 1;
		
		fPath1 = strCat(Dir_out,"/",strSubI(0,strLength(file)-3,file),NULL);
	}
	else
	{
		fPath1 = strCat(Dir_out,"/",file,".fe",NULL);
	}
	
	if (strLength(fKey) % 8 != 0)
	{
		for (int i = 0; i < strLength(fKey) % 8; i++)
		{
			fKey = strCat("0",fKey,NULL);
		}
	}
	
	fK = arrayF(Tshort,24);
	
	if (strLength(fKey) < 24)
	{
		for (int i = 0; i < fK.Length; i++)
		{
			if (i < (24 / 2) - (strLength(fKey) / 2))
			{
				fK.loc[i] = fKey[i%8];
			}
			if (i >= (24 / 2) - (strLength(fKey) / 2) && i <= (24 / 2) + strLength(fKey) / 2)
			{
				fK.loc[i] = fKey[i - ((24 / 2) - (strLength(fKey) / 2))];
			}
			if (i > (24 / 2) + strLength(fKey) / 2)
			{
				fK.loc[i] = fKey[8 - (i%8)];
			}
		}
	}
	
	SIERRA = arrayS(Tshort, 16, 4);
	
	for (int i = 0; i < SIERRA.Length; i++)
	{
		SIERRA.AlphaLoc[i] = arrayF(Tshort, 16);
	}
	
	fKilo = arrayF(Tshort, 24/2);
	
	for (int i = 0; i < fKilo.Length; i++)
	{
		for (int i1 = 0; i1 < 2; i1++)
		{
			fKilo.loc[i] += fK.loc[i + i1];
		}
	}
	
	DIR *dPointer0, *dPointer1;
	
	FILE *fPointer0, *fPointer1, *fPointer2;
	
	if (opendir(Dir_in) != NULL)
	{
		dPointer0 = opendir(Dir_in);
	}
	else
	{
		sPrint("directory does not exist", "\n");
		
		goto endoffunction;
	}
	
	if (opendir(Dir_out) != NULL)
	{
		dPointer0 = opendir(Dir_out);
	}
	else
	{
		sPrint("directory does not exist", "\n");
		
		goto endoffunction;
	}
	
	if (fopen(fPath0, "rb") != NULL)
	{
		fPointer0 = fopen(fPath0, "rb");
	}
	else
	{
		sPrint("file does not exist", "\n");
		
		goto endoffunction;
	}
	
	fPointer1 = fopen(fPath1, "wb");
	
	fseek(fPointer0, 0, SEEK_END);
	
	unsigned long long fSize0 = ftell(fPointer0);
	
	
	
	if (fEncryption == 0)
	{
		for (int i = 0; i < SIERRA.Length; i++)
		{
			for (int i1 = 0; i1 < SIERRA.AlphaLoc[i].Length; i1++)
			{
				
				if (i1 > 0)
				{
					
					for (int i2 = 0; i2 < SIERRA.AlphaLoc[i].Length; i2++)
					{
						startloop0:{};
						
						SIERRA.AlphaLoc[i].loc[i1] = seed(clock());
						
						for (int i3 = 0; i3 < SIERRA.AlphaLoc[i].Length; i3++)
						{
							if (i3 != i1 && SIERRA.AlphaLoc[i].loc[i1] == SIERRA.AlphaLoc[i].loc[i3])
							{
								goto startloop0;
							}
						}
					}
					
				}
				else
				{
					SIERRA.AlphaLoc[i].loc[i1] = seed(clock());
				}
			}
		}
		
		for (int i = 0; i < SIERRA.Length; i++)
		{
			for (int i1 = 0; i1 < SIERRA.AlphaLoc[i].Length; i1++)
			{
				for (int i2 = 0; i2 < fKilo.Length; i2++)
				{
					SIERRA.AlphaLoc[i].loc[i1] = SIERRA.AlphaLoc[i].loc[i1] ^ fKilo.loc[i2];
				}
			}
		}
		
		unsigned long long iota_0 = 0;
		
		unsigned long long iota_1 = 0;
		
		fseek(fPointer0, 0+iota_0, 0);
		
		fseek(fPointer1, 0+iota_1, 0);
		
		for (int i = 0; i < SIERRA.Length; i++)
		{
			for (int i1 = 0; i1 < SIERRA.AlphaLoc[i].Length; i1++)
			{
				putc(SIERRA.AlphaLoc[i].loc[i1], fPointer1);
				
				iota_1++;
			}
		}
		
		int bravo = 0;
		
		for (unsigned long long i = 0; i < fSize0; i++)
		{
			bravo = getc(fPointer0);
			
			for (int i1 = 0; i1 < SIERRA.Length; i1++)
			{
				for (int i2 = 0; i2 < SIERRA.AlphaLoc[i1].Length - 5; i2++)
				{
					bravo = bravo ^ SIERRA.AlphaLoc[i1].loc[i2];
				}
			}
			
			putc(bravo,fPointer1);
			
			iota_0++;
			iota_1++;
		}
	}
	else
	{
		unsigned long long iota_0 = 0;
		
		unsigned long long iota_1 = 0;
		
		fseek(fPointer0, 0 + iota_0, 0);
		
		for (int i = 0; i < SIERRA.Length; i++)
		{
			for (int i1 = 0; i1 < SIERRA.AlphaLoc[i].Length; i1++)
			{
				SIERRA.AlphaLoc[i].loc[i1] = getc(fPointer0);
				
				iota_0++;
			}
		}
		
		for (int i = 0; i < SIERRA.Length; i++)
		{
			for (int i1 = 0; i1 < SIERRA.AlphaLoc[i].Length; i1++)
			{
				for (int i2 = 0; i2 < fKilo.Length; i2++)
				{
					SIERRA.AlphaLoc[i].loc[i1] = SIERRA.AlphaLoc[i].loc[i1] ^ fKilo.loc[i2];
				}
			}
		}
		
		fseek(fPointer0,0+iota_0,0);
		fseek(fPointer1,0+iota_1,0);
		
		int bravo = 0;
		
		for (unsigned long long i = 0; i < fSize0 - SIERRA.Length * SIERRA.AlphaLoc[0].Length; i++)
		{
			bravo = getc(fPointer0);
			
			for (int i1 = SIERRA.Length - 1; i1 >= 0; i1--)
			{
				for (int i2 = SIERRA.AlphaLoc[i1].Length - 6; i2 >= 0; i2--)
				{
					bravo = bravo ^ SIERRA.AlphaLoc[i1].loc[i2];
				}
			}
			
			putc(bravo,fPointer1);
			
			iota_0++;
			iota_1++;
		}
		
		
	}
	
	endoffunction:{};
	
	fclose(fPointer0);
	fclose(fPointer1);
}