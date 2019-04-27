#pragma once
<<<<<<< HEAD
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
	void render(glm::mat4 *viewMat, float dTheta, float phi, double alpha);
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
<<<<<<< HEAD
=======
#include "GObject.h"
=======
>>>>>>> This is MUCH closer to the wormhole effect that we wanted in the beginning.
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
	void render(glm::mat4 *viewMatInv, float dTheta, float phi, double alpha);
	float calc(float val, std::list<term>* function);
	bool isAlive(); //for Wormhole to check if the particle should be rendered
	void setFunc(std::list<term>* shapingFunc); //sets the new shaping function for an individual particle, called once particle "resets" back to 0 position
	void reset(float particleCount);
	// inherits projectionMatrix, transformationMatrix, pos,
	// vel, & acc(not used)
	// every particle will also be a light

private:
	//wormhole will create a list of terms (function) to pass to each new particle
<<<<<<< HEAD
<<<<<<< HEAD
	std::list<term> function;
>>>>>>> Created Particle class. Uses a list<term> to keep track of the function (list of terms) that each Particle will update based on. (term has a coefficient and exponent)
=======
	std::list<term>* function;
=======
	std::list<term>* baseShape;
	std::list<term> shapeFunc;
<<<<<<< HEAD
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.
	float theta; //the angle that an individual particle will be rotated after being translated (drawing the circumference of the wormhole)
	void updateTheta(float dTheta, double alpha); //interpolates theta value, called in render()
=======
	float theta, thetaI, radius; //the angle that an individual particle will be rotated after being translated (drawing the circumference of the wormhole)
	void setLiving(); //sets "living" boolean to true
	void setTheta(float newTheta);
	//void updateTheta(float dTheta, double alpha); //interpolates theta value, called in render()
>>>>>>> This is MUCH closer to the wormhole effect that we wanted in the beginning.
	glm::vec3 posI;
<<<<<<< HEAD
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
	glm::mat4 getBillboardMat(glm::mat4* viewMat);
>>>>>>> messed with the camera to rotate it to look down the wormhole. buggy. bugs buggy.
=======
	glm::mat4 getBillboardMat(glm::mat4* viewMat);
>>>>>>> Added bilboarding and moved ship closer
};
