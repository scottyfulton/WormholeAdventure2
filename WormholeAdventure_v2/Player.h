#pragma once
<<<<<<< HEAD

=======
#pragma once
>>>>>>> updated player class with input switch case
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
<<<<<<< HEAD
#include <vector>

#include <string>
#include <iostream>
=======

#include <string>
<<<<<<< HEAD
>>>>>>> updated player class with input switch case
=======
#include <iostream>
>>>>>>> Latest, got shiz

#include "GObject.h"
#include "Player.h"

using namespace glm;

class Player{
public:
	Player(); // implicitly called when child classes are constructed
<<<<<<< HEAD
	Player(std::vector<GLuint> * shaderID, std::vector<GLuint> * textureID,
		std::vector<GLuint> * vaoID, std::vector<GLsizei> *vertexCount,
		glm::vec3 pos, glm::vec3 rotate);
	~Player();

	void update(double time, double dt, bool arr[4]); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha, bool isHit);
	void resetNetForce();
	void addForce(float force, float theta, float phi);
	void addForceVec(float x, float y, float z);
	glm::vec3 getPosition();
	glm::mat4 getBillboardMat(glm::mat4* viewMat);
	void setviewMat(glm::mat4 *viewMat);

protected:
	float radTemp = glm::radians(90.f);
	float valX, valY, valZ, phi, theta, force, movFriction, mass;
	std::vector<GLuint> *textures, *shaders, *vaos; // simply a reference to the correct vao/vbo to use for each GObject drawn
=======
	Player(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos, glm::vec3 rotate);
	~Player();

	void update(double time, double dt, bool arr[4]); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha);
	void resetNetForce();
	void addForce(float force, float theta, float phi);
	void addForceVec(float x, float y, float z);

protected:
	float radTemp = glm::radians(90.f);
	float valX, valY, valZ, phi, theta, force, movFriction, mass;
	GLuint texture, shader, vao; // simply a reference to the correct vao/vbo to use for each GObject drawn
>>>>>>> updated player class with input switch case
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
<<<<<<< HEAD
	glm::mat4 translationMatrix, viewMat;

	/*pos, vel, acc*/
	glm::vec3 pos;
	glm::vec3 posI;
	glm::vec3 vel;
	glm::vec3 acc;
	glm::vec3 rot;
	glm::vec3 netForce;
=======
	glm::mat4 translationMatrix;

	/*pos, vel, acc*/
	glm::vec3 pos;
	glm::vec3 posI;
	glm::vec3 vel;
	glm::vec3 acc;
	glm::vec3 rot;
<<<<<<< HEAD
>>>>>>> updated player class with input switch case
=======
	glm::vec3 netForce;
>>>>>>> Latest, got shiz

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
