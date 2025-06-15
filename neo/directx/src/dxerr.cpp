/*
IDT4: Unofficial source port for idTech4 based games
Copyright (c) Microsoft Corporation. All rights reserved.
Copyright (c) 2025 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: MIT
*/

/*
DirectX Error API
Based on DxErr.h from DirectX 9 SDK Jun 2010.
*/

#include <windows.h>
#include "dxerr.h"

// ==========================================================================

namespace {

template<typename T>
void maybe_unused(const T&)
{}

} // namespace

// ==========================================================================

const char* WINAPI DXGetErrorStringA(HRESULT hr)
{
	switch (hr)
	{
		case 0: return "E_SUCCESS";
		default: return "E_FAILURE";
	}
}

// ==========================================================================

const WCHAR* WINAPI DXGetErrorStringW(HRESULT hr)
{
	switch (hr)
	{
		case 0: return L"E_SUCCESS";
		default: return L"E_FAILURE";
	}
}

// ==========================================================================

const char* WINAPI DXGetErrorDescriptionA(HRESULT hr)
{
	switch (hr)
	{
		case 0: return "Succeeded.";
		default: return "Failed.";
	}
}

// ==========================================================================

const WCHAR* WINAPI DXGetErrorDescriptionW(HRESULT hr)
{
	switch (hr)
	{
		case 0: return L"Succeeded.";
		default: return L"Failed.";
	}
}

// ==========================================================================

HRESULT WINAPI DXTraceA(const char* strFile, DWORD dwLine, HRESULT hr, const char* strMsg, BOOL bPopMsgBox)
{
	maybe_unused(strFile);
	maybe_unused(dwLine);
	maybe_unused(strMsg);
	maybe_unused(bPopMsgBox);
	return hr;
}

// ==========================================================================

HRESULT WINAPI DXTraceW(const char* strFile, DWORD dwLine, HRESULT hr, const WCHAR* strMsg, BOOL bPopMsgBox)
{
	maybe_unused(strFile);
	maybe_unused(dwLine);
	maybe_unused(strMsg);
	maybe_unused(bPopMsgBox);
	return hr;
}
