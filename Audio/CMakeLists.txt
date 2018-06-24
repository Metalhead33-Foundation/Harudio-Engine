# Create shared library
include_directories("${HarudioEngine_SOURCE_DIR}/Audio")

target_sources(${PROJECT_NAME}
					PUBLIC
						"${CMAKE_CURRENT_LIST_DIR}/AudioContext.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioMixer.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioSource.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioBuffer.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioEffect.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioPluginPlayable.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Samplerate.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioPlayable.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AuxiliaryEffectSlot.hpp"
					PRIVATE
						"${CMAKE_CURRENT_LIST_DIR}/AudioBuffer.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioPluginPlayable.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Samplerate.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioPlayable.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/AuxiliaryEffectSlot.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioContext.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioMixer.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioSource.cpp"
						)

add_subdirectory("Effect")
add_subdirectory("FFTConvolver")

SET(				HS	"${HS}" 
						"${CMAKE_CURRENT_LIST_DIR}/AudioContext.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioMixer.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioSource.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioBuffer.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioEffect.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioPluginPlayable.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Samplerate.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AudioPlayable.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AuxiliaryEffectSlot.hpp"
)
