#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class Camera {
public:
	Camera(GLuint shaderID, float fov, float ratio, float near_p, float far_p);
	~Camera();

<<<<<<< HEAD
	void update(float phi, double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha);
	glm::mat4* getView();
	void setRotationAngles(float phi);
=======

	void update(float phi, double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha);
	glm::mat4* getView();
>>>>>>> Latest, got shiz

private:
	GLuint shader; // simply a reference to the correct vao/vbo to use for each GObject drawn
	// when glDrawElements called, pass each object's "texture", "shader", etc. which simply reference the already loaded & bound data
<<<<<<< HEAD
	
	//Matricies
	glm::mat4 projectionMatrix, viewMatrix;
	glm::vec3 pos = glm::vec3(0, 0, -900), vel, acc;
	float fov, ratio, near_p, far_p, phi, rotX, rotY;
=======

	//Matricies
	glm::mat4 projectionMatrix, viewMatrix, transformationMatrix;
	glm::vec3 pos = glm::vec3(0, 0, -500), vel, acc;
	float fov, ratio, near_p, far_p, phi;
>>>>>>> Latest, got shiz
};
