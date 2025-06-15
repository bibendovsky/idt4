/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company. 

This file is part of the Doom 3 GPL Source Code (?Doom 3 Source Code?).  

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#include "../../idlib/precompiled.h"
#pragma hdrstop

#include "win_local.h"
#include <lmerr.h>
#include <lmcons.h>
#include <lmwksta.h>
#include <errno.h>
#include <fcntl.h>
#include <direct.h>
#include <io.h>
#include <conio.h>

#ifndef	ID_DEDICATED
#ifdef IDT4_VANILLA
#include <comdef.h>
#include <comutil.h>
#endif // IDT4_VANILLA
#include <Wbemidl.h>

#pragma comment (lib, "wbemuuid.lib")
#endif

#if !(defined(IDT4_VANILLA) || defined(IDT4_MFC))
#include <tchar.h>

namespace {

template<typename T>
class CComPtr
{
public:
	CComPtr(T* ptr = NULL) throw()
		:
		ptr_(ptr)
	{
		if (ptr_ == NULL)
		{
			return;
		}

		ptr_->AddRef();
	}

	~CComPtr()
	{
		if (ptr_ == NULL)
		{
			return;
		}

		ptr_->Release();
	}

	T* operator->() const throw()
	{
		return ptr_;
	}

	operator IUnknown*() const throw()
	{
		return ptr_;
	}

	T** operator&() throw()
	{
		assert(ptr_ == NULL);
		return &ptr_;
	}

private:
	T* ptr_;

private:
	CComPtr(const CComPtr&);
	CComPtr& operator=(const CComPtr&);
};

class CComBSTR
{
#define IDT4_PREFIX "[CComBSTR] "

public:
	explicit CComBSTR(LPCSTR chars)
		:
		bstr_()
	{
		const int wchar_size_with_null = MultiByteToWideChar(
			CP_ACP,
			MB_ERR_INVALID_CHARS,
			chars,
			-1,
			NULL,
			0);

		if (wchar_size_with_null == 0)
		{
			throw Exception(IDT4_PREFIX "Failed to get OLE-char count.");
		}

		if (wchar_size_with_null > max_wchars_with_null)
		{
			throw Exception(IDT4_PREFIX "Output string too big.");
		}

		WCHAR wchars[max_wchars_with_null];

		const int converted_size = MultiByteToWideChar(
			CP_ACP,
			MB_ERR_INVALID_CHARS,
			chars,
			-1,
			wchars,
			wchar_size_with_null);

		if (wchar_size_with_null == 0)
		{
			throw Exception(IDT4_PREFIX "Failed to convert to OLE-chars.");
		}

		bstr_ = SysAllocString(wchars);

		if (bstr_ == NULL)
		{
			throw Exception(IDT4_PREFIX "SysAllocString failed.");
		}
	}

	explicit CComBSTR(const OLECHAR* ole_chars)
		:
		bstr_()
	{
		bstr_ = SysAllocString(ole_chars);

		if (bstr_ == NULL)
		{
			throw Exception(IDT4_PREFIX "SysAllocString failed.");
		}
	}

	CComBSTR(const CComBSTR& rhs)
		:
		bstr_()
	{
		bstr_ = SysAllocString(rhs.bstr_);

		if (bstr_ == NULL)
		{
			throw Exception(IDT4_PREFIX "SysAllocString failed.");
		}
	}

	~CComBSTR()
	{
		SysFreeString(bstr_);
	}

	operator const BSTR() const throw()
	{
		return bstr_;
	}

private:
	static const int max_wchars_with_null = 128;

private:
	class Exception : public std::exception
	{
	public:
		explicit Exception(const char* message) throw()
			:
			message_(message)
		{}

		Exception(const Exception& rhs) throw()
			:
			message_(rhs.what())
		{}

		Exception& operator=(const Exception& rhs) throw()
		{
			message_ = rhs.what();
			return *this;
		}

		virtual ~Exception()
		{}

		const char* what() const throw()
		{
			return message_;
		}

	private:
		const char* message_;
	};

private:
	BSTR bstr_;

private:
	CComBSTR& operator=(const CComBSTR&);

#undef IDT4_PREFIX
};

class CComVariant : public tagVARIANT
{
public:
	CComVariant() throw()
	{
		VariantInit(this);
	}

