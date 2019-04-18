#pragma once
#include "GObject.h"
#include <list>
#include <cmath> //cos,sin, exponential math

class Particle : GObject {
public:
	Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos);
	~Particle();
	//term should be in wormhole, wormhole determines the function for new particles
	struct term {
		int exponent, coeff;
	};

	void update(double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha);
	float calc(float val, std::list<term> func);

	// inherits projectionMatrix, transformationMatrix, pos,
	// vel(not used), & acc(not used)
	// every particle will also be a light

private:
	bool living;
	//wormhole will create a list of terms (function) to pass to each new particle
	std::list<term> function;
};
