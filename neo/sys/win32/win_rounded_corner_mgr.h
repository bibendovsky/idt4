/*
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company.
Copyright (c) 2022-2025 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only or MIT
*/

#ifndef IDT4_WIN_ROUNDED_CORNER_MGR_INCLUDED
#define IDT4_WIN_ROUNDED_CORNER_MGR_INCLUDED

#include <windows.h>

class WinRoundedCornerMgr
{
public:
	static void disable(HWND win32_handle);
};

#endif // IDT4_WIN_ROUNDED_CORNER_MGR_INCLUDED
