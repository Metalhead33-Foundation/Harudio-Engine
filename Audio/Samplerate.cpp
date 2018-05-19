#include "Samplerate.hpp"
namespace Audio {

Samplerate::Samplerate( int converter_type, int channels ) {
	m_state = src_new( converter_type, channels, &m_error );
}

Samplerate::~Samplerate( ) { m_state = src_delete( m_state ); }

int Samplerate::process( SRC_DATA *data ) {
	return m_error = src_process( m_state, data );
}

int Samplerate::reset( ) { return m_error = src_reset( m_state ); }

int Samplerate::setRatio( double new_ratio ) {
	return m_error = src_set_ratio( m_state, new_ratio );
}

int Samplerate::lastError( ) { return m_error; }
}
