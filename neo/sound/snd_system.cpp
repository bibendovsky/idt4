/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company. 

This file is part of the Doom 3 GPL Source Code (?Doom 3 Source Code?).  

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#include "../idlib/precompiled.h"
#pragma hdrstop

#include "snd_local.h"

#ifdef ID_DEDICATED
idCVar idSoundSystemLocal::s_noSound( "s_noSound", "1", CVAR_SOUND | CVAR_BOOL | CVAR_ROM, "" );
#else
idCVar idSoundSystemLocal::s_noSound( "s_noSound", "0", CVAR_SOUND | CVAR_BOOL | CVAR_NOCHEAT, "" );
#endif
idCVar idSoundSystemLocal::s_quadraticFalloff( "s_quadraticFalloff", "1", CVAR_SOUND | CVAR_BOOL, "" );
idCVar idSoundSystemLocal::s_drawSounds( "s_drawSounds", "0", CVAR_SOUND | CVAR_INTEGER, "", 0, 2, idCmdSystem::ArgCompletion_Integer<0,2> );
idCVar idSoundSystemLocal::s_showStartSound( "s_showStartSound", "0", CVAR_SOUND | CVAR_BOOL, "" );
idCVar idSoundSystemLocal::s_useOcclusion( "s_useOcclusion", "1", CVAR_SOUND | CVAR_BOOL, "" );
idCVar idSoundSystemLocal::s_maxSoundsPerShader( "s_maxSoundsPerShader", "0", CVAR_SOUND | CVAR_ARCHIVE, "", 0, 10, idCmdSystem::ArgCompletion_Integer<0,10> );
idCVar idSoundSystemLocal::s_showLevelMeter( "s_showLevelMeter", "0", CVAR_SOUND | CVAR_BOOL, "" );
idCVar idSoundSystemLocal::s_constantAmplitude( "s_constantAmplitude", "-1", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_minVolume6( "s_minVolume6", "0", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_dotbias6( "s_dotbias6", "0.8", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_minVolume2( "s_minVolume2", "0.25", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_dotbias2( "s_dotbias2", "1.1", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_spatializationDecay( "s_spatializationDecay", "2", CVAR_SOUND | CVAR_ARCHIVE | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_reverse( "s_reverse", "0", CVAR_SOUND | CVAR_ARCHIVE | CVAR_BOOL, "" );
idCVar idSoundSystemLocal::s_meterTopTime( "s_meterTopTime", "2000", CVAR_SOUND | CVAR_ARCHIVE | CVAR_INTEGER, "" );
idCVar idSoundSystemLocal::s_volume( "s_volume_dB", "0", CVAR_SOUND | CVAR_ARCHIVE | CVAR_FLOAT, "volume in dB" );
idCVar idSoundSystemLocal::s_playDefaultSound( "s_playDefaultSound", "1", CVAR_SOUND | CVAR_ARCHIVE | CVAR_BOOL, "play a beep for missing sounds" );
idCVar idSoundSystemLocal::s_subFraction( "s_subFraction", "0.75", CVAR_SOUND | CVAR_ARCHIVE | CVAR_FLOAT, "volume to subwoofer in 5.1" );
idCVar idSoundSystemLocal::s_globalFraction( "s_globalFraction", "0.8", CVAR_SOUND | CVAR_ARCHIVE | CVAR_FLOAT, "volume to all speakers when not spatialized" );
idCVar idSoundSystemLocal::s_doorDistanceAdd( "s_doorDistanceAdd", "150", CVAR_SOUND | CVAR_ARCHIVE | CVAR_FLOAT, "reduce sound volume with this distance when going through a door" );
idCVar idSoundSystemLocal::s_singleEmitter( "s_singleEmitter", "0", CVAR_SOUND | CVAR_INTEGER, "mute all sounds but this emitter" );
idCVar idSoundSystemLocal::s_numberOfSpeakers( "s_numberOfSpeakers", "2", CVAR_SOUND | CVAR_ARCHIVE, "number of speakers" );
idCVar idSoundSystemLocal::s_force22kHz( "s_force22kHz", "0", CVAR_SOUND | CVAR_BOOL, ""  );
idCVar idSoundSystemLocal::s_clipVolumes( "s_clipVolumes", "1", CVAR_SOUND | CVAR_BOOL, ""  );
idCVar idSoundSystemLocal::s_realTimeDecoding( "s_realTimeDecoding", "1", CVAR_SOUND | CVAR_BOOL | CVAR_INIT, "" );

idCVar idSoundSystemLocal::s_slowAttenuate( "s_slowAttenuate", "1", CVAR_SOUND | CVAR_BOOL, "slowmo sounds attenuate over shorted distance" );
idCVar idSoundSystemLocal::s_enviroSuitCutoffFreq( "s_enviroSuitCutoffFreq", "2000", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_enviroSuitCutoffQ( "s_enviroSuitCutoffQ", "2", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_reverbTime( "s_reverbTime", "1000", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_reverbFeedback( "s_reverbFeedback", "0.333", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_enviroSuitVolumeScale( "s_enviroSuitVolumeScale", "0.9", CVAR_SOUND | CVAR_FLOAT, "" );
idCVar idSoundSystemLocal::s_skipHelltimeFX( "s_skipHelltimeFX", "0", CVAR_SOUND | CVAR_BOOL, "" );

#if ID_OPENAL
// off by default. OpenAL DLL gets loaded on-demand
idCVar idSoundSystemLocal::s_libOpenAL( "s_libOpenAL", "openal32.dll", CVAR_SOUND | CVAR_ARCHIVE, "OpenAL DLL name/path" );
idCVar idSoundSystemLocal::s_useOpenAL( "s_useOpenAL", "0", CVAR_SOUND | CVAR_BOOL | CVAR_ARCHIVE, "use OpenAL" );
idCVar idSoundSystemLocal::s_useEAXReverb( "s_useEAXReverb", "0", CVAR_SOUND | CVAR_BOOL | CVAR_ARCHIVE, "use EAX reverb" );
idCVar idSoundSystemLocal::s_muteEAXReverb( "s_muteEAXReverb", "0", CVAR_SOUND | CVAR_BOOL, "mute eax reverb" );
idCVar idSoundSystemLocal::s_decompressionLimit( "s_decompressionLimit", "6", CVAR_SOUND | CVAR_INTEGER | CVAR_ARCHIVE, "specifies maximum uncompressed sample length in seconds" );
#else
idCVar idSoundSystemLocal::s_libOpenAL( "s_libOpenAL", "openal32.dll", CVAR_SOUND | CVAR_ARCHIVE, "OpenAL is not supported in this build" );
idCVar idSoundSystemLocal::s_useOpenAL( "s_useOpenAL", "0", CVAR_SOUND | CVAR_BOOL | CVAR_ROM, "OpenAL is not supported in this build" );
idCVar idSoundSystemLocal::s_useEAXReverb( "s_useEAXReverb", "0", CVAR_SOUND | CVAR_BOOL | CVAR_ROM, "EAX not available in this build" );
idCVar idSoundSystemLocal::s_muteEAXReverb( "s_muteEAXReverb", "0", CVAR_SOUND | CVAR_BOOL | CVAR_ROM, "mute eax reverb" );
idCVar idSoundSystemLocal::s_decompressionLimit( "s_decompressionLimit", "6", CVAR_SOUND | CVAR_INTEGER | CVAR_ROM, "specifies maximum uncompressed sample length in seconds" );
#endif

// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
const char* const idSoundSystemLocal::s_prefer_al_efx_cvar_name = "s_preferAlEfx";

idCVar idSoundSystemLocal::s_prefer_al_efx_cvar(
	s_prefer_al_efx_cvar_name,
	"0",
	CVAR_SOUND | CVAR_BOOL | CVAR_ARCHIVE,
	"Prefer OpenAL EFX over OpenAL EAX");
#endif

// IDT4-FEATURE-AUDIO-LIMITER
#ifndef IDT4_VANILLA
const char* const idSoundSystemLocal::s_limiter_cvar_name = "s_limiter";
idCVar idSoundSystemLocal::s_limiter_cvar(
	s_limiter_cvar_name,
	"0",
	CVAR_SOUND | CVAR_BOOL | CVAR_ARCHIVE,
	"Use audio limiter with a current volume as threshold.");
#endif

bool idSoundSystemLocal::useOpenAL = false;
bool idSoundSystemLocal::useEAXReverb = false;
int idSoundSystemLocal::EAXAvailable = -1;
// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
bool idSoundSystemLocal::al_efx_available = false;
#endif

idSoundSystemLocal	soundSystemLocal;
idSoundSystem	*soundSystem  = &soundSystemLocal;

/*
===============
SoundReloadSounds_f

  this is called from the main thread
===============
*/
void SoundReloadSounds_f( const idCmdArgs &args ) {
	if ( !soundSystemLocal.soundCache ) {
		return;
	}
	bool force = false;
	if ( args.Argc() == 2 ) {
		force = true;
	}
	soundSystem->SetMute( true );
	soundSystemLocal.soundCache->ReloadSounds( force );
	soundSystem->SetMute( false );
	common->Printf( "sound: changed sounds reloaded\n" );
}

/*
===============
ListSounds_f

Optional parameter to only list sounds containing that string
===============
*/
void ListSounds_f( const idCmdArgs &args ) {
	int i;
	const char	*snd = args.Argv( 1 );

	if ( !soundSystemLocal.soundCache ) {
		common->Printf( "No sound.\n" );
		return;
	}

	int	totalSounds = 0;
	int totalSamples = 0;
	int totalMemory = 0;
	int totalPCMMemory = 0;
	for( i = 0; i < soundSystemLocal.soundCache->GetNumObjects(); i++ ) {
		const idSoundSample *sample = soundSystemLocal.soundCache->GetObject(i);
		if ( !sample ) {
			continue;
		}
		if ( snd && sample->name.Find( snd, false ) < 0 ) {
			continue;
		}

		const waveformatex_t &info = sample->objectInfo;

		const char *stereo = ( info.nChannels == 2 ? "ST" : "  " );
		const char *format = ( info.wFormatTag == WAVE_FORMAT_TAG_OGG ) ? "OGG" : "WAV";
		const char *defaulted = ( sample->defaultSound ? "(DEFAULTED)" : sample->purged ? "(PURGED)" : "" );

		common->Printf( "%s %dkHz %6dms %5dkB %4s %s%s\n", stereo, sample->objectInfo.nSamplesPerSec / 1000,
					soundSystemLocal.SamplesToMilliseconds( sample->LengthIn44kHzSamples() ),
					sample->objectMemSize >> 10, format, sample->name.c_str(), defaulted );

		if ( !sample->purged ) {
			totalSamples += sample->objectSize;
			if ( info.wFormatTag != WAVE_FORMAT_TAG_OGG )
				totalPCMMemory += sample->objectMemSize;
			if ( !sample->hardwareBuffer )
				totalMemory += sample->objectMemSize;
		}
		totalSounds++;
	}
	common->Printf( "%8d total sounds\n", totalSounds );
	common->Printf( "%8d total samples loaded\n", totalSamples );
	common->Printf( "%8d kB total system memory used\n", totalMemory >> 10 );
#if ID_OPENAL
	common->Printf( "%8d kB total OpenAL audio memory used\n", ( alGetInteger( alGetEnumValue( (ALubyte*)"AL_EAX_RAM_SIZE" ) ) - alGetInteger( alGetEnumValue( (ALubyte*)"AL_EAX_RAM_FREE" ) ) ) >> 10 );
#endif
}

/*
===============
ListSoundDecoders_f
===============
*/
void ListSoundDecoders_f( const idCmdArgs &args ) {
	int i, j, numActiveDecoders, numWaitingDecoders;
	idSoundWorldLocal *sw = soundSystemLocal.currentSoundWorld;

	numActiveDecoders = numWaitingDecoders = 0;

	for ( i = 0; i < sw->emitters.Num(); i++ ) {
		idSoundEmitterLocal *sound = sw->emitters[i];

		if ( !sound ) {
			continue;
		}

		// run through all the channels
		for ( j = 0; j < SOUND_MAX_CHANNELS; j++ ) {
			idSoundChannel	*chan = &sound->channels[j];

			if ( chan->decoder == NULL ) {
				continue;
			}

			idSoundSample *sample = chan->decoder->GetSample();

			if ( sample != NULL ) {
				continue;
			}

			const char *format = ( chan->leadinSample->objectInfo.wFormatTag == WAVE_FORMAT_TAG_OGG ) ? "OGG" : "WAV";
			common->Printf( "%3d waiting %s: %s\n", numWaitingDecoders, format, chan->leadinSample->name.c_str() );

			numWaitingDecoders++;
		}
	}

	for ( i = 0; i < sw->emitters.Num(); i++ ) {
		idSoundEmitterLocal *sound = sw->emitters[i];

		if ( !sound ) {
			continue;
		}

		// run through all the channels
		for ( j = 0; j < SOUND_MAX_CHANNELS; j++ ) {
			idSoundChannel	*chan = &sound->channels[j];

			if ( chan->decoder == NULL ) {
				continue;
			}

			idSoundSample *sample = chan->decoder->GetSample();

			if ( sample == NULL ) {
				continue;
			}

			const char *format = ( sample->objectInfo.wFormatTag == WAVE_FORMAT_TAG_OGG ) ? "OGG" : "WAV";

			int localTime = soundSystemLocal.GetCurrent44kHzTime() - chan->trigger44kHzTime;
			int sampleTime = sample->LengthIn44kHzSamples() * sample->objectInfo.nChannels;
			int percent;
			if ( localTime > sampleTime ) {
				if ( chan->parms.soundShaderFlags & SSF_LOOPING ) {
					percent = ( localTime % sampleTime ) * 100 / sampleTime;
				} else {
					percent = 100;
				}
			} else {
				percent = localTime * 100 / sampleTime;
			}

			common->Printf( "%3d decoding %3d%% %s: %s\n", numActiveDecoders, percent, format, sample->name.c_str() );

			numActiveDecoders++;
		}
	}

	common->Printf( "%d decoders\n", numWaitingDecoders + numActiveDecoders );
	common->Printf( "%d waiting decoders\n", numWaitingDecoders );
	common->Printf( "%d active decoders\n", numActiveDecoders );
	common->Printf( "%d kB decoder memory in %d blocks\n", idSampleDecoder::GetUsedBlockMemory() >> 10, idSampleDecoder::GetNumUsedBlocks() );
}

/*
===============
TestSound_f

  this is called from the main thread
===============
*/
void TestSound_f( const idCmdArgs &args ) {
	if ( args.Argc() != 2 ) {
		common->Printf( "Usage: testSound <file>\n" );
		return;
	}
	if ( soundSystemLocal.currentSoundWorld ) {
		soundSystemLocal.currentSoundWorld->PlayShaderDirectly( args.Argv( 1 ) );
	}
}

/*
===============
SoundSystemRestart_f

restart the sound thread

  this is called from the main thread
===============
*/
void SoundSystemRestart_f( const idCmdArgs &args ) {
	soundSystem->SetMute( true );
	soundSystemLocal.ShutdownHW();
	soundSystemLocal.InitHW();
	soundSystem->SetMute( false );
}

/*
===============
idSoundSystemLocal::Init

initialize the sound system
===============
*/
void idSoundSystemLocal::Init() {

	common->Printf( "----- Initializing Sound System ------\n" );

	isInitialized = false;
	muted = false;
	shutdown = false;

	currentSoundWorld = NULL;
	soundCache = NULL;

	olddwCurrentWritePos = 0;
	buffers = 0;
	CurrentSoundTime = 0;

	nextWriteBlock = 0xffffffff;

	memset( meterTops, 0, sizeof( meterTops ) );
	memset( meterTopsTime, 0, sizeof( meterTopsTime ) );

	for( int i = -600; i < 600; i++ ) {
		float pt = i * 0.1f;
		volumesDB[i+600] = pow( 2.0f,( pt * ( 1.0f / 6.0f ) ) );
	}

	// make a 16 byte aligned finalMixBuffer
	finalMixBuffer = (float *) ( ( ( (int)realAccum ) + 15 ) & ~15 );

	graph = NULL;

	if ( !s_noSound.GetBool() ) {
		idSampleDecoder::Init();
		soundCache = new idSoundCache();
	}

	// set up openal device and context
	common->StartupVariable( "s_useOpenAL", true );
	common->StartupVariable( "s_useEAXReverb", true );

// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
	common->StartupVariable(s_prefer_al_efx_cvar_name, true);
	al_efx_available = false;
#endif

	if ( idSoundSystemLocal::s_useOpenAL.GetBool() || idSoundSystemLocal::s_useEAXReverb.GetBool() ) {
		if ( !Sys_LoadOpenAL() ) {
			idSoundSystemLocal::s_useOpenAL.SetBool( false );
		} else {
			common->Printf( "Setup OpenAL device and context... " );
			openalDevice = alcOpenDevice( NULL );
// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
			const bool prefer_al_efx = s_prefer_al_efx_cvar.GetBool();
			const bool previous_s_useEAXReverb = s_useEAXReverb.GetBool();
			ALubyte* const al_efx_ext_name = reinterpret_cast<ALubyte*>(const_cast<char*>(ALC_EXT_EFX_NAME));

			const ALCboolean al_efx_ext_present =
				(alcIsExtensionPresent(openalDevice, al_efx_ext_name) == ALC_TRUE);

			if (al_efx_ext_present)
			{
				ALCint custom_attributes[] =
				{
					// Reserve at-least one aux send.
					ALC_MAX_AUXILIARY_SENDS, 1,
					0,
				};

				openalContext = alcCreateContext(openalDevice, custom_attributes);
			}
			else
			{
				openalContext = alcCreateContext(openalDevice, NULL);
			}
#else
			openalContext = alcCreateContext( openalDevice, NULL );
#endif
			alcMakeContextCurrent( openalContext );
			common->Printf( "Done.\n" );

			// try to obtain EAX extensions
// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
			bool tried_efx = false;

			if (previous_s_useEAXReverb && al_efx_ext_present && prefer_al_efx)
			{
				tried_efx = true;

				if (al_efx_initialize())
				{
					s_useOpenAL.SetBool(true);
				}
			}

			if (!al_efx_available)
			{
#endif
			if ( idSoundSystemLocal::s_useEAXReverb.GetBool() && alIsExtensionPresent( ID_ALCHAR "EAX4.0" ) ) {
				idSoundSystemLocal::s_useOpenAL.SetBool( true );	// EAX presence causes AL enable
				alEAXSet = (EAXSet)alGetProcAddress( ID_ALCHAR "EAXSet" );
				alEAXGet = (EAXGet)alGetProcAddress( ID_ALCHAR "EAXGet" );
				common->Printf( "OpenAL: found EAX 4.0 extension\n" );
			} else {
				common->Printf( "OpenAL: EAX 4.0 extension not found\n" );
				idSoundSystemLocal::s_useEAXReverb.SetBool( false );
				alEAXSet = (EAXSet)NULL;
				alEAXGet = (EAXGet)NULL;
			}
// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
			}
#endif

			// try to obtain EAX-RAM extension - not required for operation
			if ( alIsExtensionPresent( ID_ALCHAR "EAX-RAM" ) == AL_TRUE ) {
				alEAXSetBufferMode = (EAXSetBufferMode)alGetProcAddress( ID_ALCHAR "EAXSetBufferMode" );
				alEAXGetBufferMode = (EAXGetBufferMode)alGetProcAddress( ID_ALCHAR "EAXGetBufferMode" );
				common->Printf( "OpenAL: found EAX-RAM extension, %dkB\\%dkB\n", alGetInteger( alGetEnumValue( ID_ALCHAR "AL_EAX_RAM_FREE" ) ) / 1024, alGetInteger( alGetEnumValue( ID_ALCHAR "AL_EAX_RAM_SIZE" ) ) / 1024 );
			} else {
				alEAXSetBufferMode = (EAXSetBufferMode)NULL;
				alEAXGetBufferMode = (EAXGetBufferMode)NULL;
				common->Printf( "OpenAL: no EAX-RAM extension\n" );
			}

// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
			const bool current_s_useEAXReverb = s_useEAXReverb.GetBool();

			if (previous_s_useEAXReverb &&
				!current_s_useEAXReverb &&
				!tried_efx &&
				al_efx_ext_present)
			{
				if (al_efx_initialize())
				{
					s_useOpenAL.SetBool(true);
					s_useEAXReverb.SetBool(true);
				}
			}

			if (!current_s_useEAXReverb && !al_efx_available)
			{
				s_useEAXReverb.SetBool(false);
			}
#endif

			if ( !idSoundSystemLocal::s_useOpenAL.GetBool() ) {
				common->Printf( "OpenAL: disabling ( no EAX ). Using legacy mixer.\n" );

				alcMakeContextCurrent( NULL );
		
				alcDestroyContext( openalContext );
				openalContext = NULL;
		
				alcCloseDevice( openalDevice );
				openalDevice = NULL;
			} else {

				ALuint handle;		
				openalSourceCount = 0;
				
				while ( openalSourceCount < 256 ) {
					alGetError();
					alGenSources( 1, &handle );
					if ( alGetError() != AL_NO_ERROR ) {
						break;
					} else {
						// store in source array
						openalSources[openalSourceCount].handle = handle;
						openalSources[openalSourceCount].startTime = 0;
						openalSources[openalSourceCount].chan = NULL;
						openalSources[openalSourceCount].inUse = false;
						openalSources[openalSourceCount].looping = false;

						// initialise sources
						alSourcef( handle, AL_ROLLOFF_FACTOR, 0.0f );

// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
						if (al_efx_available)
						{
							alSource3i(
								handle,
								AL_AUXILIARY_SEND_FILTER,
								static_cast<ALint>(al_efx_effect_slot),
								0,
								AL_FILTER_NULL);
						}
#endif

						// found one source
						openalSourceCount++;
					}
				}

				common->Printf( "OpenAL: found %s\n", alcGetString( openalDevice, ALC_DEVICE_SPECIFIER ) );
				common->Printf( "OpenAL: found %d hardware voices\n", openalSourceCount );

				// adjust source count to allow for at least eight stereo sounds to play
				openalSourceCount -= 8;

				EAXAvailable = 1;
			}
		}
	}

	useOpenAL = idSoundSystemLocal::s_useOpenAL.GetBool();
	useEAXReverb = idSoundSystemLocal::s_useEAXReverb.GetBool();

	cmdSystem->AddCommand( "listSounds", ListSounds_f, CMD_FL_SOUND, "lists all sounds" );
	cmdSystem->AddCommand( "listSoundDecoders", ListSoundDecoders_f, CMD_FL_SOUND, "list active sound decoders" );
	cmdSystem->AddCommand( "reloadSounds", SoundReloadSounds_f, CMD_FL_SOUND|CMD_FL_CHEAT, "reloads all sounds" );
	cmdSystem->AddCommand( "testSound", TestSound_f, CMD_FL_SOUND | CMD_FL_CHEAT, "tests a sound", idCmdSystem::ArgCompletion_SoundName );
	cmdSystem->AddCommand( "s_restart", SoundSystemRestart_f, CMD_FL_SOUND, "restarts the sound system" );

	common->Printf( "sound system initialized.\n" );
	common->Printf( "--------------------------------------\n" );
}

/*
===============
idSoundSystemLocal::Shutdown
===============
*/
void idSoundSystemLocal::Shutdown() {
	ShutdownHW();

	// EAX or not, the list needs to be cleared
	EFXDatabase.Clear();

	// destroy openal sources
	if ( useOpenAL ) {
		
		efxloaded = false;

		// adjust source count back up to allow for freeing of all resources
		openalSourceCount += 8;

		for ( ALsizei i = 0; i < openalSourceCount; i++ ) {
			// stop source
			alSourceStop( openalSources[i].handle );
			alSourcei( openalSources[i].handle, AL_BUFFER, 0 );
			
			// delete source
			alDeleteSources( 1, &openalSources[i].handle );

			// clear entry in source array
			openalSources[i].handle = NULL;
			openalSources[i].startTime = 0;
			openalSources[i].chan = NULL;
			openalSources[i].inUse = false;
			openalSources[i].looping = false;

		}

// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
		if (al_efx_symbols.alDeleteAuxiliaryEffectSlots != NULL)
		{
			al_efx_symbols.alDeleteAuxiliaryEffectSlots(1, &al_efx_effect_slot);
		}

		if (al_efx_symbols.alDeleteEffects != NULL)
		{
			al_efx_symbols.alDeleteEffects(1, &al_efx_effect);
		}

		if (al_efx_symbols.alDeleteFilters != NULL)
		{
			al_efx_symbols.alDeleteFilters(1, &al_efx_direct_filter);
			al_efx_symbols.alDeleteFilters(1, &al_efx_send_filter);
		}

		al_efx_available = false;
		al_efx_eax_reverb = false;
#endif
	}

	// destroy all the sounds (hardware buffers as well)
	delete soundCache;
	soundCache = NULL;

	// destroy openal device and context
	if ( useOpenAL ) {
		alcMakeContextCurrent( NULL );
		
		alcDestroyContext( openalContext );
		openalContext = NULL;
		
		alcCloseDevice( openalDevice );
		openalDevice = NULL;
	}

	Sys_FreeOpenAL();

	idSampleDecoder::Shutdown();
}

/*
===============
idSoundSystemLocal::InitHW
===============
*/
bool idSoundSystemLocal::InitHW() {

	if ( s_noSound.GetBool() ) {
		return false;
	}

	delete snd_audio_hw;
	snd_audio_hw = idAudioHardware::Alloc();

	if ( snd_audio_hw == NULL ) {
		return false;
	}

	if ( !useOpenAL ) {
		if ( !snd_audio_hw->Initialize() ) {
			delete snd_audio_hw;
			snd_audio_hw = NULL;
			return false;
		}

		if ( snd_audio_hw->GetNumberOfSpeakers() == 0 ) {
			return false;
		}
		// put the real number in there
		s_numberOfSpeakers.SetInteger( snd_audio_hw->GetNumberOfSpeakers() );
	}

	isInitialized = true;
	shutdown = false;

	return true;
}

/*
===============
idSoundSystemLocal::ShutdownHW
===============
*/
bool idSoundSystemLocal::ShutdownHW() {
	if ( !isInitialized ) {
		return false;
	}

	shutdown = true;		// don't do anything at AsyncUpdate() time
	Sys_Sleep( 100 );		// sleep long enough to make sure any async sound talking to hardware has returned

	common->Printf( "Shutting down sound hardware\n" );

	delete snd_audio_hw;
	snd_audio_hw = NULL;

	isInitialized = false;

	if ( graph ) {
		Mem_Free( graph );
		graph = NULL;
	}

	return true;
}

/*
===============
idSoundSystemLocal::GetCurrent44kHzTime
===============
*/
int idSoundSystemLocal::GetCurrent44kHzTime( void ) const {
	if ( snd_audio_hw ) {
		return CurrentSoundTime;
	} else {
		// NOTE: this would overflow 31bits within about 1h20 ( not that important since we get a snd_audio_hw right away pbly )
		//return ( ( Sys_Milliseconds()*441 ) / 10 ) * 4; 
		return idMath::FtoiFast( (float)Sys_Milliseconds() * 176.4f );
	}
}

/*
===================
idSoundSystemLocal::ClearBuffer
===================
*/
void idSoundSystemLocal::ClearBuffer( void ) {

	// check to make sure hardware actually exists
	if ( !snd_audio_hw ) {
		return;
	}

	short *fBlock;
	ulong fBlockLen;

	if ( !snd_audio_hw->Lock( (void **)&fBlock, &fBlockLen ) ) {
		return;
	}

	if ( fBlock ) {
		SIMDProcessor->Memset( fBlock, 0, fBlockLen );
		snd_audio_hw->Unlock( fBlock, fBlockLen );
	}
}

/*
===================
idSoundSystemLocal::AsyncMix
Mac OSX version. The system uses it's own thread and an IOProc callback
===================
*/
int idSoundSystemLocal::AsyncMix( int soundTime, float *mixBuffer ) {
	int	inTime, numSpeakers;

	if ( !isInitialized || shutdown || !snd_audio_hw ) {
		return 0;
	}

	inTime = Sys_Milliseconds();
	numSpeakers = snd_audio_hw->GetNumberOfSpeakers();
	
	// let the active sound world mix all the channels in unless muted or avi demo recording
	if ( !muted && currentSoundWorld && !currentSoundWorld->fpa[0] ) {
		currentSoundWorld->MixLoop( soundTime, numSpeakers, mixBuffer );
	}

	CurrentSoundTime = soundTime;
	
	return Sys_Milliseconds() - inTime;
}

/*
===================
idSoundSystemLocal::AsyncUpdate
called from async sound thread when com_asyncSound == 1 ( Windows )
===================
*/
int idSoundSystemLocal::AsyncUpdate( int inTime ) {

	if ( !isInitialized || shutdown || !snd_audio_hw ) {
		return 0;
	}

	ulong dwCurrentWritePos;
	dword dwCurrentBlock;

	// If not using openal, get actual playback position from sound hardware
	if ( useOpenAL ) {
		// here we do it in samples ( overflows in 27 hours or so )
		dwCurrentWritePos = idMath::Ftol( (float)Sys_Milliseconds() * 44.1f ) % ( MIXBUFFER_SAMPLES * ROOM_SLICES_IN_BUFFER );
		dwCurrentBlock = dwCurrentWritePos / MIXBUFFER_SAMPLES;
	} else {
		// and here in bytes
		// get the current byte position in the buffer where the sound hardware is currently reading
		if ( !snd_audio_hw->GetCurrentPosition( &dwCurrentWritePos ) ) {
			return 0;
		}
		// mixBufferSize is in bytes
		dwCurrentBlock = dwCurrentWritePos / snd_audio_hw->GetMixBufferSize();
	}

	if ( nextWriteBlock == 0xffffffff ) {
		nextWriteBlock = dwCurrentBlock;
	}

	if ( dwCurrentBlock != nextWriteBlock ) {
		return 0;
	}

	// lock the buffer so we can actually write to it
	short *fBlock = NULL;
	ulong fBlockLen = 0;
	if ( !useOpenAL ) {
		snd_audio_hw->Lock( (void **)&fBlock, &fBlockLen );
		if ( !fBlock ) {
			return 0;
		}
	}

	int j;
	soundStats.runs++;
	soundStats.activeSounds = 0;

	int	numSpeakers = snd_audio_hw->GetNumberOfSpeakers();

	nextWriteBlock++;
	nextWriteBlock %= ROOM_SLICES_IN_BUFFER;

	int newPosition = nextWriteBlock * MIXBUFFER_SAMPLES;

	if ( newPosition < olddwCurrentWritePos ) {
		buffers++;					// buffer wrapped
	}

	// nextWriteSample is in multi-channel samples inside the buffer
	int	nextWriteSamples = nextWriteBlock * MIXBUFFER_SAMPLES;

	olddwCurrentWritePos = newPosition;

	// newSoundTime is in multi-channel samples since the sound system was started
	int newSoundTime = ( buffers * MIXBUFFER_SAMPLES * ROOM_SLICES_IN_BUFFER ) + nextWriteSamples;
	
	// check for impending overflow
	// FIXME: we don't handle sound wrap-around correctly yet
	if ( newSoundTime > 0x6fffffff ) {
		buffers = 0;
	}

	if ( (newSoundTime - CurrentSoundTime) > (int)MIXBUFFER_SAMPLES ) {
		soundStats.missedWindow++;
	}

	if ( useOpenAL ) {
		// enable audio hardware caching
		alcSuspendContext( openalContext );
	} else {
		// clear the buffer for all the mixing output
		SIMDProcessor->Memset( finalMixBuffer, 0, MIXBUFFER_SAMPLES * sizeof(float) * numSpeakers );
	}

	// let the active sound world mix all the channels in unless muted or avi demo recording
	if ( !muted && currentSoundWorld && !currentSoundWorld->fpa[0] ) {
		currentSoundWorld->MixLoop( newSoundTime, numSpeakers, finalMixBuffer );
	}

	if ( useOpenAL ) {
		// disable audio hardware caching (this updates ALL settings since last alcSuspendContext)
		alcProcessContext( openalContext );
	} else {
// IDT4-FEATURE-AUDIO-LIMITER
#ifndef IDT4_VANILLA
		limiter_process(finalMixBuffer, MIXBUFFER_SAMPLES * numSpeakers);
#endif
		short *dest = fBlock + nextWriteSamples * numSpeakers;

		SIMDProcessor->MixedSoundToSamples( dest, finalMixBuffer, MIXBUFFER_SAMPLES * numSpeakers );

		// allow swapping the left / right speaker channels for people with miswired systems
		if ( numSpeakers == 2 && s_reverse.GetBool() ) {
			for( j = 0; j < MIXBUFFER_SAMPLES; j++ ) {
				short temp = dest[j*2];
				dest[j*2] = dest[j*2+1];
				dest[j*2+1] = temp;
			}
		}
		snd_audio_hw->Unlock( fBlock, fBlockLen );
	}

	CurrentSoundTime = newSoundTime;

	soundStats.timeinprocess = Sys_Milliseconds() - inTime;

	return soundStats.timeinprocess;
}

/*
===================
idSoundSystemLocal::AsyncUpdateWrite
sound output using a write API. all the scheduling based on time
we mix MIXBUFFER_SAMPLES at a time, but we feed the audio device with smaller chunks (and more often)
called by the sound thread when com_asyncSound is 3 ( Linux )
===================
*/
int idSoundSystemLocal::AsyncUpdateWrite( int inTime ) {

	if ( !isInitialized || shutdown || !snd_audio_hw ) {
		return 0;
	}

	if ( !useOpenAL ) {
		snd_audio_hw->Flush();
	}

	unsigned int dwCurrentBlock = (unsigned int)( inTime * 44.1f / MIXBUFFER_SAMPLES );

	if ( nextWriteBlock == 0xffffffff ) {
		nextWriteBlock = dwCurrentBlock;
	}

	if ( dwCurrentBlock < nextWriteBlock ) {
		return 0;
	}

	if ( nextWriteBlock != dwCurrentBlock ) {
		Sys_Printf( "missed %d sound updates\n", dwCurrentBlock - nextWriteBlock );
	}

	int sampleTime = dwCurrentBlock * MIXBUFFER_SAMPLES;	
	int numSpeakers = snd_audio_hw->GetNumberOfSpeakers();

	if ( useOpenAL ) {
		// enable audio hardware caching
		alcSuspendContext( openalContext );
	} else {
		// clear the buffer for all the mixing output
		SIMDProcessor->Memset( finalMixBuffer, 0, MIXBUFFER_SAMPLES * sizeof(float) * numSpeakers );
	}

	// let the active sound world mix all the channels in unless muted or avi demo recording
	if ( !muted && currentSoundWorld && !currentSoundWorld->fpa[0] ) {
		currentSoundWorld->MixLoop( sampleTime, numSpeakers, finalMixBuffer );
	}

	if ( useOpenAL ) {
		// disable audio hardware caching (this updates ALL settings since last alcSuspendContext)
		alcProcessContext( openalContext );
	} else {
// IDT4-FEATURE-AUDIO-LIMITER
#ifndef IDT4_VANILLA
		limiter_process(finalMixBuffer, MIXBUFFER_SAMPLES * numSpeakers);
#endif
		short *dest = snd_audio_hw->GetMixBuffer();

		SIMDProcessor->MixedSoundToSamples( dest, finalMixBuffer, MIXBUFFER_SAMPLES * numSpeakers );

		// allow swapping the left / right speaker channels for people with miswired systems
		if ( numSpeakers == 2 && s_reverse.GetBool() ) {
			int j;
			for( j = 0; j < MIXBUFFER_SAMPLES; j++ ) {
				short temp = dest[j*2];
				dest[j*2] = dest[j*2+1];
				dest[j*2+1] = temp;
			}
		}
		snd_audio_hw->Write( false );
	}

	// only move to the next block if the write was successful
	nextWriteBlock = dwCurrentBlock + 1;
	CurrentSoundTime = sampleTime;

	return Sys_Milliseconds() - inTime;
}

/*
===================
idSoundSystemLocal::dB2Scale
===================
*/
float idSoundSystemLocal::dB2Scale( const float val ) const {
	if ( val == 0.0f ) {
		return 1.0f;				// most common
	} else if ( val <= -60.0f ) {
		return 0.0f;
	} else if ( val >= 60.0f ) {
		return powf( 2.0f, val * ( 1.0f / 6.0f ) ); 
	}
	int ival = (int)( ( val + 60.0f ) * 10.0f );
	return volumesDB[ival];
}

/*
===================
idSoundSystemLocal::ImageForTime
===================
*/
cinData_t idSoundSystemLocal::ImageForTime( const int milliseconds, const bool waveform ) {
	cinData_t ret;
	int i, j;

	if ( !isInitialized || !snd_audio_hw ) {
		memset( &ret, 0, sizeof( ret ) );
		return ret;
	}

	Sys_EnterCriticalSection();

	if ( !graph ) {
		graph = (dword *)Mem_Alloc( 256*128 * 4);
	}
	memset( graph, 0, 256*128 * 4 );
	float *accum = finalMixBuffer;	// unfortunately, these are already clamped
	int time = Sys_Milliseconds();

	int numSpeakers = snd_audio_hw->GetNumberOfSpeakers();

	if ( !waveform ) {
		for( j = 0; j < numSpeakers; j++ ) {
			int meter = 0;
			for( i = 0; i < MIXBUFFER_SAMPLES; i++ ) {
				float result = idMath::Fabs(accum[i*numSpeakers+j]);
				if ( result > meter ) {
					meter = result;
				}
			}

			meter /= 256;		// 32768 becomes 128
			if ( meter > 128 ) {
				meter = 128;
			}
			int offset;
			int xsize;
			if ( numSpeakers == 6 ) {
				offset = j * 40;
				xsize = 20;
			} else {
				offset = j * 128;
				xsize = 63;
			}
			int x,y;
			dword color = 0xff00ff00;
			for ( y = 0; y < 128; y++ ) {
				for ( x = 0; x < xsize; x++ ) {
					graph[(127-y)*256 + offset + x ] = color;
				}
#if 0
				if ( y == 80 ) {
					color = 0xff00ffff;
				} else if ( y == 112 ) {
					color = 0xff0000ff;
				}
#endif
				if ( y > meter ) {
					break;
				}
			}

			if ( meter > meterTops[j] ) {
				meterTops[j] = meter;
				meterTopsTime[j] = time + s_meterTopTime.GetInteger();
			} else if ( time > meterTopsTime[j] && meterTops[j] > 0 ) {
				meterTops[j]--;
				if (meterTops[j]) {
					meterTops[j]--;
				}
			}
		}

		for( j = 0; j < numSpeakers; j++ ) {
			int meter = meterTops[j];

			int offset;
			int xsize;
			if ( numSpeakers == 6 ) {
				offset = j*40;
				xsize = 20;
			} else {
				offset = j*128;
				xsize = 63;
			}
			int x,y;
			dword color;
			if ( meter <= 80 ) {
				color = 0xff007f00;
			} else if ( meter <= 112 ) {
				color = 0xff007f7f;
			} else {
				color = 0xff00007f;
			}
			for ( y = meter; y < 128 && y < meter + 4; y++ ) {
				for ( x = 0; x < xsize; x++ ) {
					graph[(127-y)*256 + offset + x ] = color;
				}
			}
		}
	} else {
		dword colors[] = { 0xff007f00, 0xff007f7f, 0xff00007f, 0xff00ff00, 0xff00ffff, 0xff0000ff };

		for( j = 0; j < numSpeakers; j++ ) {
			int xx = 0;
			float fmeter;
			int step = MIXBUFFER_SAMPLES / 256;
			for( i = 0; i < MIXBUFFER_SAMPLES; i += step ) {
				fmeter = 0.0f;
				for( int x = 0; x < step; x++ ) {
					float result = accum[(i+x)*numSpeakers+j];
					result = result / 32768.0f;
					fmeter += result;
				}
				fmeter /= 4.0f;
				if ( fmeter < -1.0f ) {
					fmeter = -1.0f;
				} else if ( fmeter > 1.0f ) {
					fmeter = 1.0f;
				}
				int meter = (fmeter * 63.0f);
				graph[ (meter + 64) * 256 + xx ] = colors[j];

				if ( meter < 0 ) {
					meter = -meter;
				}
				if ( meter > meterTops[xx] ) {
					meterTops[xx] = meter;
					meterTopsTime[xx] = time + 100;
				} else if ( time>meterTopsTime[xx] && meterTops[xx] > 0 ) {
					meterTops[xx]--;
					if ( meterTops[xx] ) {
						meterTops[xx]--;
					}
				}
				xx++;
			}
		}
		for( i = 0; i < 256; i++ ) {
			int meter = meterTops[i];
			for ( int y = -meter; y < meter; y++ ) {
				graph[ (y+64)*256 + i ] = colors[j];
			}
		}
	}
	ret.imageHeight = 128;
	ret.imageWidth = 256;
	ret.image = (unsigned char *)graph;

	Sys_LeaveCriticalSection();

	return ret;
}

/*
===================
idSoundSystemLocal::GetSoundDecoderInfo
===================
*/
int idSoundSystemLocal::GetSoundDecoderInfo( int index, soundDecoderInfo_t &decoderInfo ) {
	int i, j, firstEmitter, firstChannel;
	idSoundWorldLocal *sw = soundSystemLocal.currentSoundWorld;

	if ( index < 0 ) {
		firstEmitter = 0;
		firstChannel = 0;
	} else {
		firstEmitter = index / SOUND_MAX_CHANNELS;
		firstChannel = index - firstEmitter * SOUND_MAX_CHANNELS + 1;
	}

	for ( i = firstEmitter; i < sw->emitters.Num(); i++ ) {
		idSoundEmitterLocal *sound = sw->emitters[i];

		if ( !sound ) {
			continue;
		}

		// run through all the channels
		for ( j = firstChannel; j < SOUND_MAX_CHANNELS; j++ ) {
			idSoundChannel	*chan = &sound->channels[j];

			if ( chan->decoder == NULL ) {
				continue;
			}

			idSoundSample *sample = chan->decoder->GetSample();

			if ( sample == NULL ) {
				continue;
			}

			decoderInfo.name = sample->name;
			decoderInfo.format = ( sample->objectInfo.wFormatTag == WAVE_FORMAT_TAG_OGG ) ? "OGG" : "WAV";
			decoderInfo.numChannels = sample->objectInfo.nChannels;
			decoderInfo.numSamplesPerSecond = sample->objectInfo.nSamplesPerSec;
			decoderInfo.num44kHzSamples = sample->LengthIn44kHzSamples();
			decoderInfo.numBytes = sample->objectMemSize;
			decoderInfo.looping = ( chan->parms.soundShaderFlags & SSF_LOOPING ) != 0;
			decoderInfo.lastVolume = chan->lastVolume;
			decoderInfo.start44kHzTime = chan->trigger44kHzTime;
			decoderInfo.current44kHzTime = soundSystemLocal.GetCurrent44kHzTime();

			return ( i * SOUND_MAX_CHANNELS + j );
		}

		firstChannel = 0;
	}
	return -1;
}

/*
===================
idSoundSystemLocal::AllocSoundWorld
===================
*/
idSoundWorld *idSoundSystemLocal::AllocSoundWorld( idRenderWorld *rw ) {
	idSoundWorldLocal	*local = new idSoundWorldLocal;

	local->Init( rw );

	return local;
}

/*
===================
idSoundSystemLocal::SetMute
===================
*/
void idSoundSystemLocal::SetMute( bool muteOn ) {
	muted = muteOn;
}

/*
===================
idSoundSystemLocal::SamplesToMilliseconds
===================
*/
int idSoundSystemLocal::SamplesToMilliseconds( int samples ) const {
	return ( samples / (PRIMARYFREQ/1000) );
}

/*
===================
idSoundSystemLocal::SamplesToMilliseconds
===================
*/
int idSoundSystemLocal::MillisecondsToSamples( int ms ) const {
	return ( ms * (PRIMARYFREQ/1000) );
}

/*
===================
idSoundSystemLocal::SetPlayingSoundWorld

specifying NULL will cause silence to be played
===================
*/
void idSoundSystemLocal::SetPlayingSoundWorld( idSoundWorld *soundWorld ) {
	currentSoundWorld = static_cast<idSoundWorldLocal *>(soundWorld);
}

/*
===================
idSoundSystemLocal::GetPlayingSoundWorld
===================
*/
idSoundWorld *idSoundSystemLocal::GetPlayingSoundWorld( void ) {
	return currentSoundWorld;
}

/*
===================
idSoundSystemLocal::BeginLevelLoad
===================
*/

void idSoundSystemLocal::BeginLevelLoad() {
	if ( !isInitialized ) {
		return;
	}
	soundCache->BeginLevelLoad();
	
	if ( efxloaded ) {
		EFXDatabase.UnloadFile();
		efxloaded = false;
	}
}

/*
===================
idSoundSystemLocal::EndLevelLoad
===================
*/
void idSoundSystemLocal::EndLevelLoad( const char *mapstring ) {
	if ( !isInitialized ) {
		return;
	}
	soundCache->EndLevelLoad();

	idStr efxname( "efxs/" );
	idStr mapname( mapstring );

	mapname.SetFileExtension( ".efx" );
	mapname.StripPath();
	efxname += mapname;

	efxloaded = EFXDatabase.LoadFile( efxname );

	if ( efxloaded ) {
		common->Printf("sound: found %s\n", efxname.c_str() );
	} else {
		common->Printf("sound: missing %s\n", efxname.c_str() );
	}
}

/*
===================
idSoundSystemLocal::AllocOpenALSource
===================
*/
ALuint idSoundSystemLocal::AllocOpenALSource( idSoundChannel *chan, bool looping, bool stereo ) {
	int timeOldestZeroVolSingleShot = Sys_Milliseconds();
	int timeOldestZeroVolLooping = Sys_Milliseconds();
	int timeOldestSingle = Sys_Milliseconds();
	int iOldestZeroVolSingleShot = -1;
	int iOldestZeroVolLooping = -1;
	int iOldestSingle = -1;
	int iUnused = -1;
	int index = -1;
	ALsizei i;

	// Grab current msec time
	int time = Sys_Milliseconds();

	// Cycle through all sources
	for ( i = 0; i < openalSourceCount; i++ ) {
		// Use any unused source first,
		// Then find oldest single shot quiet source,
		// Then find oldest looping quiet source and
		// Lastly find oldest single shot non quiet source..
		if ( !openalSources[i].inUse ) {
			iUnused = i;
			break;
		}  else if ( !openalSources[i].looping && openalSources[i].chan->lastVolume < SND_EPSILON ) {
			if ( openalSources[i].startTime < timeOldestZeroVolSingleShot ) {
				timeOldestZeroVolSingleShot = openalSources[i].startTime;
				iOldestZeroVolSingleShot = i;
			}
		} else if ( openalSources[i].looping && openalSources[i].chan->lastVolume < SND_EPSILON ) {
			if ( openalSources[i].startTime < timeOldestZeroVolLooping ) {
				timeOldestZeroVolLooping = openalSources[i].startTime;
				iOldestZeroVolLooping = i;
			}
		} else if ( !openalSources[i].looping ) {
			if ( openalSources[i].startTime < timeOldestSingle ) {
				timeOldestSingle = openalSources[i].startTime;
				iOldestSingle = i;
			}
		}
	}

	if ( iUnused != -1 ) {
		index = iUnused;
	} else if ( iOldestZeroVolSingleShot != - 1 ) {
		index = iOldestZeroVolSingleShot;
	} else if ( iOldestZeroVolLooping != -1 ) {
		index = iOldestZeroVolLooping;
	} else if ( iOldestSingle != -1 ) {
		index = iOldestSingle;
	}

	if ( index != -1 ) {
		// stop the channel that is being ripped off
		if ( openalSources[index].chan ) {
			// stop the channel only when not looping
			if ( !openalSources[index].looping ) {
				openalSources[index].chan->Stop();
			} else {
				openalSources[index].chan->triggered = true;
			}

			// Free hardware resources
			openalSources[index].chan->ALStop();
		}

		// Initialize structure
		openalSources[index].startTime = time;
		openalSources[index].chan = chan;
		openalSources[index].inUse = true;
		openalSources[index].looping = looping;
		openalSources[index].stereo = stereo;

		return openalSources[index].handle;
	} else {
		return NULL;
	}
}

/*
===================
idSoundSystemLocal::FreeOpenALSource
===================
*/
void idSoundSystemLocal::FreeOpenALSource( ALuint handle ) {
	ALsizei i;
	for ( i = 0; i < openalSourceCount; i++ ) {
		if ( openalSources[i].handle == handle ) {
			if ( openalSources[i].chan ) {
				openalSources[i].chan->openalSource = NULL;
// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
				openalSources[i].chan->al_efx_eax_occlusion_cached = false;
#endif
			}
#if ID_OPENAL
			// Reset source EAX ROOM level when freeing stereo source
			if ( openalSources[i].stereo && alEAXSet ) {
				long Room = EAXSOURCE_DEFAULTROOM;
				alEAXSet( &EAXPROPERTYID_EAX_Source, EAXSOURCE_ROOM, openalSources[i].handle, &Room, sizeof(Room));
			}
#endif
			// Initialize structure
			openalSources[i].startTime = 0;
			openalSources[i].chan = NULL;
			openalSources[i].inUse = false;
			openalSources[i].looping = false;
			openalSources[i].stereo = false;
		}
	}
}

/*
============================================================
SoundFX and misc effects
============================================================
*/

/*
===================
idSoundSystemLocal::ProcessSample
===================
*/
void SoundFX_Lowpass::ProcessSample( float* in, float* out ) {
	float c, a1, a2, a3, b1, b2;
	float resonance = idSoundSystemLocal::s_enviroSuitCutoffQ.GetFloat();
	float cutoffFrequency = idSoundSystemLocal::s_enviroSuitCutoffFreq.GetFloat();

	Initialize();

	c = 1.0 / idMath::Tan16( idMath::PI * cutoffFrequency / 44100 );

	// compute coefs
	a1 = 1.0 / ( 1.0 + resonance * c + c * c );
	a2 = 2* a1;
	a3 = a1;
	b1 = 2.0 * ( 1.0 - c * c) * a1;
	b2 = ( 1.0 - resonance * c + c * c ) * a1;

	// compute output value
	out[0] = a1 * in[0] + a2 * in[-1] + a3 * in[-2] - b1 * out[-1] - b2 * out[-2];
}

void SoundFX_LowpassFast::ProcessSample( float* in, float* out ) {
	// compute output value
	out[0] = a1 * in[0] + a2 * in[-1] + a3 * in[-2] - b1 * out[-1] - b2 * out[-2];
}

void SoundFX_LowpassFast::SetParms( float p1, float p2, float p3 ) {
	float c;

	// set the vars
	freq = p1;
	res = p2;

	// precompute the coefs
	c = 1.0 / idMath::Tan( idMath::PI * freq / 44100 );

	// compute coefs
	a1 = 1.0 / ( 1.0 + res * c + c * c );
	a2 = 2* a1;
	a3 = a1;

	b1 = 2.0 * ( 1.0 - c * c) * a1;
	b2 = ( 1.0 - res * c + c * c ) * a1;
}

void SoundFX_Comb::Initialize() {
	if ( initialized )
		return;

	initialized = true;
	maxlen = 50000;
	buffer = new float[maxlen];
	currentTime = 0;
}

void SoundFX_Comb::ProcessSample( float* in, float* out ) {
	float gain = idSoundSystemLocal::s_reverbFeedback.GetFloat();
	int len = idSoundSystemLocal::s_reverbTime.GetFloat() + param;

	Initialize();

	// sum up and output
	out[0] = buffer[currentTime];
	buffer[currentTime] = buffer[currentTime] * gain + in[0];

	// increment current time
	currentTime++;
	if ( currentTime >= len )
		currentTime -= len;
}

/*
===================
idSoundSystemLocal::DoEnviroSuit
===================
*/
void idSoundSystemLocal::DoEnviroSuit( float* samples, int numSamples, int numSpeakers ) {
	float out[10000], *out_p = out + 2;
	float in[10000], *in_p = in + 2;

	assert( !idSoundSystemLocal::useOpenAL );

	if ( !fxList.Num() ) {
		for ( int i = 0; i < 6; i++ ) {
			SoundFX* fx;

			// lowpass filter
			fx = new SoundFX_Lowpass();
			fx->SetChannel( i );
			fxList.Append( fx );

			// comb
			fx = new SoundFX_Comb();
			fx->SetChannel( i );
			fx->SetParameter( i * 100 );
			fxList.Append( fx );

			// comb
			fx = new SoundFX_Comb();
			fx->SetChannel( i );
			fx->SetParameter( i * 100 + 5 );
			fxList.Append( fx );
		}
	}

	for ( int i = 0; i < numSpeakers; i++ ) {
		int j;

		// restore previous samples
		memset( in, 0, 10000 * sizeof( float ) );
		memset( out, 0, 10000 * sizeof( float ) );

		// fx loop
		for ( int k = 0; k < fxList.Num(); k++ ) {
			SoundFX* fx = fxList[k];

			// skip if we're not the right channel
			if ( fx->GetChannel() != i )
				continue;

			// get samples and continuity
			fx->GetContinuitySamples( in_p[-1], in_p[-2], out_p[-1], out_p[-2] );
			for ( j = 0; j < numSamples; j++ ) {
				in_p[j] = samples[j * numSpeakers + i] * s_enviroSuitVolumeScale.GetFloat();
			}

			// process fx loop
			for ( j = 0; j < numSamples; j++ ) {
				fx->ProcessSample( in_p + j, out_p + j );
			}

			// store samples and continuity
			fx->SetContinuitySamples( in_p[numSamples-2], in_p[numSamples-3], out_p[numSamples-2], out_p[numSamples-3] );

			for ( j = 0; j < numSamples; j++ ) {
				samples[j * numSpeakers + i] = out_p[j];
			}
		}
	}
}

/*
=================
idSoundSystemLocal::PrintMemInfo
=================
*/
void idSoundSystemLocal::PrintMemInfo( MemInfo_t *mi ) {
	soundCache->PrintMemInfo( mi );
}

/*
===============
idSoundSystemLocal::EAXAvailable
===============
*/
int idSoundSystemLocal::IsEAXAvailable( void ) {
#if !ID_OPENAL
	return -1;
#else
	ALCdevice	*device;
	ALCcontext	*context;

	if ( EAXAvailable != -1 ) {
		return EAXAvailable;
	}

	if ( !Sys_LoadOpenAL() ) {
		EAXAvailable = 2;
		return 2;
	}
// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
	const bool prefer_al_efx = s_prefer_al_efx_cvar.GetBool();

	if (prefer_al_efx && al_efx_detect())
	{
		EAXAvailable = 1;
		return 1;
	}
#endif
	// when dynamically loading the OpenAL subsystem, we need to get a context before alIsExtensionPresent would work
	device = alcOpenDevice( NULL );
	context = alcCreateContext( device, NULL );
	alcMakeContextCurrent( context );
	if ( alIsExtensionPresent( ID_ALCHAR "EAX4.0" ) ) {
		alcMakeContextCurrent( NULL );
		alcDestroyContext( context );
		alcCloseDevice( device );
		EAXAvailable = 1;
		return 1;
	}
	alcMakeContextCurrent( NULL );
	alcDestroyContext( context );
	alcCloseDevice( device );
// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
	if (!prefer_al_efx && al_efx_detect())
	{
		EAXAvailable = 1;
		return 1;
	}
#endif
	EAXAvailable = 0;
	return 0;
#endif
}

// IDT4-FEATURE-OPENAL-EFX
#ifndef IDT4_VANILLA
namespace {

template<typename TSymbol>
void al_efx_resolve_symbol(const char* symbol_name, TSymbol& symbol)
{
	ALubyte* al_symbol_name = reinterpret_cast<ALubyte*>(const_cast<char*>(symbol_name));
	symbol = reinterpret_cast<TSymbol>(alGetProcAddress(al_symbol_name));

	if (symbol == NULL)
	{
		throw symbol_name;
	}
}

} // namespace

ALfloat idSoundSystemLocal::al_efx_mb_to_gain(float mb)
{
	if (mb <= al_efx_min_eax_mb)
	{
		return 0.0F;
	}

	return std::pow(10.0F, mb / 2000.0F);
}

void idSoundSystemLocal::al_efx_initialize_mb_to_gain_lut()
{
	struct MbToGain
	{
		ALfloat operator()(int mb) const
		{
			if (mb <= idSoundSystemLocal::al_efx_min_eax_mb)
			{
				return 0.0F;
			}

			return static_cast<ALfloat>(pow(10.0, static_cast<double>(mb) / 2000.0));
		}
	};

	MbToGain mb_to_gain;

	for (int i = 0; i < al_efx_mb_to_gain_lut_size; ++i)
	{
		al_efx_mb_to_gain_lut[i] = al_efx_clamp(
			mb_to_gain(al_efx_min_eax_mb + i),
			AL_EAXREVERB_MIN_LATE_REVERB_GAIN,
			AL_EAXREVERB_MAX_LATE_REVERB_GAIN);
	}
}

ALfloat idSoundSystemLocal::al_efx_lookup_gain(long eax_mb) const
{
	const long lut_index = eax_mb - al_efx_min_eax_mb;
	assert(lut_index >= 0 && lut_index < al_efx_mb_to_gain_lut_size);
	return al_efx_mb_to_gain_lut[lut_index];
}

void idSoundSystemLocal::al_efx_set_efx_density() const
{
	// efx_density = min(pow(eax_environment_size, 3) / 16, 1)

	const float eax_clamped = al_efx_clamp(
		al_efx_eax_props.flEnvironmentSize,
		EAXREVERB_MINENVIRONMENTSIZE,
		EAXREVERB_MAXENVIRONMENTSIZE);

	const ALfloat efx_unclamped = eax_clamped * eax_clamped * eax_clamped / 16.0F;

	const ALfloat efx = al_efx_clamp(
		efx_unclamped,
		AL_EAXREVERB_MIN_DENSITY,
		AL_EAXREVERB_MAX_DENSITY);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_DENSITY : AL_REVERB_DENSITY,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_diffusion() const
{
	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flEnvironmentDiffusion,
		EAXREVERB_MINENVIRONMENTDIFFUSION,
		EAXREVERB_MAXENVIRONMENTDIFFUSION);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_DIFFUSION : AL_REVERB_DIFFUSION,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_gain() const
{
	const long eax_clamped = al_efx_clamp(
		al_efx_eax_props.lRoom,
		static_cast<long>(EAXREVERB_MINROOM),
		static_cast<long>(EAXREVERB_MAXROOM));

	const ALfloat efx = al_efx_lookup_gain(eax_clamped);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_GAIN : AL_REVERB_GAIN,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_gain_hf() const
{
	const long eax_clamped = al_efx_clamp(
		al_efx_eax_props.lRoomHF,
		static_cast<long>(EAXREVERB_MINROOMHF),
		static_cast<long>(EAXREVERB_MAXROOMHF));

	const ALfloat efx = al_efx_lookup_gain(eax_clamped);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_GAINHF : AL_REVERB_GAINHF,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_gain_lf() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	const long eax_clamped = al_efx_clamp(
		al_efx_eax_props.lRoomLF,
		static_cast<long>(EAXREVERB_MINROOMLF),
		static_cast<long>(EAXREVERB_MAXROOMLF));

	const ALfloat efx = al_efx_lookup_gain(eax_clamped);
	al_efx_symbols.alEffectf(al_efx_effect, AL_EAXREVERB_GAINLF, efx);
}

void idSoundSystemLocal::al_efx_set_efx_decay_time() const
{
	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flDecayTime,
		EAXREVERB_MINDECAYTIME,
		EAXREVERB_MAXDECAYTIME);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_DECAY_TIME : AL_REVERB_DECAY_TIME,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_decay_hf_ratio() const
{
	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flDecayHFRatio,
		EAXREVERB_MINDECAYHFRATIO,
		EAXREVERB_MAXDECAYHFRATIO);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_DECAY_HFRATIO : AL_REVERB_DECAY_HFRATIO,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_decay_lf_ratio() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flDecayLFRatio,
		EAXREVERB_MINDECAYLFRATIO,
		EAXREVERB_MAXDECAYLFRATIO);

	al_efx_symbols.alEffectf(al_efx_effect, AL_EAXREVERB_DECAY_LFRATIO, efx);
}

void idSoundSystemLocal::al_efx_set_efx_reflections_gain() const
{
	const long eax_clamped = al_efx_clamp(
		al_efx_eax_props.lReflections,
		static_cast<long>(EAXREVERB_MINREFLECTIONS),
		static_cast<long>(EAXREVERB_MAXREFLECTIONS));

	const ALfloat efx = al_efx_lookup_gain(eax_clamped);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_REFLECTIONS_GAIN : AL_REVERB_REFLECTIONS_GAIN,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_reflections_delay() const
{
	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flReflectionsDelay,
		EAXREVERB_MINREFLECTIONSDELAY,
		EAXREVERB_MAXREFLECTIONSDELAY);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_REFLECTIONS_DELAY : AL_REVERB_REFLECTIONS_DELAY,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_reflections_pan() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	ALfloat efx[3] =
	{
		al_efx_eax_props.vReflectionsPan.x,
		al_efx_eax_props.vReflectionsPan.y,
		al_efx_eax_props.vReflectionsPan.z
	};

	al_efx_symbols.alEffectfv(al_efx_effect, AL_EAXREVERB_REFLECTIONS_PAN, efx);
}

void idSoundSystemLocal::al_efx_set_efx_late_reverb_gain() const
{
	const long eax_clamped = al_efx_clamp(
		al_efx_eax_props.lReverb,
		static_cast<long>(EAXREVERB_MINREVERB),
		static_cast<long>(EAXREVERB_MAXREVERB));

	const ALfloat efx = al_efx_lookup_gain(eax_clamped);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_LATE_REVERB_GAIN : AL_REVERB_LATE_REVERB_GAIN,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_late_reverb_delay() const
{
	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flReverbDelay,
		EAXREVERB_MINREVERBDELAY,
		EAXREVERB_MAXREVERBDELAY);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_LATE_REVERB_DELAY : AL_REVERB_LATE_REVERB_DELAY,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_late_reverb_pan() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	ALfloat efx[3] =
	{
		al_efx_eax_props.vReverbPan.x,
		al_efx_eax_props.vReverbPan.y,
		al_efx_eax_props.vReverbPan.z
	};

	al_efx_symbols.alEffectfv(al_efx_effect, AL_EAXREVERB_LATE_REVERB_PAN, efx);
}

void idSoundSystemLocal::al_efx_set_efx_echo_time() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flEchoTime,
		EAXREVERB_MINECHOTIME,
		EAXREVERB_MAXECHOTIME);

	al_efx_symbols.alEffectf(al_efx_effect, AL_EAXREVERB_ECHO_TIME, efx);
}

void idSoundSystemLocal::al_efx_set_efx_echo_depth() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flEchoDepth,
		EAXREVERB_MINECHODEPTH,
		EAXREVERB_MAXECHODEPTH);

	al_efx_symbols.alEffectf(al_efx_effect, AL_EAXREVERB_ECHO_DEPTH, efx);
}

void idSoundSystemLocal::al_efx_set_efx_modulation_time() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flModulationTime,
		EAXREVERB_MINMODULATIONTIME,
		EAXREVERB_MAXMODULATIONTIME);

	al_efx_symbols.alEffectf(al_efx_effect, AL_EAXREVERB_MODULATION_TIME, efx);
}

void idSoundSystemLocal::al_efx_set_efx_modulation_depth() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flModulationDepth,
		EAXREVERB_MINMODULATIONDEPTH,
		EAXREVERB_MAXMODULATIONDEPTH);

	al_efx_symbols.alEffectf(al_efx_effect, AL_EAXREVERB_MODULATION_DEPTH, efx);
}

void idSoundSystemLocal::al_efx_set_efx_air_absorption_hf() const
{
	const float eax_clamped = al_efx_clamp(
		al_efx_eax_props.flAirAbsorptionHF,
		EAXREVERB_MINAIRABSORPTIONHF,
		EAXREVERB_MAXAIRABSORPTIONHF);

	const ALfloat efx_unclamped = al_efx_mb_to_gain(eax_clamped);

	const ALfloat efx = al_efx_clamp(
		efx_unclamped,
		AL_EAXREVERB_MIN_AIR_ABSORPTION_GAINHF,
		AL_EAXREVERB_MAX_AIR_ABSORPTION_GAINHF);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_AIR_ABSORPTION_GAINHF : AL_REVERB_AIR_ABSORPTION_GAINHF,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_hf_reference() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flHFReference,
		EAXREVERB_MINHFREFERENCE,
		EAXREVERB_MAXHFREFERENCE);

	al_efx_symbols.alEffectf(al_efx_effect, AL_EAXREVERB_HFREFERENCE, efx);
}

void idSoundSystemLocal::al_efx_set_efx_lf_reference() const
{
	if (!al_efx_eax_reverb)
	{
		return;
	}

	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flLFReference,
		EAXREVERB_MINLFREFERENCE,
		EAXREVERB_MAXLFREFERENCE);

	al_efx_symbols.alEffectf(al_efx_effect, AL_EAXREVERB_LFREFERENCE, efx);
}

