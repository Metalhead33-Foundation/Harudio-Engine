#ifndef ADAPTABLECONVOLVER_HPP
#define ADAPTABLECONVOLVER_HPP
#include "../../Io/Global.hpp"
#include <vector>
namespace Audio {
namespace FX {

DEFINE_CLASS(ImpulseResponseGenerator)
DEFINE_CLASS(AdaptableConvolver)
class AdaptableConvolver
{
friend class ImpulseResponseGenerator;
protected:
	virtual void adapt(const std::vector<float>& IR, int channelId) = 0;
public:
	virtual ~AdaptableConvolver() = default;
};

}
}
#endif // ADAPTABLECONVOLVER_HPP
