#include "Wormhole.h"

Wormhole::Wormhole() {};

Wormhole::Wormhole(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei vertexCount, GLsizei particleCount, glm::vec3 pos) {
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = vertexCount;
	this->numParticles = particleCount;
	this->pos = pos;
	//this->vel = glm::vec3(0.01f, 0.0f, -0.01f);
	this->shaping = { {1, 2}, {1,1} };
	this->phi = 0;
	this->dPhi = 0.01;
	this->currTheta = 0;

	//float random = (r() / r.max) * 5;
	for (int i = 0; i < particleCount; i++) {
		//pos[0] = pos[0] + i*2;
		particles.push_back(new Particle(shaderID, textureID, vaoID, particleCount, pos, currTheta, &cone));
		particles.back()->setFunc(&shaping);
		currTheta += (float)360 / particleCount; //roughly 2*PI / particleCount
	}
};

//destruct all Particles
Wormhole::~Wormhole() {
	for (Particle* p : particles)
		p->~Particle();
};

void Wormhole::update(double time, double dt) {
	int random = r() % 1;
	if (random == 0) {
		for (Particle* p : particles) {
			if (!(p->living)) {
				p->setLiving();



				break;
			}

		}

		for (Particle* p : particles) {
			if (p->living)
				p->update(dTheta, phi, time, dt);
		}
		phi += dPhi;
	};
};

void Wormhole::render(double alpha) {
		//float phiI = phi + dPhi*alpha;
		for (Particle* p : particles) {
			if (p->isAlive())
				p->render(dTheta, phi, alpha); //change to phiI once particle movement working
		}

	};