	~CComVariant()
	{
		VariantClear(this);
	}

private:
	CComVariant(const CComVariant&);
	CComVariant& operator=(const CComVariant&);
};

} // namespace
#endif

/*
================
Sys_Milliseconds
================
*/
int Sys_Milliseconds( void ) {
	int sys_curtime;
	static int sys_timeBase;
	static bool	initialized = false;

	if ( !initialized ) {
		sys_timeBase = timeGetTime();
		initialized = true;
	}
	sys_curtime = timeGetTime() - sys_timeBase;

	return sys_curtime;
}

/*
================
Sys_GetSystemRam

	returns amount of physical memory in MB
================
*/
int Sys_GetSystemRam( void ) {
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof ( statex );
	GlobalMemoryStatusEx (&statex);
	int physRam = statex.ullTotalPhys / ( 1024 * 1024 );
	// HACK: For some reason, ullTotalPhys is sometimes off by a meg or two, so we round up to the nearest 16 megs
	physRam = ( physRam + 8 ) & ~15;
	return physRam;
}


/*
================
Sys_GetDriveFreeSpace
returns in megabytes
================
*/
int Sys_GetDriveFreeSpace( const char *path ) {
	DWORDLONG lpFreeBytesAvailable;
	DWORDLONG lpTotalNumberOfBytes;
	DWORDLONG lpTotalNumberOfFreeBytes;
	int ret = 26;
	//FIXME: see why this is failing on some machines
	if ( ::GetDiskFreeSpaceEx( path, (PULARGE_INTEGER)&lpFreeBytesAvailable, (PULARGE_INTEGER)&lpTotalNumberOfBytes, (PULARGE_INTEGER)&lpTotalNumberOfFreeBytes ) ) {
		ret = ( double )( lpFreeBytesAvailable ) / ( 1024.0 * 1024.0 );
	}
	return ret;
}