void idSoundSystemLocal::al_efx_set_efx_room_rolloff_factor() const
{
	const ALfloat efx = al_efx_clamp(
		al_efx_eax_props.flRoomRolloffFactor,
		EAXREVERB_MINROOMROLLOFFFACTOR,
		EAXREVERB_MAXROOMROLLOFFFACTOR);

	al_efx_symbols.alEffectf(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_ROOM_ROLLOFF_FACTOR : AL_REVERB_ROOM_ROLLOFF_FACTOR,
		efx);
}

void idSoundSystemLocal::al_efx_set_efx_decay_hf_limit() const
{
	const bool is_set = ((al_efx_eax_props.ulFlags & EAXREVERBFLAGS_DECAYHFLIMIT) != 0);

	al_efx_symbols.alEffecti(
		al_efx_effect,
		al_efx_eax_reverb ? AL_EAXREVERB_DECAY_HFLIMIT : AL_REVERB_DECAY_HFLIMIT,
		is_set ? AL_TRUE : AL_FALSE);
}

void idSoundSystemLocal::al_efx_load_effect_into_effect_slot() const
{
	al_efx_symbols.alAuxiliaryEffectSloti(
		static_cast<ALint>(al_efx_effect_slot),
		AL_EFFECTSLOT_EFFECT,
		static_cast<ALint>(al_efx_effect));
}

