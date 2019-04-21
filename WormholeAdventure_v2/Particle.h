#pragma once
<<<<<<< HEAD
#include <list>
#include <random>
#include <iostream>
#include "Term.h"
#include "GObject.h"

class Particle : GObject {
public:
	bool living;

	Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos, std::list<term>* baseShape);
	~Particle();

	void update(float dTheta, float phi, double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(float dTheta, float phi, double alpha);
	float calc(float val, std::list<term>* function);
	bool isAlive(); //for Wormhole to check if the particle should be rendered
	void setFunc(std::list<term>* shapingFunc); //sets the new shaping function for an individual particle, called once particle "resets" back to 0 position
	void reset(float particleCount);
	// inherits projectionMatrix, transformationMatrix, pos,
	// vel, & acc(not used)
	// every particle will also be a light

private:
	//wormhole will create a list of terms (function) to pass to each new particle
	std::list<term>* baseShape;
	std::list<term> shapeFunc;
	float theta, thetaI, radius; //the angle that an individual particle will be rotated after being translated (drawing the circumference of the wormhole)
	void setLiving(); //sets "living" boolean to true
	void setTheta(float newTheta);
	//void updateTheta(float dTheta, double alpha); //interpolates theta value, called in render()
	glm::vec3 posI;
=======
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
<<<<<<< HEAD
	std::list<term> function;
>>>>>>> Created Particle class. Uses a list<term> to keep track of the function (list of terms) that each Particle will update based on. (term has a coefficient and exponent)
=======
	std::list<term>* function;
	float theta; //the angle that an individual particle will be rotated after being translated (drawing the circumference of the wormhole)
	glm::vec3 posI;
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
};