/*
================
Sys_GetVideoRam
returns in megabytes
================
*/
// IDT4-FIX-D3-BUG-004
#ifndef IDT4_VANILLA
int Sys_GetVideoRam()
{
#ifdef ID_DEDICATED
	return 0;
#else
	const DWORD max_display_devices = ~DWORD();
	DISPLAY_DEVICEW display_device;
	display_device.cb = static_cast<DWORD>(sizeof(DISPLAY_DEVICEW));

	bool found_display_device = false;

	for (DWORD i = 0; i < max_display_devices; ++i)
	{
		const BOOL enum_display_devices_result = EnumDisplayDevicesW(NULL, i, &display_device, 0);

		if (enum_display_devices_result == FALSE)
		{
			break;
		}

		if ((display_device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) == 0 ||
			(display_device.StateFlags & (DISPLAY_DEVICE_MIRRORING_DRIVER | DISPLAY_DEVICE_REMOVABLE)) != 0)
		{
			continue;
		}

		found_display_device = true;
		break;
	}

	if (!found_display_device)
	{
		return 0;
	}

	HRESULT hresult;
	IWbemLocator* wbem_locator = NULL;
	bool got_memory = false;
	DWORD wbem_size_mb = 0;

	const HRESULT co_initialize_result = CoInitialize(NULL);

	hresult = CoCreateInstance(
		CLSID_WbemLocator,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator,
		reinterpret_cast<LPVOID*>(&wbem_locator));

	if (SUCCEEDED(hresult) && wbem_locator != NULL)
	{
		const BSTR wbem_object_path = SysAllocString(L"\\\\.\\root\\cimv2");

		IWbemServices* wbem_services = NULL;

		hresult = wbem_locator->ConnectServer(
			wbem_object_path,
			NULL,
			NULL,
			NULL,
			0,
			NULL,
			NULL,
			&wbem_services);

		if (SUCCEEDED(hresult) && wbem_services != NULL)
		{
			const HMODULE ole32_module = LoadLibraryW(L"ole32.dll");

			if (ole32_module != NULL)
			{
				typedef HRESULT (WINAPI * COSETPROXYBLANKETFUNC_)(
					IUnknown* pProxy,
					DWORD dwAuthnSvc,
					DWORD dwAuthzSvc,
					OLECHAR* pServerPrincName,
					DWORD dwAuthnLevel,
					DWORD dwImpLevel,
					RPC_AUTH_IDENTITY_HANDLE pAuthInfo,
					DWORD dwCapabilities);

				COSETPROXYBLANKETFUNC_ CoSetProxyBlanket_ = reinterpret_cast<COSETPROXYBLANKETFUNC_>(
					GetProcAddress(ole32_module, "CoSetProxyBlanket"));

				if (CoSetProxyBlanket_ != NULL)
				{
					// Switch security level to IMPERSONATE.
					CoSetProxyBlanket_(
						wbem_services,
						RPC_C_AUTHN_WINNT,
						RPC_C_AUTHZ_NONE,
						NULL,
						RPC_C_AUTHN_LEVEL_CALL,
						RPC_C_IMP_LEVEL_IMPERSONATE,
						NULL,
						0);
				}

				FreeLibrary(ole32_module);
			}

			const BSTR wbem_class_name = SysAllocString(L"Win32_VideoController");
			IEnumWbemClassObject* wbem_video_controllers = NULL;
			hresult = wbem_services->CreateInstanceEnum(wbem_class_name, 0, NULL, &wbem_video_controllers);

			if (SUCCEEDED(hresult) && wbem_video_controllers != NULL)
			{
				const BSTR pnp_device_id_prop_name = SysAllocString(L"PNPDeviceID");
				const BSTR adapter_ram_prop_name = SysAllocString(L"AdapterRAM");

				bool found_video_controller = false;
				wbem_video_controllers->Reset();

				while (!found_video_controller)
				{
					ULONG next_count = 0;
					IWbemClassObject* wbem_display_controller = NULL;

					hresult = wbem_video_controllers->Next(
						5000,
						1,
						&wbem_display_controller,
						&next_count);

					if (SUCCEEDED(hresult) && next_count == 1)
					{
						VARIANT var;
						VariantInit(&var);

						hresult = wbem_display_controller->Get(pnp_device_id_prop_name, 0L, &var, NULL, NULL);

						if (SUCCEEDED(hresult))
						{
							if (wcsstr(var.bstrVal, display_device.DeviceID) != NULL)
							{
								found_video_controller = true;
							}
						}

						VariantClear(&var);

						if (found_video_controller)
						{
							hresult = wbem_display_controller->Get(adapter_ram_prop_name, 0L, &var, NULL, NULL);

							if (SUCCEEDED(hresult))
							{
								got_memory = true;
								wbem_size_mb = var.ulVal / (1024 * 1024);
							}

							VariantClear(&var);
						}

						wbem_display_controller->Release();
					}
					else
					{
						break;
					}
				}

				SysFreeString(pnp_device_id_prop_name);
				SysFreeString(adapter_ram_prop_name);
			}

			if (wbem_video_controllers != NULL)
			{
				wbem_video_controllers->Release();
			}

			SysFreeString(wbem_class_name);
		}

		if (wbem_services != NULL)
		{
			wbem_services->Release();
		}

		SysFreeString(wbem_object_path);
	}

	if (wbem_locator != NULL)
	{
		wbem_locator->Release();
	}

	if (SUCCEEDED(co_initialize_result))
	{
		CoUninitialize();
	}

	if (!got_memory)
	{
		return 0;
	}

	int size_mb = static_cast<int>(wbem_size_mb);

	if (size_mb <= 0)
	{
		size_mb = 1;
	}

	return size_mb;
#endif
}
#else
int Sys_GetVideoRam( void ) {
#ifdef	ID_DEDICATED
	return 0;
#else
	unsigned int retSize = 64;

	CComPtr<IWbemLocator> spLoc = NULL;
	HRESULT hr = CoCreateInstance( CLSID_WbemLocator, 0, CLSCTX_SERVER, IID_IWbemLocator, ( LPVOID * ) &spLoc );
	if ( hr != S_OK || spLoc == NULL ) {
		return retSize;
	}

	CComBSTR bstrNamespace( _T( "\\\\.\\root\\CIMV2" ) );
	CComPtr<IWbemServices> spServices;

	// Connect to CIM
	hr = spLoc->ConnectServer( bstrNamespace, NULL, NULL, 0, NULL, 0, 0, &spServices );
	if ( hr != WBEM_S_NO_ERROR ) {
		return retSize;
	}

	// Switch the security level to IMPERSONATE so that provider will grant access to system-level objects.  
	hr = CoSetProxyBlanket( spServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE );
	if ( hr != S_OK ) {
		return retSize;
	}

	// Get the vid controller
	CComPtr<IEnumWbemClassObject> spEnumInst = NULL;
	hr = spServices->CreateInstanceEnum( CComBSTR( "Win32_VideoController" ), WBEM_FLAG_SHALLOW, NULL, &spEnumInst ); 
	if ( hr != WBEM_S_NO_ERROR || spEnumInst == NULL ) {
		return retSize;
	}

	ULONG uNumOfInstances = 0;
	CComPtr<IWbemClassObject> spInstance = NULL;
	hr = spEnumInst->Next( 10000, 1, &spInstance, &uNumOfInstances );

	if ( hr == S_OK && spInstance ) {
		// Get properties from the object
		CComVariant varSize;
		hr = spInstance->Get( CComBSTR( _T( "AdapterRAM" ) ), 0, &varSize, 0, 0 );
		if ( hr == S_OK ) {
			retSize = varSize.intVal / ( 1024 * 1024 );
			if ( retSize == 0 ) {
				retSize = 64;
			}
		}
	}
	return retSize;
#endif
}
#endif