void idSoundSystemLocal::al_efx_set_reverb(const EAXREVERBPROPERTIES& eax_props)
{
	assert((alGetError(), true));

	bool changed = false;

	const EAXREVERBPROPERTIES& src_props = eax_props;
	EAXREVERBPROPERTIES& dst_props = al_efx_eax_props;

	if (dst_props.flEnvironmentSize != src_props.flEnvironmentSize)
	{
		changed = true;
		dst_props.flEnvironmentSize = src_props.flEnvironmentSize;
		al_efx_set_efx_density();
	}

	if (dst_props.flEnvironmentDiffusion != src_props.flEnvironmentDiffusion)
	{
		changed = true;
		dst_props.flEnvironmentDiffusion = src_props.flEnvironmentDiffusion;
		al_efx_set_efx_diffusion();
	}

	if (dst_props.lRoom != src_props.lRoom)
	{
		changed = true;
		dst_props.lRoom = src_props.lRoom;
		al_efx_set_efx_gain();
	}

	if (dst_props.lRoomHF != src_props.lRoomHF)
	{
		changed = true;
		dst_props.lRoomHF = src_props.lRoomHF;
		al_efx_set_efx_gain_hf();
	}

	if (dst_props.lRoomLF != src_props.lRoomLF)
	{
		changed |= al_efx_eax_reverb;
		dst_props.lRoomLF = src_props.lRoomLF;
		al_efx_set_efx_gain_lf();
	}

	if (dst_props.flDecayTime != src_props.flDecayTime)
	{
		changed = true;
		dst_props.flDecayTime = src_props.flDecayTime;
		al_efx_set_efx_decay_time();
	}

	if (dst_props.flDecayHFRatio != src_props.flDecayHFRatio)
	{
		changed = true;
		dst_props.flDecayHFRatio = src_props.flDecayHFRatio;
		al_efx_set_efx_decay_hf_ratio();
	}

	if (dst_props.flDecayLFRatio != src_props.flDecayLFRatio)
	{
		changed |= al_efx_eax_reverb;
		dst_props.flDecayLFRatio = src_props.flDecayLFRatio;
		al_efx_set_efx_decay_lf_ratio();
	}

	if (dst_props.lReflections != src_props.lReflections)
	{
		changed = true;
		dst_props.lReflections = src_props.lReflections;
		al_efx_set_efx_reflections_gain();
	}

	if (dst_props.flReflectionsDelay != src_props.flReflectionsDelay)
	{
		changed = true;
		dst_props.flReflectionsDelay = src_props.flReflectionsDelay;
		al_efx_set_efx_reflections_delay();
	}

	if (dst_props.vReflectionsPan.x != src_props.vReflectionsPan.x ||
		dst_props.vReflectionsPan.y != src_props.vReflectionsPan.y ||
		dst_props.vReflectionsPan.z != src_props.vReflectionsPan.z)
	{
		changed |= al_efx_eax_reverb;
		dst_props.vReflectionsPan.x = src_props.vReflectionsPan.x;
		dst_props.vReflectionsPan.y = src_props.vReflectionsPan.y;
		dst_props.vReflectionsPan.z = src_props.vReflectionsPan.z;
		al_efx_set_efx_reflections_pan();
	}

	if (dst_props.lReverb != src_props.lReverb)
	{
		changed = true;
		dst_props.lReverb = src_props.lReverb;
		al_efx_set_efx_late_reverb_gain();
	}

	if (dst_props.flReverbDelay != src_props.flReverbDelay)
	{
		changed = true;
		dst_props.flReverbDelay = src_props.flReverbDelay;
		al_efx_set_efx_late_reverb_delay();
	}

	if (dst_props.vReverbPan.x != src_props.vReverbPan.x ||
		dst_props.vReverbPan.y != src_props.vReverbPan.y ||
		dst_props.vReverbPan.z != src_props.vReverbPan.z)
	{
		changed |= al_efx_eax_reverb;
		dst_props.vReverbPan.x = src_props.vReverbPan.x;
		dst_props.vReverbPan.y = src_props.vReverbPan.y;
		dst_props.vReverbPan.z = src_props.vReverbPan.z;
		al_efx_set_efx_late_reverb_pan();
	}

	if (dst_props.flEchoTime != src_props.flEchoTime)
	{
		changed |= al_efx_eax_reverb;
		dst_props.flEchoTime = src_props.flEchoTime;
		al_efx_set_efx_echo_time();
	}

	if (dst_props.flEchoDepth != src_props.flEchoDepth)
	{
		changed |= al_efx_eax_reverb;
		dst_props.flEchoDepth = src_props.flEchoDepth;
		al_efx_set_efx_echo_depth();
	}

	if (dst_props.flModulationTime != src_props.flModulationTime)
	{
		changed |= al_efx_eax_reverb;
		dst_props.flModulationTime = src_props.flModulationTime;
		al_efx_set_efx_modulation_time();
	}

	if (dst_props.flModulationDepth != src_props.flModulationDepth)
	{
		changed |= al_efx_eax_reverb;
		dst_props.flModulationDepth = src_props.flModulationDepth;
		al_efx_set_efx_modulation_depth();
	}

	if (dst_props.flAirAbsorptionHF != src_props.flAirAbsorptionHF)
	{
		changed = true;
		dst_props.flAirAbsorptionHF = src_props.flAirAbsorptionHF;
		al_efx_set_efx_air_absorption_hf();
	}

	if (dst_props.flHFReference != src_props.flHFReference)
	{
		changed |= al_efx_eax_reverb;
		dst_props.flHFReference = src_props.flHFReference;
		al_efx_set_efx_hf_reference();
	}

	if (dst_props.flLFReference != src_props.flLFReference)
	{
		changed |= al_efx_eax_reverb;
		dst_props.flLFReference = src_props.flLFReference;
		al_efx_set_efx_lf_reference();
	}

	if (dst_props.flRoomRolloffFactor != src_props.flRoomRolloffFactor)
	{
		changed = true;
		dst_props.flRoomRolloffFactor = src_props.flRoomRolloffFactor;
		al_efx_set_efx_room_rolloff_factor();
	}

	if ((dst_props.ulFlags & EAXREVERBFLAGS_DECAYHFLIMIT) !=
		(src_props.ulFlags & EAXREVERBFLAGS_DECAYHFLIMIT))
	{
		changed = true;
		dst_props.ulFlags = src_props.ulFlags;
		al_efx_set_efx_decay_hf_limit();
	}

	if (changed)
	{
		al_efx_load_effect_into_effect_slot();
	}

	assert(alGetError() == AL_NO_ERROR);
}

