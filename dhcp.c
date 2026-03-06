#include "winsock2.h"
#include "ws2tcpip.h"
#include "iphlpapi.h"
#include "ws2tcpip.h"
#include "windows.h"

#include "stdio.h"
#include "stdlib.h"

#include "strings.h"

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\MsWSock.Lib")

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\WS2_32.Lib")

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\iphlpapi.lib")

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


/////////////////////////////////////////


BOOL sErr(SOCKET sierra)
{	
	if (sierra == INVALID_SOCKET)
	{
		printf("invalid socket: ");
		
		int socketErr = WSAGetLastError();
		
		printf(" %d, ",socketErr);
		
		switch (socketErr)
		{
			case WSANOTINITIALISED:
				printf("wsastartup call must initialize the socket first.\n");
				return FALSE;
				
			case WSAENETDOWN:
				printf("network subsystem failed.\n");
				return FALSE;
				
			case WSAEAFNOSUPPORT:
				printf("specified address family not supported.\n");
				return FALSE;
				
			case WSAEFAULT:
				printf("buffer or to paramters are not part of user address space or tolen is too small.\n");
				return FALSE;
				
			case WSAEINPROGRESS:
				printf("blocking windows sockets 1.1 call in progress or service provider is still processing a callback function.\n");
				return FALSE;
				
				
			case WSAEINVAL:
				printf("group not valid or wsaprotocol_info struct incomplete or socket triple <af,type,and protocol> not supported.\n");
				return FALSE;
				
			case WSAEINVALIDPROVIDER:
				printf("service provider returned a version other than 2.2.\n");
				return FALSE;
				
			case WSAEINVALIDPROCTABLE:
				printf("service provider returned an invalid or incomplete procedure table.\n");
				return FALSE;
				
			case WSAEMFILE:
				printf("no more socket descriptors available.\n");
				return FALSE;
				
			case WSAENOBUFS:
				printf("no buffer space available, cannot create socket.\n");
				return FALSE;
				
			case WSAEPROTONOSUPPORT:
				printf("protocol not supported.\n");
				return FALSE;
				
			case WSAEPROTOTYPE:
				printf("specified protocol is the wrong type for the socket.\n");
				return FALSE;
			
			default:
				printf("undefined error.\n");
				return FALSE;
		}
	}
	
	return TRUE;
}


///////////////////////////////////////


