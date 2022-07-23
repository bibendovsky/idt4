#[[
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company. 
Copyright (c) 2022 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only AND MIT
]]

cmake_minimum_required(VERSION 3.16.9 FATAL_ERROR)
project(idt4_d3_game_xp VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "[${PROJECT_NAME}] Version: ${PROJECT_VERSION}")

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		CXX_STANDARD 98
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
		OUTPUT_NAME "gamex86"
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		__DOOM__
		GAME_DLL
		_D3XP
		CTF
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

set_source_files_properties(
		gamesys/TypeInfo.cpp
	PROPERTIES
		SKIP_PRECOMPILE_HEADERS TRUE
)

target_sources(${PROJECT_NAME}
	PRIVATE
		AF.cpp
		AF.h
		AFEntity.cpp
		AFEntity.h
		Actor.cpp
		Actor.h
		BrittleFracture.cpp
		BrittleFracture.h
		Camera.cpp
		Camera.h
		Entity.cpp
		Entity.h
		Fx.cpp
		Fx.h
		Game.h
		GameEdit.cpp
		GameEdit.h
		Game_local.cpp
		Game_local.h
		Game_network.cpp
		Grabber.cpp
		Grabber.h
		IK.cpp
		IK.h
		Item.cpp
		Item.h
		Light.cpp
		Light.h
		Misc.cpp
		Misc.h
		Moveable.cpp
		Moveable.h
		Mover.cpp
		Mover.h
		MultiplayerGame.cpp
		MultiplayerGame.h
		Player.cpp
		Player.h
		PlayerIcon.cpp
		PlayerIcon.h
		PlayerView.cpp
		PlayerView.h
		Projectile.cpp
		Projectile.h
		Pvs.cpp
		Pvs.h
		SecurityCamera.cpp
		SecurityCamera.h
		SmokeParticles.cpp
		SmokeParticles.h
		Sound.cpp
		Sound.h
		Target.cpp
		Target.h
		Trigger.cpp
		Trigger.h
		Weapon.cpp
		Weapon.h
		WorldSpawn.cpp
		WorldSpawn.h
		ai/AAS.cpp
		ai/AAS.h
		ai/AAS_debug.cpp
		ai/AAS_local.h
		ai/AAS_pathing.cpp
		ai/AAS_routing.cpp
		ai/AI.cpp
		ai/AI.h
		ai/AI_Vagary.cpp
		ai/AI_events.cpp
		ai/AI_pathing.cpp
		anim/Anim.cpp
		anim/Anim.h
		anim/Anim_Blend.cpp
		anim/Anim_Import.cpp
		anim/Anim_Testmodel.cpp
		anim/Anim_Testmodel.h
		gamesys/Class.cpp
		gamesys/Class.h
		gamesys/DebugGraph.cpp
		gamesys/DebugGraph.h
		gamesys/Event.cpp
		gamesys/Event.h
		gamesys/NoGameTypeInfo.h
		gamesys/SaveGame.cpp
		gamesys/SaveGame.h
		gamesys/SysCmds.cpp
		gamesys/SysCmds.h
		gamesys/SysCvar.cpp
		gamesys/SysCvar.h
		gamesys/TypeInfo.cpp
		physics/Clip.cpp
		physics/Clip.h
		physics/Force.cpp
		physics/Force.h
		physics/Force_Constant.cpp
		physics/Force_Constant.h
		physics/Force_Drag.cpp
		physics/Force_Drag.h
		physics/Force_Field.cpp
		physics/Force_Field.h
		physics/Force_Grab.cpp
		physics/Force_Grab.h
		physics/Force_Spring.cpp
		physics/Force_Spring.h
		physics/Physics.cpp
		physics/Physics.h
		physics/Physics_AF.cpp
		physics/Physics_AF.h
		physics/Physics_Actor.cpp
		physics/Physics_Actor.h
		physics/Physics_Base.cpp
		physics/Physics_Base.h
		physics/Physics_Monster.cpp
		physics/Physics_Monster.h
		physics/Physics_Parametric.cpp
		physics/Physics_Parametric.h
		physics/Physics_Player.cpp
		physics/Physics_Player.h
		physics/Physics_RigidBody.cpp
		physics/Physics_RigidBody.h
		physics/Physics_Static.cpp
		physics/Physics_Static.h
		physics/Physics_StaticMulti.cpp
		physics/Physics_StaticMulti.h
		physics/Push.cpp
		physics/Push.h
		script/Script_Compiler.cpp
		script/Script_Compiler.h
		script/Script_Interpreter.cpp
		script/Script_Interpreter.h
		script/Script_Program.cpp
		script/Script_Program.h
		script/Script_Thread.cpp
		script/Script_Thread.h
)

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION "./d3xp"
)
