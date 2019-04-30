#pragma once
#include "GObject.h"
class DigitalClock : public GObject
{
public:
	DigitalClock();
	DigitalClock(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos);
	~DigitalClock();
	virtual void update(double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	virtual void render(double alpha);
private:
	int seconds, minutes;
};

