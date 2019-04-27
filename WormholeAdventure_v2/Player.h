#pragma once
#pragma once
// Include GLEW
#include <GL/glew.h>
#include <GL/glut.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
//For using the clock
//#include <chrono>
//for loading the image
//#include <soil.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/ext.hpp>

#include <string>
#include <iostream>

#include "GObject.h"
#include "Player.h"

using namespace glm;

class Player{
public:
	Player(); // implicitly called when child classes are constructed
	Player(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos, glm::vec3 rotate);
	~Player();

	void update(double time, double dt, bool arr[4]); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha);
	void resetNetForce();
	void addForce(float force, float theta, float phi);
	void addForceVec(float x, float y, float z);
	glm::vec3 getPosition();

protected:
	float radTemp = glm::radians(90.f);
	float valX, valY, valZ, phi, theta, force, movFriction, mass;
	GLuint texture, shader, vao; // simply a reference to the correct vao/vbo to use for each GObject drawn
	// when glDrawElements called, pass each object's "texture", "shader", etc. which simply reference the already loaded & bound data
	//Matricies
	glm::mat4 projectionMatrix;
	glm::mat4 transformationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationXMatrix;
	glm::mat4 rotationYMatrix;
	glm::mat4 rotationZMatrix;
	glm::mat4 modelMatrix;
	glm::mat4 translationMatrix;

	/*pos, vel, acc*/
	glm::vec3 pos;
	glm::vec3 posI;
	glm::vec3 vel;
	glm::vec3 acc;
	glm::vec3 rot;
	glm::vec3 netForce;

	GLsizei numVertices;

	bool isLight;

	//private
	//add gobject ptr

/*

scale, rota x, y, z, translate
getters and setters for all mat and vec
vec3 rotate
mult

trans = T Z Y X S

*/
};
