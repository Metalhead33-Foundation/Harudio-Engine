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
    Util/AudioMixer.cpp \
    Sound/SoundBuffer.cpp \
    Wrappers/MhResampler.cpp \
    Wrappers/MhSoundfileWrapper.cpp \
    Sound/SoundModulePlayer.cpp \
    Wrappers/MhModuleRenderer.cpp \
    Sound/SoundSinewave.cpp \
    Driver/SDL.cpp \
    Sound/SoundStreamer.cpp \
    Abstract/AudioSeekable.cpp \
    Sound/SoundSource.cpp

HEADERS += \
    Global/FIO.hpp \
    Global/FIOSys.hpp \
    Global/Global.hpp \
    Global/StdStream.hpp \
    Global/FftwMallocator.hpp \
    Abstract/AudioPacket.hpp \
    Abstract/AudioPlayable.hpp \
    Abstract/AudioMismatchError.hpp \
    Util/AudioMixer.hpp \
    Abstract/AudioBuffer.hpp \
    Sound/SoundBuffer.hpp \
    Wrappers/MhResampler.hpp \
    Wrappers/MhSoundfileWrapper.hpp \
    Sound/SoundModulePlayer.hpp \
    Wrappers/MhModuleRenderer.hpp \
    Sound/SoundSinewave.hpp \
    Driver/SDL.hpp \
    Sound/SoundStreamer.hpp \
    Abstract/AudioSeekable.hpp \
    Sound/SoundSource.hpp