void idSoundSystemLocal::al_efx_set_reverb_defaults()
{
	const EAXVECTOR reflections_pan = EAXREVERB_DEFAULTREFLECTIONSPAN;
	const EAXVECTOR reverb_pan = EAXREVERB_DEFAULTREVERBPAN;

	al_efx_eax_props.ulEnvironment = EAXREVERB_DEFAULTENVIRONMENT;
	al_efx_eax_props.flEnvironmentSize = EAXREVERB_DEFAULTENVIRONMENTSIZE;
	al_efx_eax_props.flEnvironmentDiffusion = EAXREVERB_DEFAULTENVIRONMENTDIFFUSION;
	al_efx_eax_props.lRoom = EAXREVERB_DEFAULTROOM;
	al_efx_eax_props.lRoomHF = EAXREVERB_DEFAULTROOMHF;
	al_efx_eax_props.lRoomLF = EAXREVERB_DEFAULTROOMLF;
	al_efx_eax_props.flDecayTime = EAXREVERB_DEFAULTDECAYTIME;
	al_efx_eax_props.flDecayHFRatio = EAXREVERB_DEFAULTDECAYHFRATIO;
	al_efx_eax_props.flDecayLFRatio = EAXREVERB_DEFAULTDECAYLFRATIO;
	al_efx_eax_props.lReflections = EAXREVERB_DEFAULTREFLECTIONS;
	al_efx_eax_props.flReflectionsDelay = EAXREVERB_DEFAULTREFLECTIONSDELAY;
	al_efx_eax_props.vReflectionsPan = reflections_pan;
	al_efx_eax_props.lReverb = EAXREVERB_DEFAULTREVERB;
	al_efx_eax_props.flReverbDelay = EAXREVERB_DEFAULTREVERBDELAY;
	al_efx_eax_props.vReverbPan = reverb_pan;
	al_efx_eax_props.flEchoTime = EAXREVERB_DEFAULTECHOTIME;
	al_efx_eax_props.flEchoDepth = EAXREVERB_DEFAULTECHODEPTH;
	al_efx_eax_props.flModulationTime = EAXREVERB_DEFAULTMODULATIONTIME;
	al_efx_eax_props.flModulationDepth = EAXREVERB_DEFAULTMODULATIONDEPTH;
	al_efx_eax_props.flAirAbsorptionHF = EAXREVERB_DEFAULTAIRABSORPTIONHF;
	al_efx_eax_props.flHFReference = EAXREVERB_DEFAULTHFREFERENCE;
	al_efx_eax_props.flLFReference = EAXREVERB_DEFAULTLFREFERENCE;
	al_efx_eax_props.flRoomRolloffFactor = EAXREVERB_DEFAULTROOMROLLOFFFACTOR;
	al_efx_eax_props.ulFlags = EAXREVERB_DEFAULTFLAGS;

	assert((alGetError(), true));

	al_efx_set_efx_density();
	al_efx_set_efx_diffusion();
	al_efx_set_efx_gain();
	al_efx_set_efx_gain_hf();
	al_efx_set_efx_gain_lf();
	al_efx_set_efx_decay_time();
	al_efx_set_efx_decay_hf_ratio();
	al_efx_set_efx_decay_lf_ratio();
	al_efx_set_efx_reflections_gain();
	al_efx_set_efx_reflections_delay();
	al_efx_set_efx_reflections_pan();
	al_efx_set_efx_late_reverb_gain();
	al_efx_set_efx_late_reverb_delay();
	al_efx_set_efx_late_reverb_pan();
	al_efx_set_efx_echo_time();
	al_efx_set_efx_echo_depth();
	al_efx_set_efx_modulation_time();
	al_efx_set_efx_modulation_depth();
	al_efx_set_efx_air_absorption_hf();
	al_efx_set_efx_hf_reference();
	al_efx_set_efx_lf_reference();
	al_efx_set_efx_room_rolloff_factor();
	al_efx_set_efx_decay_hf_limit();

	al_efx_load_effect_into_effect_slot();

	assert(alGetError() == AL_NO_ERROR);
}

