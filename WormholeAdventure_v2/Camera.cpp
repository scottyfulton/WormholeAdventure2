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

void Camera::update(float phi, double time, double dt) { //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	float z = this->pos[2];
	float radius = pow(z, 2);
	//this->pos[0] += cos(phi) * sin(z / 12.75) * 30 * radius; //shift of x
	//this->pos[1] += sin(phi) * sin(z / 12.75) * 30 * radius; //shift of y
};

void Camera::render(double alpha){

	//Shader
	glUseProgram(shader);

	//Interpolate

	//projection
	projectionMatrix = glm::perspective(glm::radians(fov), ratio, near_p, far_p);

	//viewMatrix
	viewMatrix = glm::mat4(1.0);
	//viewMatrix = glm::rotate(viewMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0, -80.0f)); // adjustments to camera in x- or z-axis are inverted, not to anything else
	//viewMatrix = glm::rotate(viewMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Uniform
	glUniformMatrix4fv(glGetUniformLocation(shader, "projectionMatrix"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, false, glm::value_ptr(viewMatrix));
}

glm::mat4* Camera::getView() {
	return &viewMatrix;
}

void Camera::setRotationAngles(float phi) {
	float xCoord = cos(phi) * pow(40, 2);
	float yCoord = sin(phi) * pow(40, 2);
	float deltaZ = (-(this->pos.z) + 40);
	//float distanceToPt = sqrt(pow(xCoord, 2) + pow(yCoord, 2) + pow(deltaZ, 2));
	float distanceX = sqrt(pow(xCoord, 2) + pow(deltaZ, 2));
	float distanceY = sqrt(pow(yCoord, 2) + pow(deltaZ, 2));
	this->rotX = asin(xCoord / distanceX);
	this->rotY = asin(yCoord / distanceY);
}