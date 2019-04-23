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
	this->shaping = {{-1, 2}, {1,1} };
	this->phi = 0;
	this->dPhi = 0;
	this->ddPhi = 0.000005;
	this->currTheta = 0;

	//float random = (r() / r.max) * 5;
	for (int i = 0; i < particleCount; i++) {
		particles.push_back(new Particle(shaderID, textureID, vaoID, particleCount, pos, &cone));
		particles.back()->setFunc(&shaping);
	}
};

//destruct all Particles
Wormhole::~Wormhole() {
	for (Particle* p : particles)
		p->~Particle();
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
		int numAlive = 0;
		for (Particle* p : particles) {
			if (p->living) {
				numAlive++;
				p->update(dTheta, phi, time, dt);
			}
		}
		//std::cout << "Number of Particles alive: " << numAlive << std::endl;
		phi += dPhi;
		dPhi += ddPhi;
	};
};

void Wormhole::render(double alpha) {
	//Shader
	glUseProgram(shader);
	//VAO
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//float phiI = phi + dPhi*alpha;
	for (Particle* p : particles) {
		if (p->isAlive())
			p->render(dTheta, phi, alpha); //change to phiI once particle movement working
	}

};