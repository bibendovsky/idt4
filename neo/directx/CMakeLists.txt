#[[
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 2025 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: MIT
]]

cmake_minimum_required(VERSION 3.16.9 FATAL_ERROR)
project(idt4_directx VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "[idt4_directx] Version: ${PROJECT_VERSION}")

add_library(idt4_directx STATIC)
add_library(idt4::directx ALIAS idt4_directx)

set_target_properties(idt4_directx
	PROPERTIES
		CXX_STANDARD 98
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)

target_include_directories(idt4_directx PUBLIC include)

target_sources(idt4_directx
	PRIVATE
		include/dinput.h
		src/dinput.cpp
		include/dsound.h
		src/dsound.cpp
		include/dxerr.h
		src/dxerr.cpp
		src/dxguid.cpp
)