/*
================
Sys_GetCurrentMemoryStatus

	returns OS mem info
	all values are in kB except the memoryload
================
*/
void Sys_GetCurrentMemoryStatus( sysMemoryStats_t &stats ) {
	MEMORYSTATUSEX statex;
	unsigned __int64 work;

	memset( &statex, sizeof( statex ), 0 );
	statex.dwLength = sizeof( statex );
	GlobalMemoryStatusEx( &statex );

	memset( &stats, 0, sizeof( stats ) );

	stats.memoryLoad = statex.dwMemoryLoad;

	work = statex.ullTotalPhys >> 20;
	stats.totalPhysical = *(int*)&work;

	work = statex.ullAvailPhys >> 20;
	stats.availPhysical = *(int*)&work;

	work = statex.ullAvailPageFile >> 20;
	stats.availPageFile = *(int*)&work;

	work = statex.ullTotalPageFile >> 20;
	stats.totalPageFile = *(int*)&work;

	work = statex.ullTotalVirtual >> 20;
	stats.totalVirtual = *(int*)&work;

	work = statex.ullAvailVirtual >> 20;
	stats.availVirtual = *(int*)&work;

	work = statex.ullAvailExtendedVirtual >> 20;
	stats.availExtendedVirtual = *(int*)&work;
}

/*
================
Sys_LockMemory
================
*/
bool Sys_LockMemory( void *ptr, int bytes ) {
	return ( VirtualLock( ptr, (SIZE_T)bytes ) != FALSE );
}

/*
================
Sys_UnlockMemory
================
*/
bool Sys_UnlockMemory( void *ptr, int bytes ) {
	return ( VirtualUnlock( ptr, (SIZE_T)bytes ) != FALSE );
}

/*
================
Sys_SetPhysicalWorkMemory
================
*/
void Sys_SetPhysicalWorkMemory( int minBytes, int maxBytes ) {
	::SetProcessWorkingSetSize( GetCurrentProcess(), minBytes, maxBytes );
}

/*
================
Sys_GetCurrentUser
================
*/
char *Sys_GetCurrentUser( void ) {
	static char s_userName[1024];
	unsigned long size = sizeof( s_userName );


	if ( !GetUserName( s_userName, &size ) ) {
		strcpy( s_userName, "player" );
	}

	if ( !s_userName[0] ) {
		strcpy( s_userName, "player" );
	}

	return s_userName;
}	


/*
===============================================================================

	Call stack

===============================================================================
*/


#define PROLOGUE_SIGNATURE 0x00EC8B55

#include <dbghelp.h>

const int UNDECORATE_FLAGS =	UNDNAME_NO_MS_KEYWORDS |
								UNDNAME_NO_ACCESS_SPECIFIERS |
								UNDNAME_NO_FUNCTION_RETURNS |
								UNDNAME_NO_ALLOCATION_MODEL |
								UNDNAME_NO_ALLOCATION_LANGUAGE |
								UNDNAME_NO_MEMBER_TYPE;

#if defined(_DEBUG) && 1

typedef struct symbol_s {
	int					address;
	char *				name;
	struct symbol_s *	next;
} symbol_t;

