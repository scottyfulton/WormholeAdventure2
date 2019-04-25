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





using namespace glm;


class GObject {
public:
	GObject(); // implicitly called when child classes are constructed
	GObject(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos, glm::vec3 rot);
	~GObject();

	void update(double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha);


protected:
	
	GLuint texture, shader, vao, type; // simply a reference to the correct vao/vbo to use for each GObject drawn
	// when glDrawElements called, pass each object's "texture", "shader", etc. which simply reference the already loaded & bound data
	;

	//Matricies
	//glm::mat4 projectionMatrix;
	glm::mat4 transformationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationXMatrix;
	glm::mat4 rotationYMatrix;
	glm::mat4 rotationZMatrix;
	glm::mat4 translateMatrix;

	//pos, vel, acc
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;
<<<<<<< HEAD
	
<<<<<<< HEAD
	
	
=======
	glm::vec3 rot;
>>>>>>> updated player class with input switch case

=======
>>>>>>> messed with the camera to rotate it to look down the wormhole. buggy. bugs buggy.
	GLsizei numVertices;
	bool isLight;
};

/*

scale, rota x, y, z, translate
getters and setters for all mat and vec
vec3 rotate
mult 

trans = T Z Y X S

*/