#include <Windows.h>
#include <wchar.h>
#include <LM.h>

#pragma comment(lib, "Netapi32.lib")

int wmain(int argc, WCHAR *argv[])
{
	if (argc != 5)
	{
		fwprintf(stderr, L"\nUsage: %s [Domain] [AccountOU | NULL] [Account] [Password]\n", argv[0]);
		return 1;
	}

	//NetJoinDomain
	NET_API_STATUS joinDomain;
	LPCWSTR server = NULL;	// Local computer is used
	LPCWSTR domain = (LPCWSTR)argv[1];
	LPCWSTR accountOU = (LPCWSTR)argv[2];
	LPCWSTR account = (LPCWSTR)argv[3];
	LPCWSTR password = (LPCWSTR)argv[4];
	DWORD joinOptions = NETSETUP_JOIN_DOMAIN | NETSETUP_ACCT_CREATE;

	// Here we go! 
	joinDomain = NetJoinDomain(
		server,
		domain,
		accountOU,
		account,
		password,
		joinOptions);

	if (joinDomain != NERR_Success)
	{
		fwprintf(stderr, L"Error joining to a domain, code: %u\n", joinDomain);
		return 1;
	}

	wprintf(L"Domain join completed successfully. \n");

	return 0;
}