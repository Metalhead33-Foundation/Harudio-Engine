# Create shared library
include_directories("${HarudioEngine_SOURCE_DIR}/Sound")

target_sources(${PROJECT_NAME}
					PUBLIC
						"${CMAKE_CURRENT_LIST_DIR}/SongLibrary.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SoundSource.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SoundStreamer.hpp"
					PRIVATE
						"${CMAKE_CURRENT_LIST_DIR}/SongLibrary.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/SoundSource.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/SoundStreamer.cpp"
						)

SET(				HS	"${HS}" 
						"${CMAKE_CURRENT_LIST_DIR}/SongLibrary.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SoundSource.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SoundStreamer.hpp"
)
