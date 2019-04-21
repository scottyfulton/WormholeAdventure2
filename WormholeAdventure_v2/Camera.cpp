#pragma once
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
	viewMatrix = glm::translate(viewMatrix, glm::vec3(-30, -30, -300)); //inverted
	//viewMatrix = glm::rotate(viewMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Uniform
	glUniformMatrix4fv(glGetUniformLocation(shader, "projectionMatrix"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, false, glm::value_ptr(viewMatrix));


}
