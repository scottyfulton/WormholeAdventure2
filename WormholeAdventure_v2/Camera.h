#pragma once
// Include GLEW
#include <GL/glew.h>
//#include <GL/glut.h>
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

class Camera {
public:
	Camera(GLuint shaderID, float fov, float ratio, float near_p, float far_p);
	~Camera();


	void update(float phi, double time, double dt); //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	void render(double alpha);
	glm::mat4* getView();

private:
	GLuint shader; // simply a reference to the correct vao/vbo to use for each GObject drawn
	// when glDrawElements called, pass each object's "texture", "shader", etc. which simply reference the already loaded & bound data

	//Matricies
	glm::mat4 projectionMatrix, viewMatrix, transformationMatrix;
	glm::vec3 pos = glm::vec3(0, 0, -50), vel, acc;
	float fov, ratio, near_p, far_p, phi;
};
