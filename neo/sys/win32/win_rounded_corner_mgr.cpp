/*
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company.
Copyright (c) 2022-2025 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only or MIT
*/

#include "win_rounded_corner_mgr.h"
#include <stddef.h>
#include <string.h>

// ==========================================================================

namespace {

template<typename TDst, typename TSrc>
void bit_cast(const TSrc& src, TDst& dst)
{
	const size_t size = sizeof(TSrc);
	typedef unsigned char Sanity[2 * (size == sizeof(TDst)) - 1];
	memcpy(&dst, &src, size);
}

// ==========================================================================

template<typename T>
class UniquePtr
{
public:
	UniquePtr();
	~UniquePtr();

	T* get() const;
	void reset(T* pointer);

	T* operator->() const;

private:
	T* pointer_;

private:
	UniquePtr(const UniquePtr&);
	UniquePtr& operator=(const UniquePtr&);
};

// --------------------------------------------------------------------------

template<typename T>
UniquePtr<T>::UniquePtr()
	:
	pointer_()
{}

template<typename T>
UniquePtr<T>::~UniquePtr()
{
	delete pointer_;
}

template<typename T>
T* UniquePtr<T>::get() const
{
	return pointer_;
}

template<typename T>
void UniquePtr<T>::reset(T* pointer)
{
	delete pointer_;
	pointer_ = pointer;
}

template<typename T>
T* UniquePtr<T>::operator->() const
{
	return get();
}

// ==========================================================================

class WinRoundedCornerMgrImpl
{
public:
	WinRoundedCornerMgrImpl();
	~WinRoundedCornerMgrImpl();

	static void disable(HWND win32_handle);

private:
	static const DWORD WIN32_DWMWCP_DONOTROUND = 1;
	static const DWORD WIN32_DWMWA_WINDOW_CORNER_PREFERENCE = 33;

private:
	typedef UniquePtr<WinRoundedCornerMgrImpl> Instance;

	typedef HRESULT (WINAPI * PFNDWMSETWINDOWATTRIBUTEPROC)(
		HWND hwnd,
		DWORD dwAttribute,
		LPCVOID pvAttribute,
		DWORD cbAttribute);

private:
	static Instance instance_;

	HMODULE dwmapi_module_;
	PFNDWMSETWINDOWATTRIBUTEPROC dwm_set_window_attribute_;

private:
	WinRoundedCornerMgrImpl(const WinRoundedCornerMgrImpl&);
	WinRoundedCornerMgrImpl& operator=(const WinRoundedCornerMgrImpl&);

	bool initialize();
	void terminate();
	void impl_disable(HWND win32_handle) const;
};

// --------------------------------------------------------------------------

WinRoundedCornerMgrImpl::Instance WinRoundedCornerMgrImpl::instance_;

// --------------------------------------------------------------------------

WinRoundedCornerMgrImpl::WinRoundedCornerMgrImpl()
{
	if (!initialize())
	{
		terminate();
	}
}

WinRoundedCornerMgrImpl::~WinRoundedCornerMgrImpl()
{
	terminate();
}

void WinRoundedCornerMgrImpl::disable(HWND win32_handle)
{
	if (instance_.get() == NULL)
	{
		instance_.reset(new WinRoundedCornerMgrImpl());
	}

	instance_->impl_disable(win32_handle);
}

bool WinRoundedCornerMgrImpl::initialize()
{
	dwmapi_module_ = LoadLibraryW(L"dwmapi.dll");

	if (dwmapi_module_ == NULL)
	{
		return false;
	}

	bit_cast(GetProcAddress(dwmapi_module_, "DwmSetWindowAttribute"), dwm_set_window_attribute_);

	if (dwm_set_window_attribute_ == NULL)
	{
		return false;
	}

	return true;
}

void WinRoundedCornerMgrImpl::terminate()
{
	dwm_set_window_attribute_ = NULL;

	if (dwmapi_module_ != NULL)
	{
		FreeLibrary(dwmapi_module_);
		dwmapi_module_ = NULL;
	}
}

void WinRoundedCornerMgrImpl::impl_disable(HWND win32_handle) const
{
	if (dwm_set_window_attribute_ == NULL)
	{
		return;
	}

	const DWORD win32_rounded_corner_type = WIN32_DWMWCP_DONOTROUND;

	dwm_set_window_attribute_(
		win32_handle,
		WIN32_DWMWA_WINDOW_CORNER_PREFERENCE,
		&win32_rounded_corner_type,
		static_cast<DWORD>(sizeof(win32_rounded_corner_type)));
}

} // namespace

// ==========================================================================

void WinRoundedCornerMgr::disable(HWND win32_handle)
{
	WinRoundedCornerMgrImpl::disable(win32_handle);
}
