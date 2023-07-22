#[[
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company. 
Copyright (c) 2022 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only AND MIT
]]

cmake_policy(SET CMP0091 NEW) # MSVC runtime library flags are selected by an abstraction.
cmake_policy(SET CMP0092 NEW) # MSVC warning flags are not in CMAKE_<LANG>_FLAGS by default.

if (CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Build configurations." FORCE)
endif ()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

enable_language(CXX)
enable_language(C)

# ===========================================================================

message(STATUS "[idt4] C compiler ID: ${CMAKE_C_COMPILER_ID}")
message(STATUS "[idt4] C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")

if (NOT MSVC OR MSVC_VERSION LESS 1300)
	message(FATAL_ERROR "Expected Visual C++ 7 (2002) or higher compiler.")
endif ()

# ===========================================================================

if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)
	add_compile_definitions(_CRT_NONSTDC_NO_DEPRECATE)
	add_compile_definitions(_USE_32BIT_TIME_T)
	add_compile_definitions(WINVER=0x0501)
	add_compile_definitions(NTDDI_VERSION=0x05010000)
	add_compile_definitions(_WIN32_WINNT=0x0501)
	add_compile_definitions(_ALLOW_KEYWORD_MACROS)
endif ()

if (WIN32)
	add_compile_options(/W3)
endif ()

# ===========================================================================

option(IDT4_PRECOMPILE_HEADERS "Precompile headers." ON)

set(pch "${IDT4_PRECOMPILE_HEADERS}")
unset(pch_message)

if (IDT4_PRECOMPILE_HEADERS)
	if (MSVC)
		if (MSVC_VERSION EQUAL 1300)
			# Visual C++ 7.0 (2002)
			set(pch OFF)
			set(pch_message " (c1xx : fatal error C1060: compiler is out of heap space)")
		elseif (MSVC_VERSION EQUAL 1500)
			# Visual C++ 9.0 (2008)
			set(pch OFF)
			set(pch_message " (cl : Command line error D8036 : '...cmake_pch...' not allowed with multiple source files)")
		endif ()
	endif ()
endif ()

message(STATUS "[idt4] Precompile headers: ${pch}${pch_message}")

# ===========================================================================

option(IDT4_MULTI_PROCESS_COMPILATION "Use multi-process compilation." ON)

set(msvc_mp OFF)

if (MSVC AND IDT4_MULTI_PROCESS_COMPILATION)
	include(ProcessorCount)
	ProcessorCount(core_count)
	message(STATUS "[idt4] Core count: ${core_count}")
	
	if (${core_count} GREATER 1)
		set(msvc_mp ON)
		add_compile_options("/MP${core_count}")
	else ()
		message(STATUS "[idt4][W] Not enough cores for multi-process compilation.")
	endif ()
endif ()

message(STATUS "[idt4] Use multi-process compilation: ${msvc_mp}")

# ===========================================================================

option(IDT4_VANILLA "Build original code." OFF)
message(STATUS "[idt4] Build original code: ${IDT4_VANILLA}")

if (IDT4_VANILLA)
	add_compile_definitions(IDT4_VANILLA)
endif ()

# ===========================================================================

option(IDT4_VANILLA_FIX_COMPILATION_ERRORS "Fix original compilation errors." ON)
message(STATUS "[idt4] Fix original compilation errors: ${IDT4_VANILLA_FIX_COMPILATION_ERRORS}")

if (IDT4_VANILLA_FIX_COMPILATION_ERRORS)
	add_compile_definitions(IDT4_VANILLA_FIX_COMPILATION_ERRORS)
endif ()

# ===========================================================================

option(IDT4_MFC "Use MFC." ON)

set(win32_mfc OFF)

if (IDT4_MFC)
	if (WIN32)
		try_compile(
			win32_mfc
			"${CMAKE_BINARY_DIR}/try_compile/mfc"
			"${CMAKE_SOURCE_DIR}/cmake/try_compile/mfc"
			idt4_try_compile_mfc
			OUTPUT_VARIABLE win32_mfc_output
		)

		if (NOT win32_mfc)
			message(STATUS "[idt4][W] MFC not found.")

			if (NOT "${win32_mfc_output}" STREQUAL "")
				message(STATUS "[idt4][W] <<<<<<<< TRACE BEGIN <<<<<<<<")
				message(STATUS "[idt4][W] ${win32_mfc_output}")
				message(STATUS "[idt4][W] >>>>>>>>> TRACE END >>>>>>>>>")
			endif ()
		endif ()
	else ()
		message(STATUS "[idt4][W] MFC not supported.")
	endif ()
endif ()

message(STATUS "[idt4] Use MFC: ${win32_mfc}")

# ===========================================================================

set(IDT4_DIRECTX_DIR "" CACHE PATH "Path to DirectX SDK.")

if (NOT EXISTS "${IDT4_DIRECTX_DIR}" OR
	NOT EXISTS "${IDT4_DIRECTX_DIR}/include/dxerr.h" OR
	NOT EXISTS "${IDT4_DIRECTX_DIR}/lib/x86/dxerr.lib")
	message(FATAL_ERROR "DirectX SDK not found.")
endif ()

message(STATUS "[idt4] DirectX SDK: ${IDT4_DIRECTX_DIR}")

# ===========================================================================

cmake_minimum_required(VERSION 3.16.9 FATAL_ERROR)
project(idt4_solution VERSION 1.0.0 LANGUAGES NONE)

message(STATUS "[${PROJECT_NAME}] Version: ${PROJECT_VERSION}")

add_subdirectory(neo/curl)
add_subdirectory(neo/idlib)
if (win32_mfc)
	add_subdirectory(neo/idlib_mfc)
endif ()
add_subdirectory(neo/TypeInfo)
add_subdirectory(neo/game)
add_subdirectory(neo/d3xp)
add_subdirectory(neo/d3)
add_subdirectory(neo/d3ded)

install(FILES
	README.md
		DESTINATION "."
		RENAME idt4_readme.md
)
