IDT4: Unofficial source port for idTech4 based games
====================================================

```
!!! WARNING !!!!!!!!!!!!  
!!! WORK-IN-PROGRESS !!!  
!!!!!!!!!!!!!!!!!!!!!!!!
```

Contents
========

1. Disclaimer
2. Compiling  
   2.1 Minimum requirements  
   2.2 CMake options
3. Fixed bugs  
   3.1 Doom 3 (2004)
4. Features  
   4.1 OpenAL EFX  
   4.2 Audio limiter  
   4.3 Borderless mode
5. Links


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
  Default value: `ON` (Implicitly `OFF` for Visual C++ 7.0 (2002) and Visual Studio 9.0 (2008))

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


3 - Fixed bugs
==============

3.1 - Doom 3 (2004)
===================

- [EAX visual twitch.](https://www.pcgamingwiki.com/wiki/Doom_3#Visual_twitch_bug_with_OpenAL.2FEAX)
- [Defaults for EAX reverb properties.](https://www.pcgamingwiki.com/wiki/Doom_3#Incorrect_EAX_effect_in_Doom3:_Ressurection_of_evil_with_OpenAL.2FEAX)
- Deleting attached OpenAL buffer.
- Video RAM size detection.


4 - Features
============

4.1 - OpenAL EFX
================

An alternative to OpenAL EAX extension.

Allows to utilize EAX effects without EAX 4.0+ hardware.

Minimum requirements for OpenAL EFX implementation:
- One auxiliary send (ALC_MAX_AUXILIARY_SENDS context property).
- EAX or standard reverb effect type (AL_EFFECT_EAXREVERB or AL_EFFECT_REVERB).
- Low-pass filter type (AL_FILTER_LOWPASS).

New CVARs:
- `s_preferAlEfx <0|1>`  
  Tries to initialize OpenAL EFX extension first, if value set to `1` and the system supports for both extensions.  
  Default value: `0`


4.2 - Audio limiter
===================

Maintains an overall volume of all mixed samples below the master one, specified in the menu or in CVAR `s_volume_dB`.

_!!! Not available for OpenAL backend !!!_

New CVARs:
- `s_limiter <0|1>`  
  Enables the limiter if `value` set to `1`.  
  Default value: `0`


4.3 - Borderless mode
=====================

Creates a borderless window of desktop size without changing the display mode.

New CVARs:
- `r_preferBorderless <0|1>`  
  Tries to use borderless mode if value set to `1` and CVAR `r_fullscreen` set to `1`.  
  Default value: `0`


5 - Links
=========
- [Dependencies for building](https://github.com/bibendovsky/idt4_dependencies)