typedef struct module_s {
	int					address;
	char *				name;
	symbol_t *			symbols;
	struct module_s *	next;
} module_t;

module_t *modules;

/*
==================
SkipRestOfLine
==================
*/
void SkipRestOfLine( const char **ptr ) {
	while( (**ptr) != '\0' && (**ptr) != '\n' && (**ptr) != '\r' ) {
		(*ptr)++;
	}
	while( (**ptr) == '\n' || (**ptr) == '\r' ) {
		(*ptr)++;
	}
}

/*
==================
SkipWhiteSpace
==================
*/
void SkipWhiteSpace( const char **ptr ) {
	while( (**ptr) == ' ' ) {
		(*ptr)++;
	}
}

/*
==================
ParseHexNumber
==================
*/
int ParseHexNumber( const char **ptr ) {
	int n = 0;
	while( (**ptr) >= '0' && (**ptr) <= '9' || (**ptr) >= 'a' && (**ptr) <= 'f' ) {
		n <<= 4;
		if ( **ptr >= '0' && **ptr <= '9' ) {
			n |= ( (**ptr) - '0' );
		} else {
			n |= 10 + ( (**ptr) - 'a' );
		}
		(*ptr)++;
	}
	return n;
}

/*
==================
Sym_Init
==================
*/
void Sym_Init( long addr ) {
	TCHAR moduleName[MAX_STRING_CHARS];
	MEMORY_BASIC_INFORMATION mbi;

	VirtualQuery( (void*)addr, &mbi, sizeof(mbi) );

	GetModuleFileName( (HMODULE)mbi.AllocationBase, moduleName, sizeof( moduleName ) );

	char *ext = moduleName + strlen( moduleName );
	while( ext > moduleName && *ext != '.' ) {
		ext--;
	}
	if ( ext == moduleName ) {
		strcat( moduleName, ".map" );
	} else {
		strcpy( ext, ".map" );
	}

	module_t *module = (module_t *) malloc( sizeof( module_t ) );
	module->name = (char *) malloc( strlen( moduleName ) + 1 );
	strcpy( module->name, moduleName );
	module->address = (int)mbi.AllocationBase;
	module->symbols = NULL;
	module->next = modules;
	modules = module;

	FILE *fp = fopen( moduleName, "rb" );
	if ( fp == NULL ) {
		return;
	}

	int pos = ftell( fp );
	fseek( fp, 0, SEEK_END );
	int length = ftell( fp );
	fseek( fp, pos, SEEK_SET );

	char *text = (char *) malloc( length+1 );
	fread( text, 1, length, fp );
	text[length] = '\0';
	fclose( fp );

	const char *ptr = text;

	// skip up to " Address" on a new line
	while( *ptr != '\0' ) {
		SkipWhiteSpace( &ptr );
		if ( idStr::Cmpn( ptr, "Address", 7 ) == 0 ) {
			SkipRestOfLine( &ptr );
			break;
		}
		SkipRestOfLine( &ptr );
	}

	int symbolAddress;
	int symbolLength;
	char symbolName[MAX_STRING_CHARS];
	symbol_t *symbol;

	// parse symbols
	while( *ptr != '\0' ) {

		SkipWhiteSpace( &ptr );

		ParseHexNumber( &ptr );
		if ( *ptr == ':' ) {
			ptr++;
		} else {
			break;
		}
		ParseHexNumber( &ptr );

		SkipWhiteSpace( &ptr );

		// parse symbol name
		symbolLength = 0;
		while( *ptr != '\0' && *ptr != ' ' ) {
			symbolName[symbolLength++] = *ptr++;
			if ( symbolLength >= sizeof( symbolName ) - 1 ) {
				break;
			}
		}
		symbolName[symbolLength++] = '\0';

		SkipWhiteSpace( &ptr );

		// parse symbol address
		symbolAddress = ParseHexNumber( &ptr );

		SkipRestOfLine( &ptr );

		symbol = (symbol_t *) malloc( sizeof( symbol_t ) );
		symbol->name = (char *) malloc( symbolLength );
		strcpy( symbol->name, symbolName );
		symbol->address = symbolAddress;
		symbol->next = module->symbols;
		module->symbols = symbol;
	}

	free( text );
}

