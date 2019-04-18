#include "Particle.h"

Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos){};
Particle::~Particle(){};

void Particle::update(double time, double dt){
	//y increments by alpha
	//x and z increment based on radius (pos[0], pos[1], pos[2]) = (x, y, z)
	//radius increments based on predefined function of y
	float radius = calc(this->pos[1], function); //pass in y
	 //cos(radius) needs to be positive
	this->pos[0] = abs(cos(radius)) * this->pos[0];
	this->pos[2] = abs(cos(radius)) * this->pos[2];
};

float Particle::calc(float yVal, std::list<term> func) {
	float sum;
	for (term t : func)
		sum+= t.coeff * pow(yVal, t.exponent);

	return sum; //sum = f(y) now
};

void Particle::render(double alpha){
	
};