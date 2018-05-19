TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(release, debug|release): LIBS += -lsndfile -lsamplerate -lportaudio -lportaudiocpp
CONFIG(debug, debug|release): LIBS += -lsndfile -lsamplerate -lportaudio -lportaudiocpp
SOURCES += main.cpp \
    Io/StdStream.cpp \
    Io/SoundFile.cpp \
    Audio/Samplerate.cpp

HEADERS += \
    Io/StdStream.hpp \
    Io/FIOSys.hpp \
    Io/FIO.hpp \
    Io/SoundFile.hpp \
    Io/sndfile.hh \
    Io/Global.hpp \
    Audio/Samplerate.hpp
