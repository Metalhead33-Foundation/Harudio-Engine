project(${PROJECT_NAME} VERSION 0.1)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(SDL2)
find_package(PkgConfig)

pkg_check_modules(SndFile REQUIRED IMPORTED_TARGET sndfile)
pkg_check_modules(OpenMPT REQUIRED IMPORTED_TARGET libopenmpt)
pkg_check_modules(Samplerate REQUIRED IMPORTED_TARGET samplerate)
pkg_check_modules(Fftw3 REQUIRED IMPORTED_TARGET fftw3f)

set(CMAKE_DEBUG_POSTFIX d)

add_library(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)

#set_target_properties( ${PROJECT_NAME} PROPERTIES EXPORT_NAME HarudioEngine )

add_subdirectory(source)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source)

target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2
        PkgConfig::SndFile
        PkgConfig::OpenMPT
        PkgConfig::Samplerate
        PkgConfig::Fftw3)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake VERSION
        ${PROJECT_VERSION} COMPATIBILITY SameMajorVersion)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}Targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        NAMESPACE HarudioEngine::)

export(TARGETS ${PROJECT_NAME} NAMESPACE HarudioEngine:: FILE ${PROJECT_NAME}Targets.cmake)
export(PACKAGE ${PROJECT_NAME})

add_library(HarudioEngine::HarudioEngine ALIAS ${PROJECT_NAME})