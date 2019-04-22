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