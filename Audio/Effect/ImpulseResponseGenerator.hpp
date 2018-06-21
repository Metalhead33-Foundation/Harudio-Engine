#ifndef IRGENERATOR_HPP
#define IRGENERATOR_HPP
#include "AdaptableConvolver.hpp"
namespace Audio {
namespace FX {

class ImpulseResponseGenerator
{
private:
	int channelId;
	wAdaptableConvolver adapted;
protected:
	void adapt(const std::vector<float>& IR);
	ImpulseResponseGenerator(int channelId=0, const sAdaptableConvolver setto=nullptr);
public:
	virtual ~ImpulseResponseGenerator() = default;
	sAdaptableConvolver getAdapted() const;
	void setAdapted(const sAdaptableConvolver setto);
	int getChannelId() const;
	void setChannelId(int setto);
};

}
}
#endif // IRGENERATOR_HPP