/*
==================
Sym_Shutdown
==================
*/
void Sym_Shutdown( void ) {
	module_t *m;
	symbol_t *s;

	for ( m = modules; m != NULL; m = modules ) {
		modules = m->next;
		for ( s = m->symbols; s != NULL; s = m->symbols ) {
			m->symbols = s->next;
			free( s->name );
			free( s );
		}
		free( m->name );
		free( m );
	}
	modules = NULL;
}

/*
==================
Sym_GetFuncInfo
==================
*/
void Sym_GetFuncInfo( long addr, idStr &module, idStr &funcName ) {
	MEMORY_BASIC_INFORMATION mbi;
	module_t *m;
	symbol_t *s;

	VirtualQuery( (void*)addr, &mbi, sizeof(mbi) );

	for ( m = modules; m != NULL; m = m->next ) {
		if ( m->address == (int) mbi.AllocationBase ) {
			break;
		}
	}
	if ( !m ) {
		Sym_Init( addr );
		m = modules;
	}

	for ( s = m->symbols; s != NULL; s = s->next ) {
		if ( s->address == addr ) {

			char undName[MAX_STRING_CHARS];
			if ( UnDecorateSymbolName( s->name, undName, sizeof(undName), UNDECORATE_FLAGS ) ) {
				funcName = undName;
			} else {
				funcName = s->name;
			}
			for ( int i = 0; i < funcName.Length(); i++ ) {
				if ( funcName[i] == '(' ) {
					funcName.CapLength( i );
					break;
				}
			}
			module = m->name;
			return;
		}
	}

	sprintf( funcName, "0x%08x", addr );
	module = "";
}

#elif defined(_DEBUG)

DWORD lastAllocationBase = -1;
HANDLE processHandle;
idStr lastModule;

/*
==================
Sym_Init
==================
*/
void Sym_Init( long addr ) {
	TCHAR moduleName[MAX_STRING_CHARS];
	TCHAR modShortNameBuf[MAX_STRING_CHARS];
	MEMORY_BASIC_INFORMATION mbi;

	if ( lastAllocationBase != -1 ) {
		Sym_Shutdown();
	}

	VirtualQuery( (void*)addr, &mbi, sizeof(mbi) );

	GetModuleFileName( (HMODULE)mbi.AllocationBase, moduleName, sizeof( moduleName ) );
	_splitpath( moduleName, NULL, NULL, modShortNameBuf, NULL );
	lastModule = modShortNameBuf;

	processHandle = GetCurrentProcess();
	if ( !SymInitialize( processHandle, NULL, FALSE ) ) {
		return;
	}
	if ( !SymLoadModule( processHandle, NULL, moduleName, NULL, (DWORD)mbi.AllocationBase, 0 ) ) {
		SymCleanup( processHandle );
		return;
	}

	SymSetOptions( SymGetOptions() & ~SYMOPT_UNDNAME );

	lastAllocationBase = (DWORD) mbi.AllocationBase;
}

/*
==================
Sym_Shutdown
==================
*/
void Sym_Shutdown( void ) {
	SymUnloadModule( GetCurrentProcess(), lastAllocationBase );
	SymCleanup( GetCurrentProcess() );
	lastAllocationBase = -1;
}

/*
==================
Sym_GetFuncInfo
==================
*/
void Sym_GetFuncInfo( long addr, idStr &module, idStr &funcName ) {
	MEMORY_BASIC_INFORMATION mbi;

	VirtualQuery( (void*)addr, &mbi, sizeof(mbi) );

	if ( (DWORD) mbi.AllocationBase != lastAllocationBase ) {
		Sym_Init( addr );
	}

	BYTE symbolBuffer[ sizeof(IMAGEHLP_SYMBOL) + MAX_STRING_CHARS ];
	PIMAGEHLP_SYMBOL pSymbol = (PIMAGEHLP_SYMBOL)&symbolBuffer[0];
	pSymbol->SizeOfStruct = sizeof(symbolBuffer);
	pSymbol->MaxNameLength = 1023;
	pSymbol->Address = 0;
	pSymbol->Flags = 0;
	pSymbol->Size =0;

	DWORD symDisplacement = 0;
	if ( SymGetSymFromAddr( processHandle, addr, &symDisplacement, pSymbol ) ) {
		// clean up name, throwing away decorations that don't affect uniqueness
	    char undName[MAX_STRING_CHARS];
		if ( UnDecorateSymbolName( pSymbol->Name, undName, sizeof(undName), UNDECORATE_FLAGS ) ) {
			funcName = undName;
		} else {
			funcName = pSymbol->Name;
		}
		module = lastModule;
	}
	else {
		LPVOID lpMsgBuf;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
						(LPTSTR) &lpMsgBuf,
						0,
						NULL 
						);
		LocalFree( lpMsgBuf );

		// Couldn't retrieve symbol (no debug info?, can't load dbghelp.dll?)
		sprintf( funcName, "0x%08x", addr );
		module = "";
    }
}

