#[[
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company. 
Copyright (c) 2022 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only AND MIT
]]

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

cmake_minimum_required(VERSION 3.16.9 FATAL_ERROR)
project(idt4_try_compile_mfc VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "[${PROJECT_NAME}] Version: ${PROJECT_VERSION}")

set(CMAKE_MFC_FLAG 1)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		CXX_STANDARD 98
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
		WIN32_EXECUTABLE TRUE
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		IDT4_MFC
)

target_sources(${PROJECT_NAME}
	PRIVATE
		src/mfc.cpp
)
