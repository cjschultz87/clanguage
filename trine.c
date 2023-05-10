#include <trine.h>

void main()
{
	trine a = tri(5);
	trine b = tri(9);
	
	sTrine A = sTri(a,b,NULL);
	
	
	for (int i = 0; i < A.AlphaLength; i++)
	{
		printf("\n");
		
		for (int i1 = 0; i1 < A.Length; i1++)
		{
			printf("%d", A.AlphaLoc[i].loc[i1]);
		}
	}
	printf("\n");
	
}