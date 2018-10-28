TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsndfile -lsamplerate

SUBDIRS += \
    harudio-engine.pro

DISTFILES += \
    PLACEHOLDER.MD

HEADERS += \
    Audio/AudioImporter.hpp \
    harudio-headers/Audio/FX/AdaptableConvolver.hpp \
    harudio-headers/Audio/FX/ComplexConvolver.hpp \
    harudio-headers/Audio/FX/MultipleAttributeEffect.hpp \
    harudio-headers/Audio/FX/Panner.hpp \
    harudio-headers/Audio/FX/Resampler.hpp \
    harudio-headers/Audio/FX/SimpleConvolver.hpp \
    harudio-headers/Audio/FX/SingleAttributeEffect.hpp \
    harudio-headers/Audio/AudioAuxiliaryEffectSlot.hpp \
    harudio-headers/Audio/AudioBuffer.hpp \
    harudio-headers/Audio/AudioEffect.hpp \
    harudio-headers/Audio/AudioImporter.hpp \
    harudio-headers/Audio/AudioMixer.hpp \
    harudio-headers/Audio/AudioPlayable.hpp \
    harudio-headers/Audio/AudioPluginPlayable.hpp \
    harudio-headers/Audio/AudioSource.hpp \
    harudio-headers/Io/FIO.hpp \
    harudio-headers/Io/FIOSys.hpp \
    harudio-headers/Io/Global.hpp \
    harudio-headers/Io/PortableIterator.hpp \
    harudio-headers/Io/StatefulIterator.hpp \
    harudio-headers/Sound/SoundSource.hpp \
    harudio-headers/Sound/SoundStreamer.hpp \
    harudio-headers/AudioSystem.hpp \
    Sound/sndfile.hh \
    Sound/SoundFile.hpp \
    Audio/AudioMixer.hpp \
    Audio/AudioBuffer.hpp

SOURCES += \
    Audio/AudioImporter.cpp \
    Sound/SoundFile.cpp \
    Audio/AudioMixer.cpp \
    Audio/AudioBuffer.cpp
