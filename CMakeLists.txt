cmake_minimum_required(VERSION 3.13.0)
project(harudio-engine)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE src)
add_subdirectory(src)

find_package(SDL2)
find_package(PkgConfig)

pkg_check_modules(SndFile REQUIRED IMPORTED_TARGET sndfile)
pkg_check_modules(OpenMPT REQUIRED IMPORTED_TARGET libopenmpt)
pkg_check_modules(Samplerate REQUIRED IMPORTED_TARGET samplerate)
pkg_check_modules(Fftw3 REQUIRED IMPORTED_TARGET fftw3 fftw3f)

target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2
        PkgConfig::SndFile
        PkgConfig::OpenMPT
        PkgConfig::Samplerate
        PkgConfig::Fftw3)
