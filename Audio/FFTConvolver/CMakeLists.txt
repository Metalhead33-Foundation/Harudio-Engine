# Create shared library
include_directories("${HarudioEngine_SOURCE_DIR}/Audio/FFTConvolver")

target_sources(${PROJECT_NAME}
					PUBLIC
						"${CMAKE_CURRENT_LIST_DIR}/AudioFFT.h"
						"${CMAKE_CURRENT_LIST_DIR}/FFTConvolver.h"
						"${CMAKE_CURRENT_LIST_DIR}/TwoStageFFTConvolver.h"
						"${CMAKE_CURRENT_LIST_DIR}/Utilities.h"
					PRIVATE
						"${CMAKE_CURRENT_LIST_DIR}/AudioFFT.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/FFTConvolver.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/TwoStageFFTConvolver.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Utilities.cpp"
						)


SET(				HS	"${HS}" 
						"${CMAKE_CURRENT_LIST_DIR}/AudioFFT.h"
						"${CMAKE_CURRENT_LIST_DIR}/FFTConvolver.h"
						"${CMAKE_CURRENT_LIST_DIR}/TwoStageFFTConvolver.h"
						"${CMAKE_CURRENT_LIST_DIR}/Utilities.h"
)
