# Create shared library
include_directories("${HarudioEngine_SOURCE_DIR}/Audio/Effect")

target_sources(${PROJECT_NAME} 
					PUBLIC
						"${CMAKE_CURRENT_LIST_DIR}/AdaptableConvolver.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AmbisonicPanner.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/BitCrusher.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Clamp.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Compactor.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/ComplexConvolver.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Convolver.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Degrader.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Delay.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Filter.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Gate.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/ImpulseResponseGenerator.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/IrBufferFiller.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/MatrixPanner.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Overdrive.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Panner.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/PositionalPanner.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Resampler.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SampleLevelEffect.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SimpleConvolver.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SingleAttributeEffect.hpp"
					PRIVATE
						"${CMAKE_CURRENT_LIST_DIR}/AmbisonicPanner.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/BitCrusher.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Clamp.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Compactor.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/ComplexConvolver.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Convolver.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Degrader.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Delay.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Filter.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Gate.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/ImpulseResponseGenerator.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Overdrive.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/PositionalPanner.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Resampler.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/SampleLevelEffect.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/SimpleConvolver.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/SingleAttributeEffect.cpp"
						)


SET(				HS	"${HS}" 
						"${CMAKE_CURRENT_LIST_DIR}/AdaptableConvolver.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/AmbisonicPanner.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/BitCrusher.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Clamp.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Compactor.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/ComplexConvolver.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Convolver.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Degrader.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Delay.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Filter.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Gate.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/ImpulseResponseGenerator.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/IrBufferFiller.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/MatrixPanner.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Overdrive.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Panner.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/PositionalPanner.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/Resampler.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SampleLevelEffect.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SimpleConvolver.hpp"
						"${CMAKE_CURRENT_LIST_DIR}/SingleAttributeEffect.hpp"
)
