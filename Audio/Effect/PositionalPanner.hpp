#ifndef POSITIONALPANNER_HPP
#define POSITIONALPANNER_HPP
#include "AmbisonicPanner.hpp"
#include <glm/vec3.hpp>
namespace Audio {

DEFINE_CLASS(PositionalPanner)
class PositionalPanner : public AmbisonicPanner
{
private:
	glm::vec3 source; // Where is the sound coming from?
	glm::vec3 direction; // Where is the listener?
	float attenuation;
	void recalculatePos();
protected:
	PositionalPanner();
	PositionalPanner(const glm::vec3& source, const glm::vec3& direction, float attenuation=1.0f);
public:
	static sPositionalPanner createPositionPanner();
	static sPositionalPanner createPositionPanner(const glm::vec3 &source, const glm::vec3 &direction, float attenuation=1.0f);
	const glm::vec3& getSource() const;
	const glm::vec3& getDirection() const;
	void setSource(const glm::vec3& setto);
	void setDirection(const glm::vec3& setto);
	void setPositions(const glm::vec3& source, const glm::vec3& direction);

	float getAttenuation() const;
	void setAttenuation(float attenuation);
};

}

#endif // POSITIONALPANNER_HPP
