<<<<<<< HEAD
<<<<<<< HEAD
#include "Wormhole.h"


Wormhole::Wormhole() {};

Wormhole::Wormhole(std::vector<GLuint> * shaderID, std::vector<GLuint> *textureID, 
	std::vector<GLuint> *vaoID,	std::vector<GLsizei> *vertexCount, 
	GLsizei particleCount, GLsizei asteroidCount, glm::vec3 pos) {
	this->shaders = shaderID;
	this->textures = textureID;
	this->vaos = vaoID;
	this->vertexCounts = vertexCount;
	this->numParticles = particleCount;
	this->numAsteroids = asteroidCount;
	this->pos = pos;
	//this->vel = glm::vec3(0.01f, 0.0f, -0.01f);
	this->shaping = { {-1, 2}, {1,1} };
	this->phi = 0;
	this->dPhi = 0;
	this->ddPhi = 0.0000005;
	this->currTheta = 0;
	this->particleTimer = (100000 / numParticles);
	this->asteroidTimer = (1000000000 / numAsteroids);

	//float random = (r() / r.max) * 5;
	for (int i = 0; i < particleCount; i++) {
		particles.push_back(new Particle((*shaders)[0], (*textures)[1], (*vaos)[1], 6, pos, &cone));
		particles.back()->setFunc(&shaping);
	}

	for (int i = 0; i < asteroidCount; i++) {
		asteroids.push_back(new Asteroid((*shaders)[0], (*textures)[2], (*vaos)[2], (*vertexCounts)[2], pos, &cone));
		asteroids.back()->setFunc(&shaping);
	}

};

//destruct all Particles
Wormhole::~Wormhole() {
	for (Particle* p : particles)
		p->~Particle();

	for (Asteroid* a : asteroids)
		a->~Asteroid();

	delete this;
};

void Wormhole::update(double time, double dt) {

	float percentage = ((std::rand() % 10000)) * (particleTimer/2);
	particleTimer -= percentage;
	if (particleTimer <= 0.0f) {
		for (Particle* p : particles) {
			if (!(p->living)) {
				p->reset(numParticles);
				break;
			}

		}
		particleTimer = (100000 / numParticles);
	};
	for (Particle* p : particles) {
		if (p->living) {
			updateP(p->getTheta(), p->getPosition(), p->getVelocity());
			p->update(dTheta, phi, time, dt);
		}
	}
	percentage = ((std::rand() % 100)) * (asteroidTimer/2);
	asteroidTimer -= percentage;
	if (asteroidTimer <= 0.0f) {
		for (Asteroid* a : asteroids) {
			if (!(a->living)) {
				a->reset(numAsteroids);
				break;
			}

		}
		asteroidTimer = (1000000000 / numAsteroids);
	};

	for (Asteroid* a : asteroids) {
		if (a->living) {
			updateA((a->getTheta()), a->getPosition(), a->getVelocity());
			a->update(phi, time, dt);
		}
	}

	phi += dPhi;
	dPhi += ddPhi;
};

void Wormhole::render(double alpha) {
	//Shader
	glUseProgram((*shaders)[0]);
	//VAO
	glBindVertexArray((*vaos)[1]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*textures)[1]);

	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//float phiI = phi + dPhi*alpha;
	for (Particle* p : particles) {
		if (p->isAlive())
			p->render(&viewMat, dTheta, phi, alpha); //change to phiI once particle movement working
	}

	// set up for asteroids
	//glUseProgram((*shaders)[0]);
	glBindVertexArray((*vaos)[2]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, (*textures)[2]);

	for (Asteroid* a : asteroids) {
		if (a->isAlive())
			a->render(&viewMat, phi, alpha); //change to phiI once particle movement working
	}

};

void Wormhole::updateP(float* theta, glm::vec3* objPos, glm::vec3* vel){
	float z = (*objPos)[2];
	float radius = z; //pass in z to baseShape function
	radius > 15.0f ? radius = 15.0f : NULL;//limit on spread

	(*objPos) += *vel;
	(*objPos)[0] = cos(*theta) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
	(*objPos)[1] = sin(*theta) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
	//(*objPos)[0] -= cos(phi) * sin(z/5.0f) * 10.0f; //shift of x
	//(*objPos)[1] -= sin(phi) * sin(z/5.0f) * 10.0f; //shift of y
	*theta += dTheta;
};

void Wormhole::updateA(float* theta, glm::vec3* objPos, glm::vec3* vel) {
	float z = (*objPos)[2];
	float radius = z; //pass in z to baseShape function
	radius > 5.0f ? radius = 5.0f : NULL;//limit on spread

	(*objPos) += *vel;
	(*objPos)[0] = cos(*theta) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
	(*objPos)[1] = sin(*theta) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
	//(*objPos)[0] -= cos(phi) * sin(z / 5.0f) * 10.0f; //shift of x
	//(*objPos)[1] -= sin(phi) * sin(z / 5.0f) * 10.0f; //shift of y
};

float Wormhole::getPhi() {
	return this->phi;
};

void Wormhole::setviewMat(glm::mat4 *viewMat){
	this->viewMat = *viewMat;
};

std::list<Asteroid*>* Wormhole::getAsteroid()
{

	return &asteroids;
}
=======
#pragma once
=======
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.
#include "Wormhole.h"

Wormhole::Wormhole(){};

Wormhole::Wormhole(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei vertexCount, GLsizei particleCount, glm::vec3 pos){
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = vertexCount;
	this->numParticles = particleCount;
	this->pos = pos;
	//this->vel = glm::vec3(0.01f, 0.0f, -0.01f);
	this->shaping = {{1, 2}, {1,1}};
	this->phi = 0;
	this->dPhi = 0.1;
	this->currTheta = 0;

	//float random = (r() / r.max) * 5;
	for (int i = 0; i < particleCount; i++){
		//pos[0] = pos[0] + i*2;
		particles.push_back(new Particle(shaderID, textureID, vaoID, particleCount, pos, currTheta, (r() / (int)r.max) * 200, &cone));
		particles.back()->setFunc(&shaping);
		currTheta += (float)360/particleCount; //roughly 2*PI / particleCount
	}
};

//destruct all Particles
Wormhole::~Wormhole(){
	for(Particle* p: particles)
		p->~Particle(); 
};

void Wormhole::update(double time, double dt){
	for (Particle* p : particles) {
		if (p->isAlive()) {
			p->update(dTheta, phi, time, dt);
		} else {
			if (p->emitTimer <= 0)
			{
				p = new Particle(shader, texture, vao, numParticles, pos, currTheta, (r() / (int)r.max) * 200, &cone);
			} else {
				p->emitTimer--;
				if(p->emitTimer <= 0)
					p->setLiving();
			}
			
		}
	}

	phi += dPhi;
};

void Wormhole::render(double alpha){
	//float phiI = phi + dPhi*alpha;
	for (Particle* p : particles)
		p->render(dTheta, phi, alpha); //change to phiI once particle movement working
};

//rng a new shaping function (always a quadratic function) to give a "new" particle
void Wormhole::setNewShapingFunc(){
	
}; 
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
