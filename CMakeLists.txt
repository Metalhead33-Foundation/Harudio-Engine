cmake_minimum_required(VERSION 3.11)

project(HarudioEngine)

  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 17)
  endif ()
  
  MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    FOREACH(HEADER ${${HEADER_LIST}})
        STRING(REGEX MATCH "(.\\\*)\\\[/\\\]" DIR ${HEADER})
        INSTALL(FILES ${HEADER} DESTINATION include/${DIR})
    ENDFOREACH(HEADER)

ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
SET(HS "")
  
find_package(PortAudio REQUIRED)
find_package(SndFile REQUIRED)
find_package(Libsamplerate REQUIRED)


add_library(${PROJECT_NAME} SHARED)

add_subdirectory("Audio")
add_subdirectory("Sound")
add_subdirectory("Io")

target_link_libraries(${PROJECT_NAME}
    ${PORTAUDIO_LIBRARIES}
    ${LIBSAMPLERATE_LIBRARIES}
    ${SNDFILE_LIBRARY}
    )

# target_link_libraries(toDo toDoCore)


# Install library
install(
	TARGETS ${PROJECT_NAME} 
	LIBRARY DESTINATION lib
)
INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*")
# install(DIRECTORY "${HarudioEngine_SOURCE_DIR}" DESTINATION "include/${PROJECT_NAME}")

# Include header files
#include_directories("include")
#include_directories("include/Filetypes")

