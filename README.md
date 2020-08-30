# sf3convert

Utilities for converting Soundfont files from version 2 to version 3 and back from version 3 to version 2.

### Sf3 format

The sf3 format stores compressed data (OGG vorbis files) instead of raw data (WAVE) in a soundfont. There is thus a **loss in quality** but the resulting files are lighter and more prone to be **embedded**. This format has been primarily designed and used by [MuseScore](http://musescore.org) and is now supported by other projects:

* [Calf-Fluidsynth](http://calf-studio-gear.org/)
* [Carla](http://kxstudio.linuxaudio.org/Applications:Carla)
* [LMMS](https://lmms.io)
* [Polyphone](https://www.polyphone-soundfonts.com)
* [Qsynth](https://qsynth.sourceforge.io)
* [Qtractor](https://qtractor.sourceforge.io)

**The compressed soundfont has the major version number 3. It is non standard and no specifications have been written yet**


### Compilation

#### Dependencies

* Qt >= 5.6
* libsdnfile
* libogg
* libvorbis
* libvorbisenc
* libvorbisfile

```
$ make release
```

### Usage Example:

This compresses the Fluid soundfont from 148 MBytes to 20 MBytes.

    sf3convert -z FluidR3.SF2 compressed_soundfont.sf3

This uncompresses a soundfont

    sf3convert -y compressed_soundfont.sf3 FluidR3.sf2