Name
====
OpenAL Deleting attached buffer

Prerequisites
=============
- Using OpenAL.
- Level transition.

Symptom
=======
An error message may occur in the console "idSoundCache: error unloading data from OpenAL hardware buffer".

Reasons
=======
- Sound cache manager does not take into account the buffer can not be purged while it attached to any source.

Solution
========
In the method `idSoundSample::PurgeSoundSample` (snd_cache.cpp) call idSoundChannel::ALStop for all channels using this AL buffer.
