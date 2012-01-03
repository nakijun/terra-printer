#ifndef __TDK_WIN32_ERROR_H
#define __TDK_WIN32_ERROR_H

//#pragma once

#include <Windows.h>

class TdkWin32Error
{
public:
	
	// Throws an exception corresponding to the given
	// Win32 Error code. GUID is the CLSID of the component
	// throwing error.
	static HRESULT DispatchWin32Error(DWORD dwError,
					REFCLSID clsid, LPCTSTR szSource,
					DWORD dwHelpContext,
					LPCTSTR szHelpFileName);

	// Throws the given error code and the message
	// corresponding to the code. If the code is a
	// standard code and no message is provided, then
	// the message is extracted from the system.
	static HRESULT DispatchError(HRESULT hError,
					REFCLSID clsid, LPCTSTR szSource,
					LPCTSTR szDescription,
					DWORD dwHelpContext,
					LPCTSTR szHelpFileName);
};

#endif

