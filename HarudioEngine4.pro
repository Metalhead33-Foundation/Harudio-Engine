TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lfftw3 -lfftw3f -lsndfile -lsamplerate -lopenmpt
LIBS += -D_REENTRANT -I/usr/include/SDL2 -lSDL2

SOURCES += \
        main.cpp \
    Global/StdStream.cpp \
    Abstract/AudioMismatchError.cpp \
    Abstract/AudioProvider.cpp \
    Util/AudioMixer.cpp \
    Sound/SoundBuffer.cpp \
    Wrappers/MhResampler.cpp \
    Wrappers/MhSoundfileWrapper.cpp \
    Sound/SoundRingbuffer.cpp \
    Sound/SoundModulePlayer.cpp \
    Wrappers/MhModuleRenderer.cpp \
    Sound/SoundSinewave.cpp \
    Driver/SDL.cpp \
    Sound/SoundStreamer.cpp

HEADERS += \
    Global/FIO.hpp \
    Global/FIOSys.hpp \
    Global/Global.hpp \
    Global/StdStream.hpp \
    Global/FftwMallocator.hpp \
    Abstract/AudioPacket.hpp \
    Abstract/AudioPlayable.hpp \
    Abstract/AudioMismatchError.hpp \
    Abstract/AudioProvider.hpp \
    Util/AudioMixer.hpp \
    Abstract/AudioBuffer.hpp \
    Sound/SoundBuffer.hpp \
    Wrappers/MhResampler.hpp \
    Wrappers/MhSoundfileWrapper.hpp \
    Sound/SoundRingbuffer.hpp \
    Sound/SoundModulePlayer.hpp \
    Wrappers/MhModuleRenderer.hpp \
    Sound/SoundSinewave.hpp \
    Driver/SDL.hpp \
    Sound/SoundStreamer.hpp
