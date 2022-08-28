Name
====
Video RAM size detection

Symptom
=======
The engine could not detect the size properly in some configurations.

Reasons
=======
1) Multiple video adapters. The engine checks only for the first adapter.

Solution
========
1) Detect the primary adapter ID with `EnumDisplayDevices`. Use this ID in WBEM to find out the information about the adapter.
