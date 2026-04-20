#include "winsock2.h"
#include "ws2tcpip.h"

#include "windows.h"

#include "time.h"

#include "stdio.h"
#include "stdlib.h"

#include "strings.h"

#include "pcap.h"

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\MsWSock.Lib")

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\WS2_32.Lib")

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\OneCore.Lib")

#pragma comment(lib, "C:\\Program Files\\WpdPack\\Lib\\x64\\wpcap.lib")



/////////////////////////////////////////

int power(int base, int N)
{
	int rVal = 1;
	
	for (int i = 0; i < N; i++)
	{
		rVal *= base;
	}
	
	return rVal;
}


///////////////////////////////////////


void checksum(unsigned short *alphaIn, int length, void* out, int outL)
{
	//BYTE* alphaInB;
	//alphaInB = alphaIn;
	
	unsigned long sum = 0;
	
	for (int i = 0; i < length; i++)
	{
		sum += alphaIn[i];
		
		if (sum & 0xFFFF0000)
		{
			sum &= 0xFFFF;
			sum++;
		}
		// from davie and petersen, see "computer networks: a systems approach"
	}
	
	unsigned short sum_prime = ~(sum & 0xFFFF);
	
	BYTE* bOut;
	
	bOut = out;
	
	BYTE* sierra;
	
	sierra = &sum_prime;
	
	for (int i = 0; i < outL; i++)
	{
		*bOut = sierra[i];
		
		bOut++;
	}
}


///////////////////////////////////////

void assignData(int lowerBoundIn, int lowerBoundOut, int magnitude, void* alphaIn, void* alphaOut)
{	
	BYTE* alpha_primeIn = alphaIn;
	if (magnitude < 0)
	{
		alpha_primeIn += lowerBoundIn + abs(magnitude) - 1;
	}
	else
	{
		alpha_primeIn += lowerBoundIn;
	}
	
	BYTE* alpha_primeOut = alphaOut;
	alpha_primeOut += lowerBoundOut;
	
	for (int i = 0; i < abs(magnitude); i++)
	{
		*alpha_primeOut = *alpha_primeIn;
		if (magnitude < 0)
		{
			alpha_primeIn--;
		}
		else
		{
			alpha_primeIn++;
		}
		
		alpha_primeOut++;
	}
}


///////////////////////////////////////

void macToAlloc(int index, str sierra, void* delta)
{
	BYTE* delta_prime;
	
	delta_prime = delta + index;
	
	BYTE bravo = 0;
	
	str hexValues = "0123456789ABCDEF";
	
	for (int i = 0; i < strLength(sierra); i += 3)
	{
		bravo = 0;
		
		for (int i_b = 0; i_b < 2; i_b++)
		{
			for (int i_h = 0; i_h < strLength(hexValues); i_h++)
			{
				if (hexValues[i_h] == sierra[i + i_b] | hexValues[i_h] == sierra[i + i_b] - ('A' - 'a'))
				{
					bravo += (BYTE)(i_h * power(16, 1 - i_b));
				}
			}
		}
		
		*delta_prime = bravo;
		
		delta_prime++;
	}
}


///////////////////////////////////////

void ip4StrToAlloc(str address, void* alphaIn)
{
	BYTE* alpha_primeIn = alphaIn;
	
	int index = 0;
	int addrL = strLength(address);
	int byte_count = 0;
	
	while (byte_count < 4)
	{
		int index_up = index;
		
		while (index_up < addrL)
		{
			if (address[index_up] == '.')
			{
				break;
			}
			
			index_up++;
		}
		
		str byte = calloc(
			index_up - index,
			sizeof(BYTE)
		);
		
		for (int i = 0; i < index_up - index; i++)
		{
			byte[i] = (BYTE)address[index + i];
		}
		
		*alpha_primeIn = (BYTE)strToL(
			byte,
			10
		);
		
		index = index_up + 1;
		
		alpha_primeIn++;
		byte_count++;
	}
}


///////////////////////////////////////


BOOL eCheck()
{
	HANDLE hotel = NULL;
	
	if (OpenProcessToken(
		GetCurrentProcess(),
		TOKEN_QUERY,
		&hotel))
	{
		TOKEN_ELEVATION eToken;
		
		DWORD teSize = sizeof(TOKEN_ELEVATION);
		
		if (GetTokenInformation(
				hotel,
				TokenElevation,
				&eToken,
				sizeof(eToken),
				&teSize
			) && eToken.TokenIsElevated)
			{
				return TRUE;
			}
	}
	
	return FALSE;
}


///////////////////////////////////////

