The **Harudio Engine** (_[Japanese](https://en.wikipedia.org/wiki/Japanese_language "wikipedia:Japanese language"):_ ハルディオ・エンジン) is an in-development audio [API](https://en.wikipedia.org/wiki/Application_programming_interface "wikipedia:Application programming interface") intended to be used as part of the [Haruka Engine](https://ways-of-darkness.sonck.nl/Haruka_Engine "Haruka Engine"), which is intended to used in the [future Ways of Darkness game](https://ways-of-darkness.sonck.nl/Ways_of_Darkness_(3D_project) "Ways of Darkness (3D project)").

## Name

The name of the engine is a portmanteau of the Japanese female given name _["Haruka"](https://en.wikipedia.org/wiki/Haruka_(given_name) "wikipedia:Haruka (given name)")_ _(after the [Haruka Engine](https://ways-of-darkness.sonck.nl/Haruka_Engine "Haruka Engine"))_ and the word _"audio"_. The engine was formerly called the **Sabaton Engine** \- after the Swedish power\-metal band [Sabaton](https://en.wikipedia.org/wiki/Sabaton_(band) "wikipedia:Sabaton (band)") \- until the 14th of June\, 2018\, when the management of the band confirmed that it is illegal to name a piece of software after the band\.

## History

[Zsolt Tóth](https://ways-of-darkness.sonck.nl/Zsolt_T%C3%B3th "Zsolt Tóth") originally intended to use [OpenAL](https://en.wikipedia.org/wiki/OpenAL "wikipedia:OpenAL") within the [Haruka Engine](https://ways-of-darkness.sonck.nl/Haruka_Engine "Haruka Engine"), until the May of 2018, when he decided to begin the development of Harudio Engine.

## Features

As the game engine isn't released yet, only intended features and ambitions can be listed:

* Built on top of either [PortAudio](https://en.wikipedia.org/wiki/PortAudio "wikipedia:PortAudio") or [SDL](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer "wikipedia:Simple DirectMedia Layer"), which means that in theory, every platform that runs either of the two is supported. Nevertheless, the intended platforms are:
    * [GNU Linux](https://en.wikipedia.org/wiki/GNU_Linux "wikipedia:GNU Linux") and [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows "wikipedia:Microsoft Windows") on PC
    * [Android](https://en.wikipedia.org/wiki/Android_(operating_system) "wikipedia:Android (operating system)")
* Supported sound formats: [OGG](https://en.wikipedia.org/wiki/Vorbis "wikipedia:Vorbis") and [WAV](https://en.wikipedia.org/wiki/WAV "wikipedia:WAV") via [libsndfile](https://en.wikipedia.org/wiki/libsndfile "wikipedia:libsndfile")
* Presence of mixers _(for mixing multiple sources into one output)_, auxiliary effect slots _(for assigning effects to sources)_, resamplers and panners.
* Several built-in effects:
    * Distortion/Overdrive
    * Audio degrading
* An interface tailed for the support of custom effects and [Impulse response recordings](https://en.wikipedia.org/wiki/Impulse_response "wikipedia:Impulse response")
* An interface to provide I/O operators for loading audio files.
