#include "PositionalPanner.hpp"
#include <glm/geometric.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <cmath>

namespace Audio {

void PositionalPanner::recalculatePos()
{
	const glm::vec3 diff = direction - source;
	// const glm::vec2 horizontal(diff.x,diff.y);
	// const glm::vec2 elevation(diff.y,diff.z);
	setAttributes(atan2f(-1.0f*diff.x,-1.0f*diff.z),
				  atan2f(diff.y,sqrtf(diff.x*diff.x + diff.z*diff.z)),
				  glm::distance(source,direction)*attenuation);
	/*setAttributes(glm::orientedAngle(glm::vec2(0,0),horizontal),
				  glm::orientedAngle(glm::vec2(0,0),elevation),
				  glm::distance(source,direction)*attenuation);*/
}
PositionalPanner::PositionalPanner()
{
	this->source = glm::vec3(0.0f,0.0f,0.0f);
	this->direction = glm::vec3(0.0f,0.0f,0.0f);
	recalculatePos();
}
PositionalPanner::PositionalPanner(const glm::vec3& source, const glm::vec3& direction, float attenuation)
{
	this->source = source;
	this->direction = direction;
	this->attenuation = attenuation;
	recalculatePos();
}
sPositionalPanner PositionalPanner::createPositionPanner()
{
	return sPositionalPanner(new PositionalPanner());
}
sPositionalPanner PositionalPanner::createPositionPanner(const glm::vec3& source, const glm::vec3& direction, float attenuation)
{
	return sPositionalPanner(new PositionalPanner(source,direction,attenuation));
}
const glm::vec3& PositionalPanner::getSource() const
{
	return source;
}
const glm::vec3& PositionalPanner::getDirection() const
{
	return direction;
}
void PositionalPanner::setSource(const glm::vec3& setto)
{
	if(source != setto)
	{
		this->source = setto;
		recalculatePos();
	}
}
void PositionalPanner::setDirection(const glm::vec3& setto)
{
	if(direction != setto)
	{
		this->direction = setto;
		recalculatePos();
	}
}
void PositionalPanner::setPositions(const glm::vec3& source, const glm::vec3& direction)
{
	if(this->direction != direction && this->source != source)
	{
		this->direction = direction;
		this->source = source;
		recalculatePos();
	}
}
float PositionalPanner::getAttenuation() const
{
	return attenuation;
}
void PositionalPanner::setAttenuation(float attenuation)
{
	if(this->attenuation != attenuation)
	{
		this->attenuation = attenuation;
		recalculatePos();
	}
}

}
