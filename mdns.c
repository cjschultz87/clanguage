#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "WinDNS.h"
#include "windnsdef.h"
#include "winerror.h"

#include "strings.h"

#pragma comment(lib,"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\dnsapi.lib")

DNS_QUERY_RESULT rValS;
PDNS_QUERY_RESULT rVal = &rValS;

MDNS_QUERY_CALLBACK MdnsQueryCallback;

void WINAPI MdnsQueryCallback(PVOID pQueryContext, PMDNS_QUERY_HANDLE pQueryHandle, PDNS_QUERY_RESULT pQueryResults)
{
	rVal = &pQueryResults;
	
	DNS_RECORDA romeoS;
	
	PDNS_RECORD romeo = &romeoS;
	
	romeo = rVal->pQueryRecords;
	
	if (romeo == NULL)
	{
		printf("null record\n");
		
		goto endoffunction;
	}

	char* sierra;
	
	DWORD L = romeo->Data.TXT.dwStringCount;
	
	for (int i = 0; i < L; i++)
	{
		sierra = romeo->Data.TXT.pStringArray[i];
		printf("%s\n",sierra);
	}
	
	endoffunction:{};
	
	DnsRecordListFree(pQueryRecords,DnsFreeRecordList);
	DnsRecordListFree(romeo,DnsFreeRecordList);
	
	return;
}

void main(int argc, char** argv)
{
	if (argc < 3)
	{
		goto endoffunction;
	}
	
	int L = strLength(argv[1]);
	
	PCWSTR queryVal = (PCWSTR)calloc(L,sizeof(PCWSTR));
	
	mbstowcs_s(NULL,queryVal,L,argv[1],_TRUNCATE);
	
	MDNS_QUERY_REQUEST reqS = {0};
	
	PMDNS_QUERY_REQUEST req = &reqS;
	
	req->Version = DNS_QUERY_REQUEST_VERSION1;
	req->Query = queryVal;
	req->QueryType = DNS_TYPE_ALL;
	req->QueryOptions = DNS_QUERY_STANDARD;
	req->InterfaceIndex = (ULONG)strToL(argv[2],10);
	req->pQueryCallback = MdnsQueryCallback;
	
	MDNS_QUERY_HANDLE hotelS = {0};
	
	PMDNS_QUERY_HANDLE hotel = &hotelS;
	
	DNS_STATUS deltaStat;

	deltaStat = DnsStartMulticastQuery(req,hotel);
	
	if (deltaStat != ERROR_SUCCESS)
	{
		printf("dns_status error\n");
		
		goto endoffunction;
	}
	
	Sleep(5000);
	
	endoffunction:{};
	
	DnsStopMulticastQuery(hotel);
}