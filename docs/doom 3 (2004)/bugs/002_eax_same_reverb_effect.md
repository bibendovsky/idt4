Name
====
EAX Same Reverb Effect

Prerequisites
=============
- Enabled EAX.
- Official add-on "Resurrection Of Evil".

Symptom
=======
The reverb effect sounding same in different zones of a level.

Reasons
=======
- Missing parameter `air absorption hf` in EFX files (efxs/*.efx).
- Uninitialized reverb properties.

Solution
========
Initialize reverb properties with default values when reading them from EFX file in method `idEFXFile::ReadEffect` (snd_efxfile.cpp).

References
==========
- https://www.pcgamingwiki.com/wiki/Doom_3#Incorrect_EAX_effect_in_Doom3:_Ressurection_of_evil_with_OpenAL.2FEAX
