IDT4: Unofficial source port for idTech4 based games
====================================================
WORK-IN-PROGRESS


Contents
========

1. Disclaimer
2. Compiling  
   2.1 Minimum requirements
   2.2 CMake options
3. Links


1 - Disclaimer
==============

Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company.  
Copyright (c) 2022 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.  
SPDX-License-Identifier: GPL-3.0-only AND MIT

All dependencies are licensed under their own license (see README.txt).  
Original or mixed source code files are licensed under GPL 3.0 (see LICENSE.md).  
Completely new source code files are licensed under MIT unless otherwise stated (see LICENSE.md).


2 - Compiling
=============


2.1 - Minimum requirements
==========================

- [CMake 3.16.9](https://cmake.org/)
- Visual C++ 7.0 (2002)


2.2 - CMake options
===================

- `IDT4_PRECOMPILE_HEADERS`  
  Precompiles the headers.  
  Default value: `ON` (Always `OFF` for Visual C++ 7.0 (2002) and Visual Studio 9.0 (2008))

- `IDT4_MULTI_PROCESS_COMPILATION`  
  Utilizes multi-process compilation.  
  Default value: `ON`

- `IDT4_VANILLA`  
  Builds original source code only.  
  Default value: `OFF`

- `IDT4_VANILLA_FIX_COMPILATION_ERRORS`  
  Fixes compilation errors in the original source code for newer compilers.  
  Default value: `ON`

- `IDT4_MFC`  
  Utilizes MFC to build the editor.  
  Default value: `ON`

- `IDT4_DIRECTX_DIR`  
  Required path to DirectX headers and libraries.  
  Expected directory layout: `include`, `lib/x86`  
  Requires `dxerr.h` and `dxerr.lib` from DirectX 8/9.


3 - Links
=========
- [Dependencies for building](https://github.com/bibendovsky/idt4_dependencies)