void idSoundSystemLocal::al_efx_disable_source_send_0_and_filters(ALuint source_id) const
{
	alSourcei(source_id, AL_DIRECT_FILTER, AL_FILTER_NULL);
	alSource3i(source_id, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, AL_FILTER_NULL);
}

void idSoundSystemLocal::al_efx_calculate_occlusion(
	const AlEfxEaxOcclusionPathParam& eax,
	AlEfxLowPassFilterParam& efx)
{
	const float occlusion = static_cast<float>(eax.occlusion);
	const float ratio_1 = (eax.lf_ratio + eax.ratio) - 1.0F;
	const float ratio_2 = eax.lf_ratio * eax.ratio;
	const float ratio = (ratio_2 > ratio_1) ? ratio_2 : ratio_1;

	efx.gain = al_efx_mb_to_gain(occlusion * ratio);
	efx.gain_hf = al_efx_mb_to_gain(occlusion * eax.ratio);
}

void idSoundSystemLocal::al_efx_calculate_occlusion(
	const AlEfxEaxOcclusionParam& eax,
	AlEfxLowPassFilterParam& efx_direct,
	AlEfxLowPassFilterParam& efx_send)
{
	if (eax.occlusion <= EAXSOURCE_MINOCCLUSION)
	{
		efx_direct.gain = 0.0F;
		efx_direct.gain_hf = 0.0F;

		efx_send.gain = 0.0F;
		efx_send.gain_hf = 0.0F;

		return;
	}

	if (eax.occlusion >= EAXSOURCE_MAXOCCLUSION)
	{
		efx_direct.gain = 1.0F;
		efx_direct.gain_hf = 1.0F;

		efx_send.gain = 1.0F;
		efx_send.gain_hf = 1.0F;

		return;
	}

	AlEfxEaxOcclusionPathParam eax_path;
	eax_path.occlusion = eax.occlusion;
	eax_path.lf_ratio = eax.occlusion_lf_ratio;

	eax_path.ratio = eax.occlusion_direct_ratio;
	al_efx_calculate_occlusion(eax_path, efx_direct);
	efx_direct.gain = al_efx_clamp(efx_direct.gain, LOWPASS_MIN_GAIN, LOWPASS_MAX_GAIN);
	efx_direct.gain_hf = al_efx_clamp(efx_direct.gain_hf, LOWPASS_MIN_GAINHF, LOWPASS_MAX_GAINHF);

	eax_path.ratio = eax.occlusion_room_ratio;
	al_efx_calculate_occlusion(eax_path, efx_send);
	efx_send.gain = al_efx_clamp(efx_send.gain, LOWPASS_MIN_GAIN, LOWPASS_MAX_GAIN);
	efx_send.gain_hf = al_efx_clamp(efx_send.gain_hf, LOWPASS_MIN_GAINHF, LOWPASS_MAX_GAINHF);
}

