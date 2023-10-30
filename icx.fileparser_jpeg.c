#include "stdio.h"
#include "stdlib.h"
#include "array.h"
#include "strings.h"


str fPath;

FILE *foxtrot;

unsigned long long fL;

array foxtrot_bytes;

char textIn = 0;


str hex_str(int decimal)
{	
	return "ff";
}


void main(int argc, str *argv)
{
	fPath = argv[1];
	
	if (strCompare(strSubI(strLength(fPath)-4,4,fPath),".txt") == 1)
	{
		textIn = 1;
	}
	
	if (fopen(fPath,"r") != NULL)
	{
		if (textIn == 1)
		{
			foxtrot = fopen(fPath,"r");
		}
		else
		{
			foxtrot = fopen(fPath,"rb");
		}
	}
	else
	{
		sPrint("invalid path\n");
		goto endoffunction;
	}
	
	
	fseek(foxtrot,0,SEEK_END);
	
	fL = ftell(foxtrot);
	
	fseek(foxtrot,0,0);
	
	foxtrot_bytes = arrayF(Tshort,fL);
	
	
	str hex = "0123456789abcdef";
	
	str m16 = "cdef";
	

	
	int hexVal;
	
	str textByte;
	
	
	for (int i = 0; i < fL; i++)
	{
		if (textIn == 0)
		{	
			fseek(foxtrot,i,0);
			
			foxtrot_bytes.loc[i] = getc(foxtrot);
		}
		
		if (textIn == 1)
		{
			hexVal = 0; 
			
			i++;
			
			fseek(foxtrot,i,0);
			
			str textByte = strToN(getc(foxtrot),10);
			
			for (int i_1 = 0; i_1 < 16; i_1++)
			{
				if (textByte[0] == hex[i_1])
				{
					hexVal += 16 * i_1;
						
					goto endHexLoop0;
				}
			}
				
			endHexLoop0:{};
			
			
			i++;
			
			fseek(foxtrot,i,0);
			
			textByte = strToN(getc(foxtrot),10);
			
			for (int i_1 = 0; i_1 < 16; i_1++)
			{
				if (textByte[0] == hex[i_1])
				{
					hexVal += i_1;
						
					goto endHexLoop1;
				}
			}
				
			endHexLoop1:{};
			
			
			foxtrot_bytes.loc[i/3] = hexVal;
			
		}
	}
	
	
	
	
	int m16_start = strSubS(hex,m16);
	
	int tags_L = strLength(hex)*strLength(hex) - 1;
	
	array tags = arrayF(Tshort,tags_L);
	
	for (int i = m16_start * 16; i < tags_L; i++)
	{
		tags.loc[i] = 1;
	}
	


	int fbl;
	
	int alpha = 0;
	
	unsigned long long index = 0;
	
	unsigned long long segment_val;
	
	while (alpha == 0 & index < foxtrot_bytes.Length)
	{	
		fbl = foxtrot_bytes.loc[index];
		
		if (fbl == strToL("ff",16))
		{
			index++;
			
			segment_val = 0;
			
			fbl = foxtrot_bytes.loc[index];
			
			if (tags.loc[fbl] == 1 && (fbl >= (12*16) + 16 && fbl <= (12*16) + 25))
			{
				index++;
			}
			
			fbl = foxtrot_bytes.loc[index];
			
			if (tags.loc[fbl] == 1 && !(fbl >= (12*16) + 16 && fbl <= (12*16) + 25))
			{	
				if (fbl == strToL("da",16))
				{
					
					sPrint("start of scan: byte ", strToN(index,10),"\n");
					
					int bravo = 0;
					
					while (bravo == 0)
					{
						index++;
						
						fbl = foxtrot_bytes.loc[index];
						
						if (fbl == strToL("ff",16))
						{
							index++;
							
							fbl = foxtrot_bytes.loc[index];
							
							if (tags.loc[fbl] == 1 && !(fbl >= (12*16) + 16 && fbl <= (12*16) + 25))
							{
								index--;
								bravo = 1;
							}
							
							fbl = foxtrot_bytes.loc[index];
							
							if (fbl == strToL("d9",16))
							{
								alpha = 1;
								
								break;
							}
						}
					}
				}

				else
				{
					
					int sierra_0 = foxtrot_bytes.loc[index-1];
					int sierra_1 = foxtrot_bytes.loc[index];
					
					sPrint(strToN(sierra_0,16), strToN(sierra_1,16), ": byte ", strToN(index,10),"\n");
					
					index++;
					
					segment_val += 256 *  foxtrot_bytes.loc[index];
					
					index++;
					
					segment_val += foxtrot_bytes.loc[index];
					
					segment_val--;
				}

				
			}
			
			index += segment_val;
			
		}
		else
		{
			sPrint("Tagged length not congruent with bytes!\n");
			
			while (!(fbl == strToL("ff",16)))
			{
				fbl = foxtrot_bytes.loc[index];
				
				index++;
			}
		}
	}
	
	sPrint(strToN(index + 1,10), " bytes\n");
	
	
	endoffunction:{};
	
	fclose(foxtrot);
}