#include "ImpulseResponseGenerator.hpp"
namespace Audio {
namespace FX {

ImpulseResponseGenerator::ImpulseResponseGenerator(int channelId, const sAdaptableConvolver setto)
	: channelId(channelId), adapted(setto)
{

}
sAdaptableConvolver ImpulseResponseGenerator::getAdapted() const
{
	if(adapted.expired()) return nullptr;
	else return adapted.lock();
}
void ImpulseResponseGenerator::setAdapted(const sAdaptableConvolver setto)
{
	adapted = setto;
}
void ImpulseResponseGenerator::adapt(const std::vector<float>& IR)
{
	const sAdaptableConvolver adapted = getAdapted();
	if(adapted) adapted->adapt(IR,channelId);
}
int ImpulseResponseGenerator::getChannelId() const
{
	return channelId;
}
void ImpulseResponseGenerator::setChannelId(int setto)
{
	channelId = setto;
}

}
}
