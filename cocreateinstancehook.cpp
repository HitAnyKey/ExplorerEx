#include "cocreateinstancehook.h"
#include <stdio.h>

DWORD WINAPI BeepThread(LPVOID)
{
	Beep(1700, 200);
	return 0;
}

HRESULT CoCreateInstanceHook(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv)
{
	HRESULT res = CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
	if (res != ERROR_SUCCESS)
	{
		CreateThread(0, 0, BeepThread, 0, 0, 0);

		wchar_t* clsidstring = 0;
		StringFromCLSID(rclsid, &clsidstring);

		wchar_t* iidstring = 0;
		StringFromCLSID(riid, &iidstring);

		wprintf(L"COCREATEINSTANCE FAILED! clsid %s, riid %s\n", clsidstring, iidstring);
	}
	return res;
}
