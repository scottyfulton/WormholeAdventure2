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
<<<<<<< HEAD
	float radius = pow(z,2);
	this->phi = phi;
	//this->setRotationAngles(phi);
	//this->pos[0] += cos(phi) * sin(z / 12.75) * 30 * radius; //shift of x
	//this->pos[1] += sin(phi) * sin(z / 12.75) * 30 * radius; //shift of y
=======
	float radius = pow(z, 2);
<<<<<<< HEAD
	this->pos[0] += cos(phi) * sin(z / 12.75) * 30 * radius; //shift of x
	this->pos[1] += sin(phi) * sin(z / 12.75) * 30 * radius; //shift of y
>>>>>>> Latest, got shiz
=======
	//this->pos[0] += cos(phi) * sin(z / 12.75) * 30 * radius; //shift of x
	//this->pos[1] += sin(phi) * sin(z / 12.75) * 30 * radius; //shift of y
>>>>>>> Updated wormhole to perform position calculations for each Particle/Asteroid. Made shaping function an even amplitude throughout. Sped up Asteroids. Asteroids STILL follow a DIFFERENT path than Particles for SOME UNGODLY REASON.
};

void Camera::render(double alpha){

	//Shader
	glUseProgram(shader);

	//Interpolate

	//projection
	projectionMatrix = glm::perspective(glm::radians(fov), ratio, near_p, far_p);
	viewMatrix = glm::mat4(1.0);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, -500)); //inverted
>>>>>>> Updated Camera to adjust its position to move with the center of the wormhole. Updated Particles & Asteroids to not use the transpose of the Camera's view matrix & directly use the Camera's view matrix (passed to each Particle/Asteroid). Got keyboard input working how we want with Blane.
=======
	//viewMatrix = glm::rotate(viewMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
<<<<<<< HEAD
<<<<<<< HEAD
	//viewMatrix = glm::translate(viewMatrix, glm::vec3(-40.0f, 0, 0.0f)); //inverted
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0, -100.0f)); //inverted
>>>>>>> Added bilboarding and moved ship closer
=======
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0, -50.0f)); // adjustments to camera in x- or z-axis are inverted, not to anything else
>>>>>>> Updated wormhole to perform position calculations for each Particle/Asteroid. Made shaping function an even amplitude throughout. Sped up Asteroids. Asteroids STILL follow a DIFFERENT path than Particles for SOME UNGODLY REASON.
=======
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0, -80.0f)); // adjustments to camera in x- or z-axis are inverted, not to anything else
>>>>>>> Changed phi value for moving player left (case 2) to 90 & commented the z-coordinate update for the player (shouldn't move in the z anyways). Weird result.
	//viewMatrix = glm::rotate(viewMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

=======
	//glm::vec3 samplePoint = glm::vec3(cos(phi) * pow(12.0f, 2.0f), sin(phi) * pow(12.0f, 2.0f), 12.0f); //12.0f
	glm::vec3 samplePoint = glm::vec3(pow(12.0f, 2.0f), pow(12.0f, 2.0f), 12.0f); //12.0f
	glm::vec3 upBS = glm::vec3(0.0f, -1.0f, 0.0f);
	viewMatrix = glm::lookAt(pos, samplePoint, upBS);
	//viewMatrix = glm::rotate(viewMatrix, glm::radians(-phi), glm::vec3(0.0f, 0.0f, 1.0f));
	/*glm::mat4 rotationY = glm::rotate(viewMatrix, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationX = glm::rotate(viewMatrix, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));*/
	//viewMatrix *= (rotationX * rotationY);
	//viewMatrix = glm::translate(viewMatrix, pos); //inverted
	//viewMatrix = glm::translate(viewMatrix, pos); 
>>>>>>> messed with the camera to rotate it to look down the wormhole. buggy. bugs buggy.
	//Uniform
	glUniformMatrix4fv(glGetUniformLocation(shader, "projectionMatrix"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, false, glm::value_ptr(viewMatrix));
<<<<<<< HEAD
}

void Camera::setRotationAngles(float phi) {
	float xCoord = cos(phi) * pow(800,2);
	float yCoord = sin(phi) * pow(800,2);
	float deltaZ = (-(this->pos.z)+ 800);
	//float distanceToPt = sqrt(pow(xCoord, 2) + pow(yCoord, 2) + pow(deltaZ, 2));
	float distanceX = sqrt(pow(xCoord, 2) + pow(deltaZ, 2));
	float distanceY = sqrt(pow(yCoord, 2) + pow(deltaZ, 2));
	this->rotX = asin(xCoord / distanceX);
	this->rotY = asin(yCoord / distanceY);

}

glm::mat4* Camera::getView() {
	return &viewMatrix;
=======
>>>>>>> Updated wormhole to perform position calculations for each Particle/Asteroid. Made shaping function an even amplitude throughout. Sped up Asteroids. Asteroids STILL follow a DIFFERENT path than Particles for SOME UNGODLY REASON.
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