void main(int argc, str* argv)
{
	BOOL elevation = eCheck();
	
	if (elevation == FALSE)
	{
		printf("command requires elevation.\n");
		
		goto endoffunction;
	}
		
	if (argc < 5)
	{
		printf("invalid args\n");
		
		goto endoffunction;
	}
	
	unsigned int iMax = strToL(argv[argc - 6],10);
	str server = argv[argc - 5];
	str mask = argv[argc - 4];
	str macIn = argv[argc - 3];
	str ipIn = argv[argc - 2];
	str iota = argv[argc - 1];


	
	////////////////
	//allocate frame
	////////////////
	
	unsigned short fL = 42;
	
	BYTE* frame = calloc(fL, sizeof(BYTE));
	
	//////////////////////
	//start of 802.x frame
	//////////////////////
	BYTE* mac = calloc(6, sizeof(BYTE));
	
	for (int i = 0; i < 6; i++)
	{
		frame[i] = (BYTE)255;
	}
	
	macToAlloc(
		0,
		macIn,
		mac
	);
	
	for (int i = 0; i < 6; i++)
	{
		frame[6 + i] = mac[i];
	}
	
	frame[12] = 8;
	frame[13] = 6;
	
	///////////////////
	//start of arp data
	///////////////////
	
	frame[15] = (BYTE)1;	// htype ethernet for frame[0:1]
	
	unsigned short protocol = 0x0800;
	
	BYTE* protocolB;
	
	protocolB = &protocol;
	
	for (int i = 1; i >= 0; i--)
	{
		frame[16 + i] = *protocolB;
		
		protocolB++;
	}
	
	frame[18] = (BYTE)6;	// hardware length, ethernet address
	
	frame[19] = (BYTE)4;	// protocol length, ipv4 address
	
	frame[21] = (BYTE)1;	// operation, arp request
	
	mac = calloc(6, sizeof(BYTE));
	
	macToAlloc(
		0,
		macIn,
		mac
	);
	
	for (int i = 0; i < 6; i++)
	{
		frame[22 + i] = mac[i];
	}
	// sender mac
	
	BYTE* ipAlpha = calloc(4, sizeof(BYTE));
	
	ip4StrToAlloc(
		ipIn,
		ipAlpha
	);
	
	for (int i = 0; i < 4; i++)
	{
		frame[28 + i] = ipAlpha[i];
	}
	// sender ipv4 address
	
	for (int i = 0; i < 6; i++)
	{
		frame[32 + i] = 0;
	}
	// target mac
	
	BYTE* maskAlpha = calloc(4, sizeof(BYTE));
	
	ip4StrToAlloc(
		mask,
		maskAlpha
	);
	
	unsigned int index = 0;
	
	condition0:{};
	
	ipAlpha = calloc(4, sizeof(BYTE));
	
	ip4StrToAlloc(
		server,
		ipAlpha
	);
	
	for (int i = 0; i < 4; i++)
	{
		ipAlpha[i] &= maskAlpha[i];
		
		if (maskAlpha[i] < 255)
		{
			BYTE mBravo = 0xFF ^ maskAlpha[i];
			
			srand(clock());
			
			BYTE bravo = 2 + ((BYTE)rand() % (mBravo - 2));
			
			Sleep(bravo);
			
			ipAlpha[i] = bravo;
		}
		
		frame[38 + i] = ipAlpha[i];
	}
	
	
	
	//////////////
	//start socket
	//////////////
	
	char perr[PCAP_ERRBUF_SIZE];
	
	pcap_if_t *devices;
	
	int delta = pcap_findalldevs(&devices,perr);
	
	pcap_if_t *deviceInstant;
	
	deviceInstant = devices;
	
	str iotaDevice;
	
	while (deviceInstant->next != NULL)
	{
		/*
		printf(
			"%s\n%s\n\n",
			deviceInstant->name,
			deviceInstant->description
		);
		*/
		
		for (int i = 1; i < strLength(deviceInstant->description); i++)
		{
			if (
				strCompare(
					strSubI(
						0,
						i,
						deviceInstant->description
					),
					iota
				) == 1
			)
			{
				iotaDevice = deviceInstant->name;
				
				goto devicecheck;
			}
		}
		
		deviceInstant = deviceInstant->next;
	}
	
	printf("couldn't find device.\n");
	pcap_freealldevs(devices);
	
	goto endoffunction;
	
	devicecheck:{};
	
	pcap_t *p;

	p = pcap_create(iotaDevice,perr);
	
	if (p == NULL)
	{
		printf("couldn't start pcap handle.\n");
		printf("%s\n",perr);
		
		pcap_freealldevs(devices);
		
		goto endoffunction;
	}
	
	if (pcap_activate(p) != 0)
	{
		printf("could not activate handle.\n");
		
		goto endoffunction;
	}
	
	pcap_sendpacket(
		p,
		frame,
		fL
	);
	
	pcap_freealldevs(devices);
	
	index++;
	
	if (index < iMax)
	{
		srand(time(NULL));
		
		Sleep(255 % ((rand() % (255 - 50)) + 50));
		
		goto condition0;
	}
	
	endoffunction:{};
}