void idSoundSystemLocal::al_efx_set_source_occlusion(idSoundChannel& sound_channel, long eax_occlusion)
{
	if (!sound_channel.al_efx_enabled_send_0)
	{
		return;
	}

	if (sound_channel.al_efx_eax_occlusion_cached &&
		sound_channel.al_efx_eax_occlusion_cache == eax_occlusion)
	{
		return;
	}

	assert((alGetError(), true));
	sound_channel.al_efx_eax_occlusion_cached = true;
	sound_channel.al_efx_eax_occlusion_cache = eax_occlusion;

	AlEfxEaxOcclusionParam eax;
	eax.occlusion = eax_occlusion;
	eax.occlusion_lf_ratio = EAXSOURCE_DEFAULTOCCLUSIONLFRATIO;
	eax.occlusion_room_ratio = EAXSOURCE_DEFAULTOCCLUSIONROOMRATIO;
	eax.occlusion_direct_ratio = EAXSOURCE_DEFAULTOCCLUSIONDIRECTRATIO;

	AlEfxLowPassFilterParam efx_direct;
	AlEfxLowPassFilterParam efx_send;
	al_efx_calculate_occlusion(eax, efx_direct, efx_send);

	const ALuint& source_id = sound_channel.openalSource;

	al_efx_symbols.alFilterf(al_efx_direct_filter, AL_LOWPASS_GAIN, efx_direct.gain);
	al_efx_symbols.alFilterf(al_efx_direct_filter, AL_LOWPASS_GAINHF, efx_direct.gain_hf);
	alSourcei(source_id, AL_DIRECT_FILTER, static_cast<ALint>(al_efx_direct_filter));

	al_efx_symbols.alFilterf(al_efx_send_filter, AL_LOWPASS_GAIN, efx_send.gain);
	al_efx_symbols.alFilterf(al_efx_send_filter, AL_LOWPASS_GAINHF, efx_send.gain_hf);

	alSource3i(
		source_id,
		AL_AUXILIARY_SEND_FILTER,
		static_cast<ALint>(al_efx_effect_slot),
		0,
		static_cast<ALint>(al_efx_send_filter));

	assert(alGetError() == AL_NO_ERROR);
}

