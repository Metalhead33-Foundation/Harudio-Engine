#include "AmbisonicPanner.hpp"
#include <cmath>
#include <cstdint>
namespace Audio {

void AmbisonicPanner::recalculate()
{
	const float S = 1.0f/distance;
	const float W = S * (1/sqrtf(2.0f));
	const float X = S * cosf(horizontalAngle) * cosf(elevationAngle);
	const float Y = S * sinf(horizontalAngle) * cosf(elevationAngle);

	const float frontLeft = (sqrtf(2.0f) * W + X + Y) * sqrtf(8.0f);
	const float backLeft = (sqrtf(2.0f) * W - X + Y) * sqrtf(8.0f);
	const float backRight = (sqrtf(2.0f) * W - X - Y) * sqrtf(8.0f);
	const float frontRight = (sqrtf(2.0f) * W + X - Y) * sqrtf(8.0f);

	volumeLevel[0] = frontLeft;
	volumeLevel[1] = frontRight;
	volumeLevel[2] = backLeft;
	volumeLevel[3] = backRight;

}
sAmbisonicPanner AmbisonicPanner::createAmbisonicPanner(float horizontalAngle,
														float elevationAngle,
														float distance)
{
	return sAmbisonicPanner(new AmbisonicPanner(horizontalAngle,elevationAngle,distance));
}

AmbisonicPanner::AmbisonicPanner(float horizontalAngle, float elevationAngle, float distance)
{
	this->horizontalAngle = horizontalAngle;
	this->elevationAngle = elevationAngle;
	this->distance = distance;
	recalculate();
}
float AmbisonicPanner::getHorizontalAngle() const
{
	return horizontalAngle;
}
float AmbisonicPanner::getElevationAngle() const
{
	return elevationAngle;
}
float AmbisonicPanner::getDistance() const
{
	return distance;
}
void AmbisonicPanner::setHorizontalAngle(float setto)
{
	if(horizontalAngle != setto)
	{
		horizontalAngle = setto;
		recalculate();
	}
}
void AmbisonicPanner::setElevationAngle(float setto)
{
	if(elevationAngle != setto)
	{
		elevationAngle = setto;
		recalculate();
	}
}
void AmbisonicPanner::setDistance(float setto)
{
	if(distance != setto)
	{
		distance = setto;
		recalculate();
	}
}
void AmbisonicPanner::setAttributes(float horizontalAngle, float elevationAngle, float distance)
{
	if(this->horizontalAngle != horizontalAngle && this->elevationAngle != elevationAngle
			&& this->distance != distance)
	{
		this->horizontalAngle = horizontalAngle;
		this->elevationAngle = elevationAngle;
		this->distance = distance;
		recalculate();
	}
}

}
