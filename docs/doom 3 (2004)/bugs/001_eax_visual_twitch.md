Name
====
EAX Visual Twitch

Prerequisite
============
Enabled EAX.

Symptom
=======
Very short but noticeable shake of screen in some places.

Reason
======
Incorrect caching of amplitude data for OpenAL.

Solution
========
Don't update amplitude data (`amplitudeData`) and don't free non-cache data (`nonCacheData`) in `idSoundSample::Load` (snd_cache.cpp).

References
==========
- https://www.pcgamingwiki.com/wiki/Doom_3#Visual_twitch_bug_with_OpenAL.2FEAX