void idSoundSystemLocal::al_efx_resolve_symbols(AlEfxSymbols& al_efx_symbols)
{
	al_efx_resolve_symbol("alGenEffects", al_efx_symbols.alGenEffects);
	al_efx_resolve_symbol("alDeleteEffects", al_efx_symbols.alDeleteEffects);
	al_efx_resolve_symbol("alEffecti", al_efx_symbols.alEffecti);
	al_efx_resolve_symbol("alEffectf", al_efx_symbols.alEffectf);
	al_efx_resolve_symbol("alEffectfv", al_efx_symbols.alEffectfv);

	al_efx_resolve_symbol("alGenFilters", al_efx_symbols.alGenFilters);
	al_efx_resolve_symbol("alDeleteFilters", al_efx_symbols.alDeleteFilters);
	al_efx_resolve_symbol("alFilteri", al_efx_symbols.alFilteri);
	al_efx_resolve_symbol("alFilterf", al_efx_symbols.alFilterf);

	al_efx_resolve_symbol("alGenAuxiliaryEffectSlots", al_efx_symbols.alGenAuxiliaryEffectSlots);
	al_efx_resolve_symbol("alDeleteAuxiliaryEffectSlots", al_efx_symbols.alDeleteAuxiliaryEffectSlots);
	al_efx_resolve_symbol("alAuxiliaryEffectSloti", al_efx_symbols.alAuxiliaryEffectSloti);
	al_efx_resolve_symbol("alGetAuxiliaryEffectSloti", al_efx_symbols.alGetAuxiliaryEffectSloti);
}

