#include <ntddk.h>
#include <wdm.h>
#include <wdf.h>
#include <ntifs.h>

#include <initguid.h>
#include <guiddef.h>

#include <fwpstypes.h>
#include <fwpmtypes.h>

#include <fwpvi.h>

#include <fwpmk.h>
#include <fwpsk.h>

DRIVER_INITIALIZE DriverEntry;

char *addressList;

int addrL = 0;

static long long power(char base, char N)
{
	long long rVal = 1;

	for (int i = 0; i < N; i++)
	{
		rVal *= base;
	}

	return rVal;
}

static void NTAPI KmdfMacFilter(
	[in] const FWPS_INCOMING_VALUES0* valIn,
	[in] const FWPS_INCOMING_METADATA_VALUES* valInMeta,
	[in] FWPM_FILTER0 foxtrot
)
{
	GUID ethIn;

	ethIn = FWPM_LAYER_INBOUND_MAC_FRAME_ETHERNET;

	UINT64 macIn = valIn->incomingValue[FWPS_FIELD_INBOUND_MAC_FRAME_ETHERNET_MAC_REMOTE_ADDRESS].value.uint64;

	UINT64 addrMac;

	for (int i = 0; i < addrL / 6; i++)
	{
		addrMac = 0;

		for (int i_0 = 0; i_0 < 6; i_0++)
		{
			addrMac += addressList[i * 6 + i_0] * power(256, 5 - i_0);
		}

		if (addrMac != macIn)
		{
			goto filterDecision;
		}
		else {
			goto skipFilterDecision;
		}
	}

	filterDecision:{};

	foxtrot.layerKey = ethIn;
	foxtrot.action.type = FWP_ACTION_BLOCK;

	NTSTATUS filterResult;

	HANDLE foxtrotHotel;

	filterResult = FwpmEngineOpen0(
		NULL,
		RPC_C_AUTHN_WINNT,
		NULL,
		NULL,
		&foxtrotHotel
	);

	filterResult = FwpmFilterAdd0(
		foxtrotHotel,
		&foxtrot,
		NULL,
		NULL
	);

	skipFilterDecision:{};
}


////////////////////////////////////////////////////////////////////////////////



static NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
)
{
	NTSTATUS status = STATUS_SUCCESS;

	OBJECT_ATTRIBUTES objectAttributes;

	UNICODE_STRING regKeyPath;
	
	RtlInitUnicodeString(&regKeyPath, L"\\Registry\\Machine\\Software\\foxcom\\macfilter");

	HANDLE regObjectHandle;

	InitializeObjectAttributes(
		&objectAttributes,
		&regKeyPath,
		OBJ_PERMANENT,
		regObjectHandle,
		NULL
	);

	PUNICODE_STRING regClassString;

	NTSTATUS keyStatus;
		
	keyStatus = ZwCreateKey(
		&regObjectHandle,
		KEY_ALL_ACCESS,
		&objectAttributes,
		NULL,
		regClassString,
		REG_OPTION_NON_VOLATILE,
		NULL
		);

	if (keyStatus != STATUS_SUCCESS)
	{
		goto endoffunction;
	}

	PVOID valueNameData;
	LPDWORD valueLength = 64;

	DWORD addrDecrement = 0;
	DWORD i = 0;

	addressList = ExAllocatePoolWithTag(PagedPool, 1, 'rdda');

	ULONG* ZwSizeVal;

	while (1 > 0)
	{
		keyStatus = ZwEnumerateKey(
			regObjectHandle,
			i,
			KeyNameInformation,
			valueNameData,
			sizeof(KEY_NAME_INFORMATION),
			&ZwSizeVal
		);

		if (keyStatus == STATUS_NO_MORE_ENTRIES)
		{
			goto breakWhile;
		}
		if (keyStatus == STATUS_BUFFER_OVERFLOW)
		{
			goto skipWhileLoop;
		}

		PKEY_NAME_INFORMATION keyInfo = valueNameData;

		WCHAR* keyName;

		keyName = &(keyInfo->Name[0]);

		keyName += keyInfo->NameLength;

		*keyName = NULL;

		keyName -= keyInfo->NameLength;

		PULONG lengthResult;

		keyStatus = ZwQueryValueKey(
			regObjectHandle,
			keyName,
			KeyValueFullInformation,
			valueNameData,
			sizeof(KEY_VALUE_FULL_INFORMATION),
			lengthResult
		);

		PKEY_VALUE_FULL_INFORMATION keyValueInfo = valueNameData;

		WCHAR* macChar;

		macChar = &keyValueInfo + keyValueInfo->DataOffset;

		WCHAR characters[16] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9',L'a',L'b',L'c',L'd',L'e',L'f'};

		for (int i_v = 0; i_v < 12; i_v += 2)
		{
			int n_0 = -1;
			int n_1 = -1;

			for (int i_c = 0; i_c < 16; i_c++)
			{
				if (characters[i_c] == macChar[i_v])
				{
					n_0 = i_c;
				}
				if (characters[i_c] == macChar[i_v + 1])
				{
					n_1 = i_c;
				}
				if (n_0 != -1 && n_1 != -1)
				{
					break;
				}
				else
				{
					addressList -= i_v;
					addrDecrement++;

					goto skipAddressIncrement;
				}
			}

			*addressList = 16 * n_0 + n_1;

			addressList++;
		}

		skipAddressIncrement: {};

		i++;

		skipWhileLoop:{};
	}

	breakWhile:{};

	addrL = (i - addrDecrement) * 6;

	addressList -= addrL;

	ZwClose(regObjectHandle);

	FWPS_CALLOUT0 driverCallout = { 0 };

	GUID calloutGUID = { "CEF5C31A5F4A9C7A143C1573E3F12837" };

	driverCallout.calloutKey = calloutGUID;

	driverCallout.classifyFn = KmdfMacFilter;

	HANDLE engineHandle;

	FwpmEngineOpen0(
		NULL,
		RPC_C_AUTHN_WINNT,
		NULL,
		NULL,
		engineHandle
	);

	FwpmCalloutAdd(
		engineHandle,
		&driverCallout,
		NULL,
		NULL
	);

	endoffunction:{};


	return status;
}