void assignData(int lowerBoundIn, int lowerBoundOut, int magnitude, void* alphaIn, void* alphaOut)
{
	BYTE* alpha_primeIn = alphaIn;
	alpha_primeIn += lowerBoundIn;
	
	BYTE* alpha_primeOut = alphaOut;
	alpha_primeOut += lowerBoundOut;
	
	for (int i = 0; i < magnitude; i++)
	{
		*alpha_primeOut = *alpha_primeIn;
		
		alpha_primeIn++;
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


BOOL sockErrSwitch(int sockErr)
{	
	if (sockErr != 0)
	{
		printf("socket error: ");
		
		sockErr = WSAGetLastError();
		
		printf(" %d, ",sockErr);
	
		switch (sockErr)
		{
			case WSANOTINITIALISED:
				printf("must call wsastartup first\n");
				return FALSE;
				
			case WSAENETDOWN:
				printf("network subsystem failure.\n");
				return FALSE;
				
			case WSAENOTSOCK:
				printf("descriptor is not a socket.\n");
				return FALSE;
				
			case WSAEINPROGRESS:
				printf("block windows sockets 1.1 call in progress, or the service provider is still processing a callback function.\n");
				return FALSE;
				
			case WSAEINTR:
				printf("blocking windows socket 1.1 call canceled through wsacancelblockingcall.\n");
				return FALSE;
				
			case WSAEWOULDBLOCK:
				printf("socket is nonblocking, but l_onoff member of linger structure is set to nonzero and l_linger of linger struct has a non-zero timeout.\n");
				return FALSE;
			
			case WSAEFAULT:
				printf("invalid pointer address or incorrect buffer size used in the socket function call.\n");
				return FALSE;
		
			default:
				printf("unknown error.\n");
				return FALSE;
		}
	}
	
	return TRUE;
}


///////////////////////////////////////


void main(int argc, str* argv)
{	
	if (argc != 8)
	{
		printf("use args: <server ipv4> <gateway ipv4> <gateway mask> <client ipv4> <requested ipv4> <client mac> <adapter index>\n");
		
		goto endoffunction;
	}
	
	BYTE* server = calloc(4,sizeof(BYTE));
	
	ip4StrToAlloc(
		argv[1],
		server
	);
	
	BYTE* gateway = calloc(4,sizeof(BYTE));
	
	ip4StrToAlloc(
		argv[2],
		gateway
	);
	
	BYTE* maskArray = calloc(4,sizeof(BYTE));
	
	ip4StrToAlloc(
		argv[3],
		maskArray
	);
	
	BYTE* client = calloc(4,sizeof(BYTE));
	
	ip4StrToAlloc(
		argv[4],
		client
	);
	
	BYTE* requested = calloc(4,sizeof(BYTE));
	
	ip4StrToAlloc(
		argv[5],
		requested
	);
	
	str macString = argv[6];
	
	BYTE* macArray = calloc(6,sizeof(BYTE));
	
	macToAlloc(
		0,				// index
		macString,		// string in
		macArray		// byte allocation delta
	);
	
	str adapterIndexS = argv[7];
	
	for (int i = 0; i < strLength(adapterIndexS); i++)
	{
		if (adapterIndexS[i] < '0' | adapterIndexS[i] > '9')
		{
			printf("must use base 10 digits for adapter index\n");
			
			goto endoffunction;
		}
	}
	
	
	printf("gateway: ");
	
	for (int i = 0; i < 4; i++)
	{
		printf("%d",gateway[i]);
		
		if (i < 3)
		{
			printf(".");
		}
	}
	
	printf("\n");
	
	printf("requested: ");
	
	for (int i = 0; i < 4; i++)
	{
		printf("%d",requested[i]);
		
		if (i < 3)
		{
			printf(".");
		}
	}
	
	printf("\n");
	
	WSADATA whiskeyData = { 0 };
	
	LPBYTE whiskeyVersion = calloc(2,sizeof(BYTE));
	
	int byteCount = 0;
	
	while (byteCount < 2)
	{
		*whiskeyVersion = (BYTE)2;
		whiskeyVersion++;
		byteCount++;
	}
	
	whiskeyVersion -= byteCount;
	
	int startupErr = WSAStartup(
		(WORD)whiskeyVersion,			// wVersionRequired
		&whiskeyData					// lpWSAData
	);
	
	if (startupErr != 0)
	{
		printf("couldn't start socket: ");
		
		switch (startupErr)
		{
			case WSASYSNOTREADY:
				printf("underlying network subsystem not ready for coms\n");
				goto endoffunction;
			
			case WSAVERNOTSUPPORTED:
				printf("the requested version of winsock not supported\n");
				goto endoffunction;
				
			case WSAEINPROGRESS:
				printf("blocking windows socket 1.1 op in progress\n");
				goto endoffunction;
				
			case WSAEPROCLIM:
				printf("task limit reached\n");
				goto endoffunction;
				
			case WSAEFAULT:
				printf("lpWSAData parameter is not a valid pointer\n");
				goto endoffunction;
			
			default:
				printf("undefined error\n");
				goto endoffunction;
		}
	}
	
	int sockErr;
	
	////////////////////
	// dhcp request send
	////////////////////
	

	SOCKET dhcpSocket;
	
	dhcpSocket = socket(
		AF_INET,			// af
		SOCK_DGRAM,			// type
		IPPROTO_UDP			// protocol
	);
	
	BOOL dhcpSocketErr = sErr(dhcpSocket);
	
	if (dhcpSocketErr == FALSE)
	{
		goto endoffunction;
	}
	
	
	struct sockaddr_in sourceAddr = { 0 };
	
	sourceAddr.sin_family = AF_INET;
	sourceAddr.sin_port = htons(68);
	
	sourceAddr.sin_addr.S_un.S_addr = 0;
	
	for (int i = 0; i < 4; i++)
	{
		sourceAddr.sin_addr.S_un.S_addr += client[3-i] * power(256, 3-i);
	}
	
	sockErr = bind(
		dhcpSocket,								// s (socket)
		(struct sockaddr*)&sourceAddr,			// sockaddr *name (source info)
		sizeof(sourceAddr)						// namelen
	);
	
	BOOL bravo;
	
	bravo = sockErrSwitch(sockErr);
	
	if (bravo == FALSE)
	{
		goto endoffunction;
	}
	
	struct sockaddr_in destinationAddr = { 0 };
	
	destinationAddr.sin_family = AF_INET;
	destinationAddr.sin_port = htons(67);
	
	destinationAddr.sin_addr.S_un.S_addr = 0;
	
	for (int i = 0; i < 4; i++)
	{
		destinationAddr.sin_addr.S_un.S_addr += gateway[3-i] * power(256, 3-i);
	}
	
	
	
	char* dhcpRequestData;
	int maxSize = 295;
	int difference = 28;
	int dRDL = maxSize - (difference + 1);
	int dRDFlags = 0;
	
	dRDFlags = dRDFlags | MSG_DONTROUTE;
	
	BYTE* payload = calloc(dRDL,sizeof(BYTE));
	
	payload[0] = (BYTE)(0x01);			// OP
	payload[1] = (BYTE)(0x01);			// HTYPE
	payload[2] = (BYTE)(0x06);			// HLEN
	payload[3] = (BYTE)(0x00);			// HOPS
	
	payload[4] = (BYTE)rand();			// xid[0]
	payload[5] = (BYTE)rand();			// xid[1]
	payload[6] = (BYTE)rand();			// xid[2]
	payload[7] = (BYTE)rand();			// xid[3]
	
	assignData(
		0,					// lowerBoundIn
		40 - difference,	// lowerBoundOut
		4,					// magnitude
		client,				// alphaIn
		payload				// alphaOut
	);
	
	assignData(
		0,					// lowerBoundIn
		56 - difference,	// lowerBoundOut
		6,					// magnitude
		macArray,			// alphaIn
		payload				// alphaOut
	);
	
	// magic number
	payload[264 - difference] = (BYTE)(0x63);
	payload[265 - difference] = (BYTE)(0x82);
	payload[266 - difference] = (BYTE)(0x53);
	payload[267 - difference] = (BYTE)(0x63);
	
	// option: dhcp message Type
	payload[268 - difference] = (BYTE)(0x35);
	payload[269 - difference] = (BYTE)(0x01);
	payload[270 - difference] = (BYTE)(0x03);
	
	// option: client identifier
	payload[271 - difference] = (BYTE)(0x3d);
	payload[272 - difference] = (BYTE)(0x07);
	payload[273 - difference] = (BYTE)(0x01);
	
	assignData(
		0,					// lowerBoundIn
		274 - difference,	// lowerBoundOut
		6,					// magnitude
		macArray,			// alphaIn
		payload				// alphaOut
	);
	
	// option: requested ipv4 address
	payload[280 - difference] = (BYTE)(0x32);
	payload[281 - difference] = (BYTE)(0x04);
	
	assignData(
		0,					// lowerBoundIn
		282 - difference,	// lowerBoundOut
		4,					// magnitude
		requested,			// alphaIn
		payload				// alphaOut
	);
	
	// option: dhcp server address
	payload[286 - difference] = (BYTE)(0x36);
	payload[287 - difference] = (BYTE)(0x04);
	
	assignData(
		0,					// lowerBoundIn
		288 - difference,	// lowerBoundOut
		4,					// magnitude
		server,				// alphaIn
		payload				// alphaOut
	);
	
	// option: end
	
	payload[292 - difference] = (BYTE)(0xff);
	payload[293 - difference] = (BYTE)(0x00);
	payload[294 - difference] = (BYTE)(0x00);
	
	
	////////
	// send
	////////
	
	int sockSend;
	
	sockSend = sendto(
		dhcpSocket,				// s (socket)
		payload,		// data *buffer
		dRDL,					// len
		dRDFlags,				// flags
		&destinationAddr,		// *to (port address data)
		sizeof(destinationAddr)	// tolen
	);
	
	bravo = sErr(sockSend);
	
	if (bravo == FALSE)
	{
		goto endoffunction;
	}
	
	sockErr = closesocket(dhcpSocket);
	
	dhcpSocketErr = sockErrSwitch(sockErr);
	
	if (dhcpSocketErr == FALSE)
	{
		goto endoffunction;
	}
	
	
	///////////////////////////////
	// set up the new ipv4 address
	///////////////////////////////
	
	u_long sourceAddrChange = 0;
	
	for (int i = 0; i < 4; i++)
	{
		sourceAddrChange += requested[3-i] * power(256, 3-i);
	}
	
	u_long maskAddress = 0;
	
	for (int i = 0; i < 4; i++)
	{
		maskAddress += maskArray[3-i] * power(256, 3-i);
	}
	
	PULONG ipChangeContext;
	PULONG ipInstance;
	
	DWORD adapterIndex = strToL(adapterIndexS,10);
	
	AddIPAddress(
		sourceAddrChange,			// new address
		maskAddress,				// ip mask
		adapterIndex,				// ifindex
		ipChangeContext,			// NTEcontext
		ipInstance					// NTEinstance
	);
	
	
	/////////////////////
	// dhcp offer receive
	/////////////////////
	
	dhcpSocket = socket(
		AF_INET,			// af
		SOCK_DGRAM,			// type
		IPPROTO_UDP			// protocol
	);
	
	dhcpSocketErr = sErr(dhcpSocket);
	
	if (dhcpSocketErr == FALSE)
	{
		goto endoffunction;
	}
	
	sourceAddr.sin_family = AF_INET;
	sourceAddr.sin_port = htons(68);
	
	sourceAddr.sin_addr.S_un.S_addr = 0;
	
	for (int i = 0; i < 4; i++)
	{
		sourceAddr.sin_addr.S_un.S_addr += requested[3-i] * power(256, 3-i);
	}
	
	sockErr = bind(
		dhcpSocket,				// s (socket)
		&sourceAddr,			// sockaddr *name (source info)
		sizeof(sourceAddr)		// namelen
	);
	
	bravo = sockErrSwitch(sockErr);
	
	if (bravo == FALSE)
	{
		goto endoffunction;
	}
	
	dRDL = 303 - 28;
	
	payload = calloc(dRDL,sizeof(BYTE));
	
	
	int sockRecv;
	
	sockRecv = recv(
		dhcpSocket,				// s (socket)
		payload,				// *buf (payload in)
		dRDL,					// len (of payload)
		0						// flags
	);
	
	BYTE* newAddress = calloc(4,sizeof(BYTE));
	
	
	assignData(
		44 - 28,			// lowerBoundIn
		0,					// lowerBoundOut
		4,					// magnitude
		payload,			// alphaIn
		newAddress			// alphaOut
	);
	
	
	// in case of a nak response
	
	if (
		newAddress[0] == 0 
		&& newAddress[1] == 0
		&& newAddress[2] == 0
		&& newAddress[3] == 0
	)
	{
		sourceAddrChange = 0;
		
		for (int i = 0; i < 4; i++)
		{
			sourceAddrChange += requested[3-i] * power(256, 3-i);
		}
		
		
		AddIPAddress(
			sourceAddrChange,		// new address
			maskAddress,				// ip mask
			adapterIndex,				// ifindex
			ipChangeContext,			// NTEcontext
			ipInstance					// NTEinstance
		);
	}
	
	printf("new address: ");
	
	for (int i = 0; i < 4; i++)
	{
		printf("%d",newAddress[i]);
		
		if (i < 3)
		{
			printf(".");
		}
	}
	
	printf("\n");
	
	
	endoffunction:{};
	
	sockErr = closesocket(dhcpSocket);
}