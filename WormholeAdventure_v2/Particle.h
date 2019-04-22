#pragma once
#include "GObject.h"
#include <list>
#include "Term.h"

class Particle : GObject {
public:
	bool living;

	Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos, float theta, std::list<term>* baseShape);
	~Particle();

	void update(float dTheta, float phi, double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(float dTheta, float phi, double alpha);
	float calc(float val, std::list<term>* function);
	bool isAlive(); //for Wormhole to check if the particle should be rendered
	void setFunc(std::list<term>* shapingFunc); //sets the new shaping function for an individual particle, called once particle "resets" back to 0 position
	void setLiving(); //sets "living" boolean to true
	// inherits projectionMatrix, transformationMatrix, pos,
	// vel, & acc(not used)
	// every particle will also be a light

private:
	//wormhole will create a list of terms (function) to pass to each new particle
	std::list<term>* baseShape;
	std::list<term> shapeFunc;
	float theta; //the angle that an individual particle will be rotated after being translated (drawing the circumference of the wormhole)
	void updateTheta(float dTheta, double alpha); //interpolates theta value, called in render()
	glm::vec3 posI;
};
