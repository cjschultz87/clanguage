#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <array.h>
#include <strings.h>
#include <time.h>

str path_in = NULL;
str path_out = NULL;

short fEncryption = 0;

str fKey = NULL;

int dice()
{	
	int rVal = 0;
	
	for (int i = 0; i < 8; i++)
	{
		short exp = 7-i;
		
		int power = 1;
		
		for (int i_1 = 0; i_1 < exp; i_1++)
		{
			power *= 2;
		}
		
		rVal += (clock()%2) * power;
	}
	
	return rVal;
}

array rotate(array alpha, int n, short direction)
{
	if (direction < 0 & direction > 1)
	{
		return	alpha;
	}
	
	array bravo = arrayF(Tshort,alpha.Length);
	
	if (direction == 1)
	{
		for (int i = 0; i < bravo.Length; i++)
		{
			bravo.loc[i] = alpha.loc[(i+n)%alpha.Length];
		}
	}
	if (direction == 0)
	{
		for (int i = 0; i < bravo.Length; i++)
		{
			bravo.loc[i] = alpha.loc[((alpha.Length) + (i-n))%alpha.Length];
		}
	}
	
	return bravo;
}

void main(int argc, char **argv)
{
	
	if (argc != 3)
	{
		sPrint("<path> <key>\n");
		goto endoffunction;
	}
	else
	{
		path_in = argv[1];
		
		if (strCompare(strSubI(strLength(path_in)-3,3,path_in),".fe") == 1)
		{
			fEncryption = 1;
			
			path_out = strSubI(0,strLength(path_in)-3,path_in);
		}
		else
		{
			path_out = strCat(path_in,".fe",NULL);
		}
		
		fKey = argv[2];
	}
	
	if (strLength(fKey) % 8 != 0)
	{
		int fKey_L = strLength(fKey);
		
		int fKey_L8 = 8 * (fKey_L/8) + 8;
		
		for (int i = 0; i < fKey_L8 - fKey_L; i++)
		{
			str fKey_prime = fKey;
			
			str fKey_prime_element = strSubI(i%fKey_L,(i+1)%fKey_L,argv[2]);
			
			fKey = strCat(fKey_prime_element,fKey,NULL);
		}
	}
	
	array fK_0 = arrayF(Tshort,strLength(fKey));
	
	
	
	FILE *foxtrot_0, *foxtrot_1;
	
	
	if (fopen(path_in,"rb") != NULL)
	{
		foxtrot_0 = fopen(path_in,"rb");
	}
	else
	{
		sPrint("file does not exist\n");
		
		goto endoffunction;
	}
	
	foxtrot_1 = fopen(path_out,"wb");
	
	fseek(foxtrot_0,0,SEEK_END);
	
	unsigned long long fSize0 = ftell(foxtrot_0);
	
	fseek(foxtrot_0,0,0);
	
	array fSIERRA = arrayF(Tshort,fSize0 * 8);
	
	for (int i = 0; i < fSize0; i++)
	{
		fseek(foxtrot_0,i,0);
		
		int fox_byte = getc(foxtrot_0);
		
		array fS_0 = arrayF(Tshort,8);
		
		int i_1 = 0;
		
		while (fox_byte > 0)
		{
			
			fS_0.loc[i_1] = fox_byte % 2;
			
			fox_byte /= 2;
			i_1++;
		}
		
		for (i_1 = 0; i_1 < 8; i_1++)
		{
			fSIERRA.loc[(i*8)+i_1] = fS_0.loc[7-i_1];
		}
	}
	
	//////////////////////
	sPrint("input ready\n");
	
	
	
	
	int rotation_november = 0;
	
	for (int i = 0; i < fK_0.Length; i++)
	{
		fK_0.loc[i] = fKey[i];
		
		rotation_november += fK_0.loc[i];
	}
	
	int november_1 = 0;
	
	for (int i = 0; i < fSIERRA.Length; i++)
	{
		november_1 += fSIERRA.loc[i] % rotation_november;
	}
	
	rotation_november = (rotation_november + november_1) % rotation_november;
	
	fK_0 = rotate(fK_0,rotation_november,1);
	
	array fK_1 = arrayF(Tshort,64);
	
	int fK_center = (fK_1.Length / 2) - (fK_0.Length / 2);
	
	for (int i = fK_center; i < fK_center + fK_0.Length; i++)
	{
		fK_1.loc[i] = fK_0.loc[i - fK_center];
	}
	
	if (fK_0.Length < 64)
	{
		
		int fK_lima	= fK_0.Length;
		int fK_L = fK_0.Length;
		
		while (fK_lima < 64)
		{
			
			fK_0 = rotate(fK_0,5,0);
		
			int i = fK_center - 4;
			
			while (i < fK_center + 2)
			{
				fK_1.loc[i] = fK_0.loc[i-(fK_center - 4)];
				
				i++;
			}
			
			fK_1.loc[i] = fK_0.loc[3 + fK_center - (i)];
			
			i++;
			
			fK_1.loc[i] = fK_0.loc[3];
			
			i = fK_center + fK_lima;
			
			
			while (i < fK_center + fK_lima + 2)
			{
				fK_1.loc[i] = fK_0.loc[fK_0.Length - (1+ i%fK_0.Length)];
				
				i++;
			}
			
			fK_1.loc[i] = fK_0.loc[2];
			
			i++;
			
			fK_1.loc[i] = fK_0.loc[fK_0.Length - (1+ i%fK_0.Length)];
			
			fK_lima += 8;
			
			fK_center -= 4;
			
		}
	}
	
	if (fK_0.Length > 64)
	{
		for (int i = 0; i < 64; i++)
		{
			fK_1.loc[i] = fK_0.loc[i];
		}
	}
	///////////////////////////////////
	sPrint("passkey\n.....expanded\n");
	
	
	array kSIERRA = arrayF(Tshort,8*64);
	
	for (int i = 0; i < 64; i++)
	{
		for (int i_1 = 0; i_1 < 8; i_1++)
		{	
			kSIERRA.loc[i*8+i_1] = fK_1.loc[i] % 2; 
			
			fK_1.loc[i] /= 2;
		}
	}
	
	kSIERRA = rotate(kSIERRA,rotation_november,1);
	
	fK_0 = arrayF(Tshort,0);
	fK_1 = arrayF(Tshort,64);
	
	for (int i = 0; i < 64; i++)
	{
		array fS_0 = arrayF(Tshort,8);
		
		for (int i_1 = 0; i_1 < 8; i_1++)
		{
			fS_0.loc[i_1] = kSIERRA.loc[(i*8)+i_1];
		}
		
		fS_0 = rotate(fS_0,i,1);
		
		int sierra = 0;
		
		for (int i_1 = 0; i_1 < 8; i_1++)
		{
			int exp = 1;
			
			for (int i_2 = 0; i_2 < i_1; i_2++)
			{
				exp *= 2;
			}
			
			sierra += fS_0.loc[i_1] * exp;
		}
		
		fK_1.loc[i] = sierra;
	}
	
	/////////////////////////
	sPrint(".....rotated\n");
	
	
	
	
	
	
	
	
	
	
	if (fEncryption == 0)
	{
		for (int i = 0; i < fK_1.Length; i += 8)
		{
			/////////////////////
			printf("%d/8\n",i/8);
			
			fSIERRA = rotate(fSIERRA,rotation_november,rotation_november%2);
			
			for (int i_1 = 0; i_1 < fSize0; i_1 += 2)
			{	
				int sierra_byte = 0;
		
				int i_2;
		
				for (i_2 = 0; i_2 < 8; i_2++)
				{
					int exp = 1;
					
					for (int i_3 = 0; i_3 < 7 - i_2; i_3++)
					{
						exp *= 2;
					}
					
					sierra_byte += fSIERRA.loc[(i_1*8)+i_2] * exp;
					
				}
				
				sierra_byte = sierra_byte ^ fK_1.loc[i];
				
				array fS_0 = arrayF(Tshort,8);
				
				i_2 = 0;
				
				while (sierra_byte > 0)
				{	
					fS_0.loc[i_2] = sierra_byte % 2;
					
					sierra_byte /= 2;
					i_2++;
				}
				
				for (i_2 = 0; i_2 < fS_0.Length; i_2++)
				{
					fSIERRA.loc[(i_1*8)+i_2] = fS_0.loc[7-i_2];
				}
			}
		}
	}
	
	if (fEncryption == 1)
	{
		for (int i = fK_1.Length - 8; i >=0; i -= 8)
		{	
			/////////////////////
			printf("%d/8\n",i/8);
	
			for (int i_1 = 0; i_1 < fSize0; i_1 += 2)
			{	
				int sierra_byte = 0;
		
				int i_2;
		
				for (i_2 = 0; i_2 < 8; i_2++)
				{
					int exp = 1;
					
					for (int i_3 = 0; i_3 < 7 - i_2; i_3++)
					{
						exp *= 2;
					}
					
					sierra_byte += fSIERRA.loc[(i_1*8)+i_2] * exp;
					
				}
				
				sierra_byte = sierra_byte ^ fK_1.loc[i];
				
				array fS_0 = arrayF(Tshort,8);
				
				i_2 = 0;
				
				while (sierra_byte > 0)
				{	
					fS_0.loc[i_2] = sierra_byte % 2;
					
					sierra_byte /= 2;
					i_2++;
				}
				
				for (i_2 = 0; i_2 < fS_0.Length; i_2++)
				{
					fSIERRA.loc[(i_1*8)+i_2] = fS_0.loc[7-i_2];
				}
			}
			
			fSIERRA = rotate(fSIERRA,5,0);
		}
	}
	
	if (fEncryption != 0 & fEncryption != 1)
	{
		sPrint("error\n");
		
		goto endoffunction;
	}
	
	
	for (int i = 0; i < fSize0; i++)
	{
		int sierra_byte = 0;
			
		for (int i_1 = 0; i_1 < 8; i_1++)
		{
			int exp = 1;
				
			for (int i_2 = 0; i_2 < 7-i_1; i_2++)
			{
				exp *= 2;
			}
				
			sierra_byte += fSIERRA.loc[(i*8)+i_1] * exp;
		}
		
		fseek(foxtrot_1,i,0);
		
		putc(sierra_byte,foxtrot_1);
	}
	
	
	endoffunction:{};
	
	sPrint("encrypted\n");
	
	fclose(foxtrot_0);
	fclose(foxtrot_1);
}
