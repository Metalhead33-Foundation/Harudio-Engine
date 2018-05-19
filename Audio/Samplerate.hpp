#ifndef SAMPLERATE_HPP
#define SAMPLERATE_HPP
#include <samplerate.h>
#include "../Io/Global.hpp"
namespace Audio {

DEFINE_CLASS(Samplerate)
class Samplerate {
	SRC_STATE *m_state;

	int m_error;

  public:
	Samplerate( int converter_type, int channels );
	~Samplerate( );

	int process( SRC_DATA *data );
	int reset( );

	int setRatio( double new_ratio );

  public:
	int lastError( );
};

}
#endif // SAMPLERATE_HPP
