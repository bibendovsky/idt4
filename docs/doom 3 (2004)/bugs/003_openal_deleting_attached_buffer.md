Name
====
OpenAL Deleting attached buffer

Prerequisites
=============
- Using OpenAL.
- Level transition.

How to reproduce in base game
=============================
1) `set com_purgeAll 1`
2) `map game/mars_city2`
3) Wait for radio transmission.
4) `map game/mars_city1`

How to reproduce in ROE
=======================
1) `set com_purgeAll 1`
2) `map game/erebus6`
3) `teleport func_static_5381`
4) Look to the right and click to exit the level.
5) If next level loaded without an error try `map game/erebus6` one more time.

Symptom
=======
The game stops with an error message in the console "idSoundCache: error unloading data from OpenAL hardware buffer".

Reasons
=======
- Sound cache manager does not take into account the buffer can not be purged while it is attached to a source.

Solution
========
In the method `idSoundSample::PurgeSoundSample` (snd_cache.cpp) call idSoundChannel::ALStop for all sources using this AL buffer.
