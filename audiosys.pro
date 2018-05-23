TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(release, debug|release): LIBS += -lsndfile -lsamplerate -lportaudio -lportaudiocpp
CONFIG(debug, debug|release): LIBS += -lsndfile -lsamplerate -lportaudio -lportaudiocpp
SOURCES += main.cpp \
    Io/StdStream.cpp \
    Io/SoundFile.cpp \
    Audio/Samplerate.cpp \
    Audio/AudioContext.cpp \
    Audio/AudioPlayable.cpp \
    Audio/AudioMixer.cpp \
    Audio/AuxiliaryEffectSlot.cpp \
    Audio/Effect/Resampler.cpp \
    Audio/AudioSource.cpp \
    Audio/AudioBuffer.cpp

HEADERS += \
    Io/StdStream.hpp \
    Io/FIOSys.hpp \
    Io/FIO.hpp \
    Io/SoundFile.hpp \
    Io/sndfile.hh \
    Io/Global.hpp \
    Audio/Samplerate.hpp \
    Audio/AudioContext.hpp \
    Audio/AudioPlayable.hpp \
    Audio/AudioMixer.hpp \
    Audio/AuxiliaryEffectSlot.hpp \
    Audio/AudioEffect.hpp \
    Audio/Effect/Resampler.hpp \
    Audio/Effect/Panner.hpp \
    Audio/Effect/DimensionalPanner.hpp \
    Audio/Effect/MatrixPanner.hpp \
    Audio/AudioSource.hpp \
    Audio/AudioSource.hpp \
    Audio/AudioBuffer.hpp
