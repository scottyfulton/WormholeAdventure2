#include "Asteroid.h"
#include <iostream>
#include <stdlib.h>



Asteroid::Asteroid(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices,
	glm::vec3 pos, std::list<term>* baseShape) {
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = numVertices;
	this->pos = pos;
	this->baseShape = baseShape;
	this->theta = theta;
	this->living = false;
	this->isLight = true;
};

Asteroid::~Asteroid() {
	delete this;
};

//z increments by velocity of a particle
//x and y increment based on radius (pos[0], pos[1], pos[2]) = (x, y, z)
//radius increments based on predefined function of z
void Asteroid::update(float phi, double time, double dt) {
	
	if (this->pos[2] >=50) {
		this->living = false;
	}

	//float z = this->pos[2];
	//
	//float answer = z - 3;
	////keeps z-3 positive
	//if (answer <= 0)
	//{
	//	answer = 0;
	//}
	//this->radius = calc(answer, baseShape); //pass in z to baseShape function
	//radius > 79 ? radius = 79 : NULL;//limit on spread
	//this->vel += this->acc;
	//this->pos += this->vel;
	//this->pos[2] = cos(theta) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
	//this->pos[1] = sin(theta) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
	//this->pos[2] += cos(phi) * sin(z) * 5; //shift of x
	//this->pos[1] += sin(phi) * sin(z) * 5; //shift of y

	//this->pos[2] += cos(phi) * sin(z) * 5; //shift of x
	//this->pos[1] += sin(phi) * sin(z) * 5; //shift of y
};

void Asteroid::render(glm::mat4 *viewMatInv, float phi, double alpha) {
	//Interpolate
	this->posI = pos + vel * (float)alpha;
	//this->thetaI = theta + dTheta * (float)alpha;
	
	transformationMatrix = glm::mat4(1.0);//this works NICK! it's ugly but it WORKS
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(0.5, 0.5, 0.5));
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(0.2));
	transformationMatrix = glm::translate(transformationMatrix, posI);
	//transformationMatrix *= *viewMatInv; //won't work if camera's view matrix is adjusted

	//Setting Uniform Value
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));
	
	//Draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	//glDisable(GL_BLEND); //other textures aren't transparent and don't have an alpha value (0)
};

//always passed the z value of a Particle
float Asteroid::calc(float val, std::list<term>* function) {
	float sum = 0;
	for (term t : *function)
		sum += t.coeff * pow(val, t.exponent);

	return sum; //sum = f(z) now
};

void Asteroid::reset(float asteroidCount) {
	this->pos[0] = 0;
	this->vel = glm::vec3(0, 0, 1);
	this->acc = glm::vec3(0, 0, 0.85);
	this->setTheta(((float)360 / asteroidCount) * (std::rand() / (float(RAND_MAX) / 360.0f)));
	this->setLiving();
}

glm::vec3* Asteroid::getPosition() { return &(this->pos); }
glm::vec3* Asteroid::getVelocity() { return &(this->vel); }
float* Asteroid::getTheta() { return &theta; }
//for Wormhole to check if the particle should be rendered
bool Asteroid::isAlive() {
	return this->living;
};


void Asteroid::setLiving() {
	this->living = true;
}

void Asteroid::setTheta(float newTheta) {
	this->theta = newTheta;
}

//sets the new shaping function for an individual particle, called once particle "resets" back to 0 position
void Asteroid::setFunc(std::list<term>* shapingFunc) {
	shapeFunc = *shapingFunc;
};
