#ifndef AUDIOEFFECT_HPP
#define AUDIOEFFECT_HPP
#include <Global/Global.hpp>

namespace Audio {
	DEFINE_CLASS( Effect )
	class Effect {
	  public:
		virtual ~Effect( ) = default;
		virtual void doEffect(float& target) = 0;
	};

} // namespace Audio

#endif // AUDIOBUFFER_HPP