#else

/*
==================
Sym_Init
==================
*/
void Sym_Init( long addr ) {
}

/*
==================
Sym_Shutdown
==================
*/
void Sym_Shutdown( void ) {
}

/*
==================
Sym_GetFuncInfo
==================
*/
void Sym_GetFuncInfo( long addr, idStr &module, idStr &funcName ) {
	module = "";
	sprintf( funcName, "0x%08x", addr );
}

#endif

/*
==================
GetFuncAddr
==================
*/
address_t GetFuncAddr( address_t midPtPtr ) {
	long temp;
	do {
		temp = (long)(*(long*)midPtPtr);
		if ( (temp&0x00FFFFFF) == PROLOGUE_SIGNATURE ) {
			break;
		}
		midPtPtr--;
	} while(true);

	return midPtPtr;
}

/*
==================
GetCallerAddr
==================
*/
address_t GetCallerAddr( long _ebp ) {
	long midPtPtr;
	long res = 0;

	__asm {
		mov		eax, _ebp
		mov		ecx, [eax]		// check for end of stack frames list
		test	ecx, ecx		// check for zero stack frame
		jz		label
		mov		eax, [eax+4]	// get the ret address
		test	eax, eax		// check for zero return address
		jz		label
		mov		midPtPtr, eax
	}
	res = GetFuncAddr( midPtPtr );
label:
	return res;
}

/*
==================
Sys_GetCallStack

 use /Oy option
==================
*/
void Sys_GetCallStack( address_t *callStack, const int callStackSize ) {
#if 1 //def _DEBUG
	int i;
	long m_ebp;

	__asm {
		mov eax, ebp
		mov m_ebp, eax
	}
	// skip last two functions
	m_ebp = *((long*)m_ebp);
	m_ebp = *((long*)m_ebp);
	// list functions
	for ( i = 0; i < callStackSize; i++ ) {
		callStack[i] = GetCallerAddr( m_ebp );
		if ( callStack[i] == 0 ) {
			break;
		}
		m_ebp = *((long*)m_ebp);
	}
#else
	int i = 0;
#endif
	while( i < callStackSize ) {
		callStack[i++] = 0;
	}
}

/*
==================
Sys_GetCallStackStr
==================
*/
const char *Sys_GetCallStackStr( const address_t *callStack, const int callStackSize ) {
	static char string[MAX_STRING_CHARS*2];
	int index, i;
	idStr module, funcName;

	index = 0;
	for ( i = callStackSize-1; i >= 0; i-- ) {
		Sym_GetFuncInfo( callStack[i], module, funcName );
		index += sprintf( string+index, " -> %s", funcName.c_str() );
	}
	return string;
}

/*
==================
Sys_GetCallStackCurStr
==================
*/
const char *Sys_GetCallStackCurStr( int depth ) {
	address_t *callStack;

	callStack = (address_t *) _alloca( depth * sizeof( address_t ) );
	Sys_GetCallStack( callStack, depth );
	return Sys_GetCallStackStr( callStack, depth );
}

/*
==================
Sys_GetCallStackCurAddressStr
==================
*/
const char *Sys_GetCallStackCurAddressStr( int depth ) {
	static char string[MAX_STRING_CHARS*2];
	address_t *callStack;
	int index, i;

	callStack = (address_t *) _alloca( depth * sizeof( address_t ) );
	Sys_GetCallStack( callStack, depth );

	index = 0;
	for ( i = depth-1; i >= 0; i-- ) {
		index += sprintf( string+index, " -> 0x%08x", callStack[i] );
	}
	return string;
}

/*
==================
Sys_ShutdownSymbols
==================
*/
void Sys_ShutdownSymbols( void ) {
	Sym_Shutdown();
}
