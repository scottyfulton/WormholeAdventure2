#pragma once
#include "Wormhole.h"

Wormhole::Wormhole(){};

Wormhole::Wormhole(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei vertexCount, GLsizei particleCount, glm::vec3 pos){
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = vertexCount;
	this->pos = pos;
	//this->vel = glm::vec3(0.01f, 0.0f, -0.01f);

	for (int i = 0; i < particleCount; i++){
		pos[0] = pos[0] + i*2;
		particles.push_back(new Particle(shaderID, textureID, vaoID, particleCount, pos));
	}
};

Wormhole::~Wormhole(){};

void Wormhole::update(double time, double dt){
	for(Particle* p: particles)
		p->update(time, dt);
};

void Wormhole::render(double alpha){
	for (Particle* p : particles)
		p->render(alpha);

	////Shader
	//glUseProgram(shader);
	////VAO
	//glBindVertexArray(vao);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	////Texture
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	
	//Interpolate


	//Transformation
	

	////Uniform
	//glUniform1i(texture, 0);
	//glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	//glDrawArrays(GL_TRIANGLES, 0, numParticles);
};

//rng a new shaping function (always a quadratic function) to give a "new" particle
void Wormhole::setNewShapingFunc(){
	
}; 