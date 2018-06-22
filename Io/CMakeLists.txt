# Create shared library
include_directories("${HarudioEngine_SOURCE_DIR}/Io")

target_sources(${PROJECT_NAME}
					PUBLIC
						"${CMAKE_CURRENT_LIST_DIR}/FIO.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/FIOSys.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/fsqrt.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Global.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/sndfile.hh"
						"${CMAKE_CURRENT_LIST_DIR}/SoundFile.hpp"
					PRIVATE
						"${CMAKE_CURRENT_LIST_DIR}/SoundFile.cpp"
						)
						
SET(				HS	"${HS}" 
						"${CMAKE_CURRENT_LIST_DIR}/FIO.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/FIOSys.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/fsqrt.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Global.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/sndfile.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SoundFile.hpp"
)


# CMakeLists.txt  FIO.hpp  FIOSys.hpp  fsqrt.hpp  Global.hpp  sndfile.hh  SoundFile.cpp  SoundFile.hpp  StdStream.cpp  StdStream.hpp
