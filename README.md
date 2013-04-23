sfconvert
=====================

Utilities for SoundFont files.

- compress sound font files with ogg vorbis for use with [MuseScore](http://musescore.org)
- convert to "C" for embedding

Usage Example:

This compresses the Fluid sound font from 148 MBytes to 20 MBytes.

    sfconvert -z FluidR3.SF2 mops.sf3

**The compressed sound font has the major version number 3. Its non standard
and can be used only (so far) by [MuseScore](http://musescore.org).** 


TODO:
Stereo samples are compressed as two single streams instead of compressing
them as stereo ogg vorbis streams. This may be less optimal.