bool idSoundSystemLocal::al_efx_initialize()
{
	common->Printf("%s: Initialize EFX\n", "OpenAL");
	bool is_succeeded = true;

	ALint major_version = 0;
	ALint minor_version = 0;

	if (is_succeeded)
	{
		alcGetIntegerv(openalDevice, ALC_EFX_MAJOR_VERSION, 1, &major_version);
		alcGetIntegerv(openalDevice, ALC_EFX_MAJOR_VERSION, 1, &minor_version);

		if (major_version <= 0)
		{
			is_succeeded = false;
			common->Printf("%s: Unsupported version: %d.%d\n", "OpenAL", major_version, minor_version);
		}
	}

	ALint max_sends = 0;

	if (is_succeeded)
	{
		alcGetIntegerv(openalDevice, ALC_MAX_AUXILIARY_SENDS, 1, &max_sends);

		if (max_sends <= 0)
		{
			is_succeeded = false;
			common->Printf("%s: Not enough aux sends: %d\n", "OpenAL", max_sends);
		}
	}

	if (is_succeeded)
	{
		try
		{
			al_efx_resolve_symbols(al_efx_symbols);
		}
		catch (const char* failed_symbol_name)
		{
			is_succeeded = false;
			common->Printf("%s: Missing symbol: %s\n", "OpenAL", failed_symbol_name);
		}
	}

	al_efx_effect_slot = AL_NONE;

	if (is_succeeded)
	{
		alGetError();
		al_efx_symbols.alGenAuxiliaryEffectSlots(1, &al_efx_effect_slot);

		if (alGetError() != AL_NO_ERROR)
		{
			is_succeeded = false;
			common->Printf("%s: Failed to create EFX effect slot\n", "OpenAL");
		}
	}

	al_efx_effect = AL_NONE;

	if (is_succeeded)
	{
		alGetError();
		al_efx_symbols.alGenEffects(1, &al_efx_effect);

		if (alGetError() == AL_NO_ERROR)
		{
			// Note: The order of alEffecti is important here.

			al_efx_symbols.alEffecti(al_efx_effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
			const bool has_std_reverb = (alGetError() == AL_NO_ERROR);

			al_efx_symbols.alEffecti(al_efx_effect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
			const bool has_eax_reverb = (alGetError() == AL_NO_ERROR);

			if (has_eax_reverb)
			{
				al_efx_eax_reverb = true;
			}
			else if (has_std_reverb)
			{
				al_efx_eax_reverb = false;
			}
			else
			{
				is_succeeded = false;
				common->Printf("%s: No reverb effect\n", "OpenAL");
			}
		}
		else
		{
			is_succeeded = false;
			common->Printf("%s: Failed to create an effect\n", "OpenAL");
		}
	}

	al_efx_direct_filter = AL_FILTER_NULL;
	al_efx_send_filter = AL_FILTER_NULL;

	if (is_succeeded)
	{
		const int filter_count = 2;
		ALuint filters[filter_count] = {AL_FILTER_NULL, AL_FILTER_NULL};

		alGetError();
		al_efx_symbols.alGenFilters(filter_count, filters);

		if (alGetError() == AL_NO_ERROR)
		{
			for (int i = 0; is_succeeded && i < filter_count; ++i)
			{
				alGetError();
				al_efx_symbols.alFilteri(filters[i], AL_FILTER_TYPE, AL_FILTER_LOWPASS);
				const bool has_low_pass_filter = (alGetError() == AL_NO_ERROR);

				if (!has_low_pass_filter)
				{
					is_succeeded = false;
					common->Printf("%s: No low-pass filter\n", "OpenAL");
				}
			}

			al_efx_direct_filter = filters[0];
			al_efx_send_filter = filters[1];
		}
		else
		{
			is_succeeded = false;
			common->Printf("%s: Failed to create a filter\n", "OpenAL");
		}
	}

	if (is_succeeded)
	{
		al_efx_initialize_mb_to_gain_lut();
		al_efx_set_reverb_defaults();
	}

	if (is_succeeded)
	{
		al_efx_available = true;

		common->Printf("%s: Version: %d.%d\n", "OpenAL", major_version, minor_version);
		common->Printf("%s: Max sends: %d\n", "OpenAL", max_sends);

		common->Printf(
			"%s: Reverb effect type: %s\n",
			"OpenAL",
			al_efx_eax_reverb ? "EAX" : "standard");

		common->Printf("%s: EFX initialized\n", "OpenAL");
	}
	else
	{
		if (al_efx_symbols.alDeleteAuxiliaryEffectSlots != NULL)
		{
			al_efx_symbols.alDeleteAuxiliaryEffectSlots(1, &al_efx_effect_slot);
		}

		if (al_efx_symbols.alDeleteEffects != NULL)
		{
			al_efx_symbols.alDeleteEffects(1, &al_efx_effect);
		}

		if (al_efx_symbols.alDeleteFilters != NULL)
		{
			al_efx_symbols.alDeleteFilters(1, &al_efx_direct_filter);
			al_efx_symbols.alDeleteFilters(1, &al_efx_send_filter);
		}

		common->Printf("%s: EFX failed\n", "OpenAL");
	}

	return al_efx_available;
}

bool idSoundSystemLocal::al_efx_detect()
{
	ALint context_attributes[] =
	{
		ALC_MAX_AUXILIARY_SENDS, 1,
		0
	};

	ALCdevice* const device = alcOpenDevice(NULL);
	ALCcontext* const context = alcCreateContext(device, context_attributes);
	alcMakeContextCurrent(context);

	const bool has_extension = (alcIsExtensionPresent(
		device,
		reinterpret_cast<ALubyte*>(const_cast<char*>(ALC_EXT_EFX_NAME))) == ALC_TRUE);

	ALint major_version = 0;
	alcGetIntegerv(device, ALC_EFX_MAJOR_VERSION, 1, &major_version);
	
	ALint max_sends = 0;
	alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &max_sends);

	AlEfxSymbols symbols = AlEfxSymbols();
	bool has_failed_symbol_name = false;

	try
	{
		al_efx_resolve_symbols(symbols);
	}
	catch (const char*)
	{
		has_failed_symbol_name = true;
	}

	bool has_effect_slot = false;

	if (symbols.alGenAuxiliaryEffectSlots != NULL &&
		symbols.alDeleteAuxiliaryEffectSlots != NULL &&
		symbols.alAuxiliaryEffectSloti != NULL &&
		symbols.alGetAuxiliaryEffectSloti != NULL)
	{
		ALuint effect_slot = AL_NONE;
		alGetError();
		symbols.alGenAuxiliaryEffectSlots(1, &effect_slot);
		has_effect_slot = (alGetError() == AL_NO_ERROR);

		if (has_effect_slot)
		{
			symbols.alDeleteAuxiliaryEffectSlots(1, &effect_slot);
		}
	}

	bool has_eax_reverb = false;
	bool has_std_reverb = false;

	if (symbols.alGenEffects != NULL &&
		symbols.alDeleteEffects != NULL &&
		symbols.alEffecti != NULL &&
		symbols.alEffectf != NULL &&
		symbols.alEffectfv != NULL)
	{
		ALuint effect = AL_NONE;
		alGetError();
		symbols.alGenEffects(1, &effect);

		if (alGetError() == AL_NO_ERROR)
		{
			symbols.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
			has_eax_reverb = (alGetError() == AL_NO_ERROR);

			symbols.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
			has_std_reverb = (alGetError() == AL_NO_ERROR);

			symbols.alDeleteEffects(1, &effect);
		}
	}

	bool has_low_pass_filter = false;

	if (symbols.alGenFilters != NULL &&
		symbols.alDeleteFilters != NULL &&
		symbols.alFilteri != NULL &&
		symbols.alFilterf != NULL)
	{
		ALuint filter = AL_NONE;
		alGetError();
		symbols.alGenFilters(1, &filter);

		if (alGetError() == AL_NO_ERROR)
		{
			symbols.alFilteri(filter, AL_FILTER_TYPE, AL_FILTER_LOWPASS);
			has_low_pass_filter = (alGetError() == AL_NO_ERROR);

			symbols.alDeleteFilters(1, &filter);
		}
	}

	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);

	return
		has_extension &&
		major_version > 0 &&
		max_sends > 0 &&
		!has_failed_symbol_name &&
		has_effect_slot &&
		(has_eax_reverb || has_std_reverb) &&
		has_low_pass_filter;
}
#endif

// IDT4-FEATURE-AUDIO-LIMITER
#ifndef IDT4_VANILLA
void idSoundSystemLocal::limiter_process(float* samples, int sample_count) const
{
	if (!s_limiter_cvar.GetBool())
	{
		return;
	}

	static const float min_sample = -32768.0F;
	static const float max_sample = +32767.0F;
	static const float max_amplitude = max_sample - min_sample;
	const float volume = dB2Scale(s_volume.GetFloat());
	const float threshold = max_amplitude * volume;
	float sample_min = 0.0F;
	float sample_max = 0.0F;
	SIMDProcessor->MinMax(sample_min, sample_max, samples, sample_count);
	const float amplitude = sample_max - sample_min;

	if (amplitude <= threshold)
	{
		return;
	}

	const float scale_factor = threshold / amplitude;
	SIMDProcessor->MulAssign16(samples, scale_factor, sample_count);
}
#endif
