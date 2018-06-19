#ifndef AMBISONICPANNER_HPP
#define AMBISONICPANNER_HPP
#include "Panner.hpp"

namespace Audio {

DEFINE_CLASS(AmbisonicPanner)
class AmbisonicPanner : public QuadPanner
{
private:
	// Raw input parameters
	float horizontalAngle;
	float elevationAngle;
	float distance;
	// Black magic variables
	/*
	float W; // S * 1/sqrt(2)
	float X; // S * cos(horizontalAngle)*cos(elevationAngle)
	float Y; // S * sin(horizontalAngle)*cos(elevationAngle)
	float Z; // S * sin(elevationAngle)
	*/
	// In this situation, S equals 1/distance
	// These "black magic variables" are used to evaluate these four:
	// Front Left = (sqrt(2) * W + X + Y)*sqrt(8)
	// Back Left = (sqrt(2) * W - X + Y)*sqrt(8)
	// Back Right = (sqrt(2) * W - X - Y)*sqrt(8)
	// Front Right = (sqrt(2) * W + X - Y)*sqrt(8)

	// In the matrix panner, the order isn't FL-BL-BR-FR
	// But FL-FR-BL-BR
	void recalculate();
protected:
	AmbisonicPanner(float horizontalAngle=0.0f, float elevationAngle=0.0f, float distance=1.0f);
public:
	static sAmbisonicPanner createAmbisonicPanner(float horizontalAngle=0.0f, float elevationAngle=0.0f, float distance=1.0f);
	float getHorizontalAngle() const;
	float getElevationAngle() const;
	float getDistance() const;
	void setHorizontalAngle(float setto);
	void setElevationAngle(float setto);
	void setDistance(float setto);
	void setAttributes(float horizontalAngle, float elevationAngle, float distance);
};

}
#endif // AMBISONICPANNER_HPP
