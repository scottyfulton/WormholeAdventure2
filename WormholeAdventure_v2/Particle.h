#pragma once
#include "GObject.h"
#include <list>
#include <cmath> //cos,sin, exponential math
#include "Term.h"

class Particle : GObject {
public:
	Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos);
	~Particle();
	//term should be in wormhole, wormhole determines the function for new particles

	void update(double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha);
	float calc(float val, std::list<term>* baseShape);
	bool isAlive(); //for Wormhole to check if the particle should be rendered
	void setFunc(); //sets the new shaping function for an individual particle, called once particle "resets" back to 0 position
	// inherits projectionMatrix, transformationMatrix, pos,
	// vel(not used), & acc(not used)
	// every particle will also be a light

private:
	bool living;
	//wormhole will create a list of terms (function) to pass to each new particle
	std::list<term>* function;
	float theta; //the angle that an individual particle will be rotated after being translated (drawing the circumference of the wormhole)
	glm::vec3 posI;
};
