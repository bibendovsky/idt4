#[[
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company. 
Copyright (c) 2022 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only AND MIT
]]

cmake_minimum_required(VERSION 3.16.9 FATAL_ERROR)
project(idt4_id_lib VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "[${PROJECT_NAME}] Version: ${PROJECT_VERSION}")

add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		CXX_STANDARD 98
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		__IDLIB__
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		"${IDT4_DIRECTX_DIR}/include"
		.
)

if (pch)
	target_precompile_headers(${PROJECT_NAME}
		PRIVATE
			precompiled.h
	)
endif ()

target_sources(${PROJECT_NAME}
	PRIVATE
		Base64.cpp
		Base64.h
		BitMsg.cpp
		BitMsg.h
		CmdArgs.cpp
		CmdArgs.h
		Dict.cpp
		Dict.h
		Heap.cpp
		Heap.h
		LangDict.cpp
		LangDict.h
		Lexer.cpp
		Lexer.h
		Lib.cpp
		Lib.h
		MapFile.cpp
		MapFile.h
		Parser.cpp
		Parser.h
		Str.cpp
		Str.h
		Timer.cpp
		Timer.h
		Token.cpp
		Token.h
		bv/Bounds.cpp
		bv/Bounds.h
		bv/Box.cpp
		bv/Box.h
		bv/Frustum.cpp
		bv/Frustum.h
		bv/Sphere.cpp
		bv/Sphere.h
		containers/BTree.h
		containers/BinSearch.h
		containers/HashIndex.cpp
		containers/HashIndex.h
		containers/HashTable.h
		containers/Hierarchy.h
		containers/LinkList.h
		containers/List.h
		containers/PlaneSet.h
		containers/Queue.h
		containers/Stack.h
		containers/StaticList.h
		containers/StrList.h
		containers/StrPool.h
		containers/VectorSet.h
		geometry/DrawVert.cpp
		geometry/DrawVert.h
		geometry/JointTransform.cpp
		geometry/JointTransform.h
		geometry/Surface.cpp
		geometry/Surface.h
		geometry/Surface_Patch.cpp
		geometry/Surface_Patch.h
		geometry/Surface_Polytope.cpp
		geometry/Surface_Polytope.h
		geometry/Surface_SweptSpline.cpp
		geometry/Surface_SweptSpline.h
		geometry/TraceModel.cpp
		geometry/TraceModel.h
		geometry/Winding.cpp
		geometry/Winding.h
		geometry/Winding2D.cpp
		geometry/Winding2D.h
		hashing/CRC32.cpp
		hashing/CRC32.h
		hashing/MD4.cpp
		hashing/MD4.h
		hashing/MD5.cpp
		hashing/MD5.h
		math/Angles.cpp
		math/Angles.h
		math/Complex.cpp
		math/Complex.h
		math/Curve.h
		math/Extrapolate.h
		math/Interpolate.h
		math/Lcp.cpp
		math/Lcp.h
		math/Math.cpp
		math/Math.h
		math/Matrix.cpp
		math/Matrix.h
		math/Ode.cpp
		math/Ode.h
		math/Plane.cpp
		math/Plane.h
		math/Pluecker.cpp
		math/Pluecker.h
		math/Polynomial.cpp
		math/Polynomial.h
		math/Quat.cpp
		math/Quat.h
		math/Random.h
		math/Rotation.cpp
		math/Rotation.h
		math/Simd.cpp
		math/Simd.h
		math/Simd_3DNow.cpp
		math/Simd_3DNow.h
		math/Simd_AltiVec.h
		math/Simd_Generic.cpp
		math/Simd_Generic.h
		math/Simd_MMX.cpp
		math/Simd_MMX.h
		math/Simd_SSE.cpp
		math/Simd_SSE.h
		math/Simd_SSE2.cpp
		math/Simd_SSE2.h
		math/Simd_SSE3.cpp
		math/Simd_SSE3.h
		math/Vector.cpp
		math/Vector.h
		precompiled.h
)
