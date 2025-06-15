/*
IDT4: Unofficial source port for idTech4 based games
Copyright (c) Microsoft Corporation. All rights reserved.
Copyright (c) 2025 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: MIT
*/

/*
DirectSound API
Based on dsound.h from Windows SDK v10.0.26100.
*/

#define DIRECTSOUND_VERSION 0x0800

#include <stddef.h>
#include <string.h>
#include "dsound.h"

// ==========================================================================

namespace {

typedef HRESULT (WINAPI * IMPL_DirectSoundCreate)(LPCGUID pcGuidDevice, LPDIRECTSOUND* ppDS, LPUNKNOWN pUnkOuter);
typedef HRESULT (WINAPI * IMPL_DirectSoundEnumerateA)(LPDSENUMCALLBACKA pDSEnumCallback, LPVOID pContext);
typedef HRESULT (WINAPI * IMPL_DirectSoundEnumerateW)(LPDSENUMCALLBACKW pDSEnumCallback, LPVOID pContext);
typedef HRESULT (WINAPI * IMPL_DirectSoundCaptureCreate)(
	LPCGUID pcGuidDevice,
	LPDIRECTSOUNDCAPTURE* ppDSC,
	LPUNKNOWN pUnkOuter);
typedef HRESULT (WINAPI * IMPL_DirectSoundCaptureEnumerateA)(LPDSENUMCALLBACKA pDSEnumCallback, LPVOID pContext);
typedef HRESULT (WINAPI * IMPL_DirectSoundCaptureEnumerateW)(LPDSENUMCALLBACKW pDSEnumCallback, LPVOID pContext);
typedef HRESULT (WINAPI * IMPL_DirectSoundCreate8)(LPCGUID pcGuidDevice, LPDIRECTSOUND8* ppDS8, LPUNKNOWN pUnkOuter);
typedef HRESULT (WINAPI * IMPL_DirectSoundCaptureCreate8)(
	LPCGUID pcGuidDevice,
	LPDIRECTSOUNDCAPTURE8* ppDSC8,
	LPUNKNOWN pUnkOuter);
typedef HRESULT (WINAPI * IMPL_DirectSoundFullDuplexCreate)(
	LPCGUID pcGuidCaptureDevice,
	LPCGUID pcGuidRenderDevice,
	LPCDSCBUFFERDESC pcDSCBufferDesc,
	LPCDSBUFFERDESC pcDSBufferDesc,
	HWND hWnd,
	DWORD dwLevel,
	LPDIRECTSOUNDFULLDUPLEX* ppDSFD,
	LPDIRECTSOUNDCAPTUREBUFFER8* ppDSCBuffer8,
	LPDIRECTSOUNDBUFFER8* ppDSBuffer8,
	LPUNKNOWN pUnkOuter);
typedef HRESULT (WINAPI * IMPL_GetDeviceID)(LPCGUID pGuidSrc, LPGUID pGuidDest);

bool impl_is_initialized = false;
HMODULE impl_module = NULL;
IMPL_DirectSoundCreate impl_DirectSoundCreate = NULL;
IMPL_DirectSoundEnumerateA impl_DirectSoundEnumerateA = NULL;
IMPL_DirectSoundEnumerateW impl_DirectSoundEnumerateW = NULL;
IMPL_DirectSoundCaptureCreate impl_DirectSoundCaptureCreate = NULL;
IMPL_DirectSoundCaptureEnumerateA impl_DirectSoundCaptureEnumerateA = NULL;
IMPL_DirectSoundCaptureEnumerateW impl_DirectSoundCaptureEnumerateW = NULL;
IMPL_DirectSoundCreate8 impl_DirectSoundCreate8 = NULL;
IMPL_DirectSoundCaptureCreate8 impl_DirectSoundCaptureCreate8 = NULL;
IMPL_DirectSoundFullDuplexCreate impl_DirectSoundFullDuplexCreate = NULL;
IMPL_GetDeviceID impl_GetDeviceID;

template<typename TDst>
void impl_cast_proc(const FARPROC& src, TDst& dst)
{
	const size_t size = sizeof(FARPROC);
	typedef unsigned char Sanity[2 * (size == sizeof(TDst)) - 1];
	memcpy(&dst, &src, size);
}

void impl_initialize()
{
	if (impl_is_initialized)
	{
		return;
	}

	impl_is_initialized = true;
	impl_module = LoadLibraryW(L"dsound.dll");

	if (impl_module != NULL)
	{
#define IMPL_GET_PROC(symbol) \
	impl_cast_proc(GetProcAddress(impl_module, #symbol), impl_##symbol)

		IMPL_GET_PROC(DirectSoundCreate);
		IMPL_GET_PROC(DirectSoundEnumerateA);
		IMPL_GET_PROC(DirectSoundEnumerateW);
		IMPL_GET_PROC(DirectSoundCaptureCreate);
		IMPL_GET_PROC(DirectSoundCaptureEnumerateA);
		IMPL_GET_PROC(DirectSoundCaptureEnumerateW);
		IMPL_GET_PROC(DirectSoundCreate8);
		IMPL_GET_PROC(DirectSoundCaptureCreate8);
		IMPL_GET_PROC(DirectSoundFullDuplexCreate);
		IMPL_GET_PROC(GetDeviceID);

#undef IMPL_GET_PROC
	}
}

} // namespace

extern "C" {

HRESULT WINAPI DirectSoundCreate(LPCGUID pcGuidDevice, LPDIRECTSOUND* ppDS, LPUNKNOWN pUnkOuter)
{
	impl_initialize();

	if (impl_DirectSoundCreate == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundCreate(pcGuidDevice, ppDS, pUnkOuter);
}

HRESULT WINAPI DirectSoundEnumerateA(LPDSENUMCALLBACKA pDSEnumCallback, LPVOID pContext)
{
	impl_initialize();

	if (impl_DirectSoundEnumerateA == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundEnumerateA(pDSEnumCallback, pContext);
}

HRESULT WINAPI DirectSoundEnumerateW(LPDSENUMCALLBACKW pDSEnumCallback, LPVOID pContext)
{
	impl_initialize();

	if (impl_DirectSoundEnumerateW == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundEnumerateW(pDSEnumCallback, pContext);
}

HRESULT WINAPI DirectSoundCaptureCreate(LPCGUID pcGuidDevice, LPDIRECTSOUNDCAPTURE* ppDSC, LPUNKNOWN pUnkOuter)
{
	impl_initialize();

	if (impl_DirectSoundCaptureCreate == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundCaptureCreate(pcGuidDevice, ppDSC, pUnkOuter);
}

HRESULT WINAPI DirectSoundCaptureEnumerateA(LPDSENUMCALLBACKA pDSEnumCallback, LPVOID pContext)
{
	impl_initialize();

	if (impl_DirectSoundCaptureEnumerateA == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundCaptureEnumerateA(pDSEnumCallback, pContext);
}

HRESULT WINAPI DirectSoundCaptureEnumerateW(LPDSENUMCALLBACKW pDSEnumCallback, LPVOID pContext)
{
	impl_initialize();

	if (impl_DirectSoundCaptureEnumerateW == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundCaptureEnumerateW(pDSEnumCallback, pContext);
}

HRESULT WINAPI DirectSoundCreate8(LPCGUID pcGuidDevice, LPDIRECTSOUND8* ppDS8, LPUNKNOWN pUnkOuter)
{
	impl_initialize();

	if (impl_DirectSoundCreate8 == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundCreate8(pcGuidDevice, ppDS8, pUnkOuter);
}

HRESULT WINAPI DirectSoundCaptureCreate8(LPCGUID pcGuidDevice, LPDIRECTSOUNDCAPTURE8* ppDSC8, LPUNKNOWN pUnkOuter)
{
	impl_initialize();

	if (impl_DirectSoundCaptureCreate8 == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundCaptureCreate8(pcGuidDevice, ppDSC8, pUnkOuter);
}

HRESULT WINAPI DirectSoundFullDuplexCreate(
	LPCGUID pcGuidCaptureDevice,
	LPCGUID pcGuidRenderDevice,
	LPCDSCBUFFERDESC pcDSCBufferDesc,
	LPCDSBUFFERDESC pcDSBufferDesc,
	HWND hWnd,
	DWORD dwLevel,
	LPDIRECTSOUNDFULLDUPLEX* ppDSFD,
	LPDIRECTSOUNDCAPTUREBUFFER8* ppDSCBuffer8,
	LPDIRECTSOUNDBUFFER8* ppDSBuffer8,
	LPUNKNOWN pUnkOuter)
{
	impl_initialize();

	if (impl_DirectSoundFullDuplexCreate == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_DirectSoundFullDuplexCreate(
		pcGuidCaptureDevice,
		pcGuidRenderDevice,
		pcDSCBufferDesc,
		pcDSBufferDesc,
		hWnd,
		dwLevel,
		ppDSFD,
		ppDSCBuffer8,
		ppDSBuffer8,
		pUnkOuter);
}

HRESULT WINAPI GetDeviceID(LPCGUID pGuidSrc, LPGUID pGuidDest)
{
	impl_initialize();

	if (impl_GetDeviceID == NULL)
	{
		return DSERR_GENERIC;
	}

	return impl_GetDeviceID(pGuidSrc, pGuidDest);
}

} // extern "C"
