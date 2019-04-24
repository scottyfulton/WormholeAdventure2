#include "Wormhole.h"


Wormhole::Wormhole() {};

Wormhole::Wormhole(std::vector<GLuint> * shaderID, std::vector<GLuint> *textureID, std::vector<GLuint> *vaoID,
	std::vector<GLsizei> *vertexCount, GLsizei particleCount, GLsizei asteroidCount, glm::vec3 pos) {
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
	this->ddPhi = 0.000005;
	this->currTheta = 0;

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
};

void Wormhole::update(double time, double dt) {

	int random = (std::rand() / RAND_MAX) % 2;
	if (random == 0) {
		for (Particle* p : particles) {
			if (!(p->living)) {
				p->reset(numParticles);
				break;
			}

		}
		for (Particle* p : particles) {
			if (p->living) {

				p->update(dTheta, phi, time, dt);
			}
		}
	};

	random = (std::rand() / RAND_MAX) % 10;
	if (random == 0) {
		for (Asteroid* a : asteroids) {
			if (!(a->living)) {
				a->reset(numAsteroids);
				break;
			}

		}
		for (Asteroid* a : asteroids) {
			if (a->living) {

				a->update(dTheta, phi, time, dt);
			}
		}
	};

	phi += sin(phi)*dPhi;
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
			p->render(&viewMatTransposed, dTheta, phi, alpha); //change to phiI once particle movement working
	}


	//VAO
	glUseProgram((*shaders)[0]);
	glBindVertexArray((*vaos)[2]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, (*textures)[2]);

	for (Asteroid* a : asteroids) {
		if (a->isAlive())
			a->render(&viewMatTransposed, dTheta, phi, alpha); //change to phiI once particle movement working
	}

};