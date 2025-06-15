#[[
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company. 
Copyright (c) 2022 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only AND MIT
]]

cmake_minimum_required(VERSION 3.16.9 FATAL_ERROR)
project(idt4_id_lib_mfc VERSION 1.0.0 LANGUAGES CXX)

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
	PRIVATE
		IDT4_MFC
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		../idlib
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		idt4::directx
)

if(idt4_pch)
	target_precompile_headers(${PROJECT_NAME}
		PRIVATE
			../idlib/precompiled.h
	)
endif()

target_sources(${PROJECT_NAME}
	PRIVATE
		../idlib/Base64.cpp
		../idlib/Base64.h
		../idlib/BitMsg.cpp
		../idlib/BitMsg.h
		../idlib/CmdArgs.cpp
		../idlib/CmdArgs.h
		../idlib/Dict.cpp
		../idlib/Dict.h
		../idlib/Heap.cpp
		../idlib/Heap.h
		../idlib/LangDict.cpp
		../idlib/LangDict.h
		../idlib/Lexer.cpp
		../idlib/Lexer.h
		../idlib/Lib.cpp
		../idlib/Lib.h
		../idlib/MapFile.cpp
		../idlib/MapFile.h
		../idlib/Parser.cpp
		../idlib/Parser.h
		../idlib/Str.cpp
		../idlib/Str.h
		../idlib/Timer.cpp
		../idlib/Timer.h
		../idlib/Token.cpp
		../idlib/Token.h
		../idlib/bv/Bounds.cpp
		../idlib/bv/Bounds.h
		../idlib/bv/Box.cpp
		../idlib/bv/Box.h
		../idlib/bv/Frustum.cpp
		../idlib/bv/Frustum.h
		../idlib/bv/Sphere.cpp
		../idlib/bv/Sphere.h
		../idlib/containers/BTree.h
		../idlib/containers/BinSearch.h
		../idlib/containers/HashIndex.cpp
		../idlib/containers/HashIndex.h
		../idlib/containers/HashTable.h
		../idlib/containers/Hierarchy.h
		../idlib/containers/LinkList.h
		../idlib/containers/List.h
		../idlib/containers/PlaneSet.h
		../idlib/containers/Queue.h
		../idlib/containers/Stack.h
		../idlib/containers/StaticList.h
		../idlib/containers/StrList.h
		../idlib/containers/StrPool.h
		../idlib/containers/VectorSet.h
		../idlib/geometry/DrawVert.cpp
		../idlib/geometry/DrawVert.h
		../idlib/geometry/JointTransform.cpp
		../idlib/geometry/JointTransform.h
		../idlib/geometry/Surface.cpp
		../idlib/geometry/Surface.h
		../idlib/geometry/Surface_Patch.cpp
		../idlib/geometry/Surface_Patch.h
		../idlib/geometry/Surface_Polytope.cpp
		../idlib/geometry/Surface_Polytope.h
		../idlib/geometry/Surface_SweptSpline.cpp
		../idlib/geometry/Surface_SweptSpline.h
		../idlib/geometry/TraceModel.cpp
		../idlib/geometry/TraceModel.h
		../idlib/geometry/Winding.cpp
		../idlib/geometry/Winding.h
		../idlib/geometry/Winding2D.cpp
		../idlib/geometry/Winding2D.h
		../idlib/hashing/CRC32.cpp
		../idlib/hashing/CRC32.h
		../idlib/hashing/MD4.cpp
		../idlib/hashing/MD4.h
		../idlib/hashing/MD5.cpp
		../idlib/hashing/MD5.h
		../idlib/math/Angles.cpp
		../idlib/math/Angles.h
		../idlib/math/Complex.cpp
		../idlib/math/Complex.h
		../idlib/math/Curve.h
		../idlib/math/Extrapolate.h
		../idlib/math/Interpolate.h
		../idlib/math/Lcp.cpp
		../idlib/math/Lcp.h
		../idlib/math/Math.cpp
		../idlib/math/Math.h
		../idlib/math/Matrix.cpp
		../idlib/math/Matrix.h
		../idlib/math/Ode.cpp
		../idlib/math/Ode.h
		../idlib/math/Plane.cpp
		../idlib/math/Plane.h
		../idlib/math/Pluecker.cpp
		../idlib/math/Pluecker.h
		../idlib/math/Polynomial.cpp
		../idlib/math/Polynomial.h
		../idlib/math/Quat.cpp
		../idlib/math/Quat.h
		../idlib/math/Random.h
		../idlib/math/Rotation.cpp
		../idlib/math/Rotation.h
		../idlib/math/Simd.cpp
		../idlib/math/Simd.h
		../idlib/math/Simd_3DNow.cpp
		../idlib/math/Simd_3DNow.h
		../idlib/math/Simd_AltiVec.h
		../idlib/math/Simd_Generic.cpp
		../idlib/math/Simd_Generic.h
		../idlib/math/Simd_MMX.cpp
		../idlib/math/Simd_MMX.h
		../idlib/math/Simd_SSE.cpp
		../idlib/math/Simd_SSE.h
		../idlib/math/Simd_SSE2.cpp
		../idlib/math/Simd_SSE2.h
		../idlib/math/Simd_SSE3.cpp
		../idlib/math/Simd_SSE3.h
		../idlib/math/Vector.cpp
		../idlib/math/Vector.h
		../idlib/precompiled.h
)
