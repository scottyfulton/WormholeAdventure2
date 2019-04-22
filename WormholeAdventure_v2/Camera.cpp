#include "Camera.h"

using namespace glm;
/*
** Each GObject's light sources should be obtained by looping through every object, determining if a GObject is a light,
** then sorting (binarySort) for the 10 closest light sources
*/

Camera::Camera(GLuint shaderID, float fov, float ratio, float near_p, float far_p) {
	shader = shaderID;
	this->fov = fov;
	this->ratio = ratio;
	this->near_p = near_p;
	this->far_p = far_p;

};

Camera::~Camera() {

}

void Camera::update(double time, double dt) { //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)

};

void Camera::render(double alpha){

	//Shader
	glUseProgram(shader);

	//Interpolate

	//projection
	projectionMatrix = glm::perspective(glm::radians(fov), ratio, near_p, far_p);

	//viewMatrix
	viewMatrix = glm::mat4(1.0);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, -100)); //inverted
=======
	viewMatrix = glm::translate(viewMatrix, glm::vec3(-30, -30, -300)); //inverted
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, -50)); //inverted
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.
=======
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, -100)); //inverted
>>>>>>> This is MUCH closer to the wormhole effect that we wanted in the beginning.
	//viewMatrix = glm::rotate(viewMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Uniform
	glUniformMatrix4fv(glGetUniformLocation(shader, "projectionMatrix"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, false, glm::value_ptr(viewMatrix));


}
