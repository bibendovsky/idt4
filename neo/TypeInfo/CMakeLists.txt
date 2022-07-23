#[[
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company. 
Copyright (c) 2022 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only AND MIT
]]

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(idt4_type_info VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "[${PROJECT_NAME}] Version: ${PROJECT_VERSION}")

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		OUTPUT_NAME "typeinfo"
		CXX_VISIBILITY_PRESET "hidden"
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		ID_ENABLE_CURL=0
		ID_TYPEINFO
		__DOOM_DLL__
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		"${IDT4_DIRECTX_DIR}/include"
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		idt4_id_lib
)

if (pch)
	target_precompile_headers(${PROJECT_NAME}
		PRIVATE
			../idlib/precompiled.h
	)
endif ()

target_sources(${PROJECT_NAME}
	PRIVATE
		../framework/CVarSystem.cpp
		../framework/CVarSystem.h
		../framework/CmdSystem.cpp
		../framework/CmdSystem.h
		../framework/File.cpp
		../framework/File.h
		../framework/FileSystem.cpp
		../framework/FileSystem.h
		../framework/Licensee.h
		../framework/Unzip.cpp
		../framework/Unzip.h
		TypeInfoGen.cpp
		TypeInfoGen.h
		main.cpp
)
