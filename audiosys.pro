TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

debug {
CONFIG += -O0
}

CONFIG(release, debug|release): LIBS += -lsndfile -lsamplerate -lportaudio -lportaudiocpp
CONFIG(debug, debug|release): LIBS += -lsndfile -lsamplerate -lportaudio -lportaudiocpp

SUBDIRS += \
    audiosys.pro

DISTFILES += \
    Audio/FFTConvolver/README.md \
    Audio/FFTConvolver/COPYING.txt

HEADERS += \
    Audio/Effect/BitCrusher.hpp \
    Audio/Effect/Clamp.hpp \
    Audio/Effect/Convolver.hpp \
    Audio/Effect/Degrader.hpp \
    Audio/Effect/DimensionalPanner.hpp \
    Audio/Effect/Gate.hpp \
    Audio/Effect/Overdrive.hpp \
    Audio/Effect/Panner.hpp \
    Audio/Effect/Resampler.hpp \
    Audio/Effect/SampleLevelEffect.hpp \
    Audio/Effect/SingleAttributeEffect.hpp \
    Audio/FFTConvolver/AudioFFT.h \
    Audio/FFTConvolver/FFTConvolver.h \
    Audio/FFTConvolver/TwoStageFFTConvolver.h \
    Audio/FFTConvolver/Utilities.h \
    Audio/AudioBuffer.hpp \
    Audio/AudioContext.hpp \
    Audio/AudioEffect.hpp \
    Audio/AudioMixer.hpp \
    Audio/AudioPlayable.hpp \
    Audio/AudioPluginPlayable.hpp \
    Audio/AudioSource.hpp \
    Audio/AuxiliaryEffectSlot.hpp \
    Audio/Samplerate.hpp \
    Io/FIO.hpp \
    Io/FIOSys.hpp \
    Io/Global.hpp \
    Io/sndfile.hh \
    Io/SoundFile.hpp \
    Io/StdStream.hpp \
    Sound/SoundSource.hpp \
    Sound/SoundStreamer.hpp \
    Audio/Effect/TwoStageConvolver.hpp \
    Audio/Effect/IrBufferFiller.hpp \
    Audio/Effect/LowpassFilter.hpp

SOURCES += \
    Audio/Effect/BitCrusher.cpp \
    Audio/Effect/Clamp.cpp \
    Audio/Effect/Convolver.cpp \
    Audio/Effect/Degrader.cpp \
    Audio/Effect/Gate.cpp \
    Audio/Effect/Overdrive.cpp \
    Audio/Effect/Resampler.cpp \
    Audio/Effect/SampleLevelEffect.cpp \
    Audio/Effect/SingleAttributeEffect.cpp \
    Audio/FFTConvolver/AudioFFT.cpp \
    Audio/FFTConvolver/FFTConvolver.cpp \
    Audio/FFTConvolver/TwoStageFFTConvolver.cpp \
    Audio/FFTConvolver/Utilities.cpp \
    Audio/AudioBuffer.cpp \
    Audio/AudioContext.cpp \
    Audio/AudioMixer.cpp \
    Audio/AudioPlayable.cpp \
    Audio/AudioPluginPlayable.cpp \
    Audio/AudioSource.cpp \
    Audio/AuxiliaryEffectSlot.cpp \
    Audio/Samplerate.cpp \
    Io/SoundFile.cpp \
    Io/StdStream.cpp \
    Sound/SoundSource.cpp \
    Sound/SoundStreamer.cpp \
    main.cpp \
    Audio/Effect/TwoStageConvolver.cpp \
    Audio/Effect/LowpassFilter.cpp
