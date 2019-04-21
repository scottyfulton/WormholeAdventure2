#include "Particle.h"

Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos){
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = numVertices;
	this->pos = pos;
	this->vel = glm::vec3(0.1,0.2,0.2);
};

Particle::~Particle(){};

void Particle::update(double time, double dt){
	//z increments by velocity of a particle
	//x and y increment based on radius (pos[0], pos[1], pos[2]) = (x, y, z)
	//radius increments based on predefined function of y
	//float radius = calc(this->pos[2], function); //pass in y
	////cos(radius) needs to be positive
	//this->pos[0] = abs(cos(radius)) * this->pos[0];
	//this->pos[1] = abs(cos(radius)) * this->pos[2];
	/*this->pos[0] += 0.1;
	this->pos[1] += 0.1;*/
	this->pos += this->vel;
};

void Particle::render(double alpha){
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
	
	//Interpolate
	this->posI = pos + vel*(float)alpha;

	//Transformation
	transformationMatrix = glm::mat4(1.0);//this works NICK! it's ugly but it WORKS
	glm::mat4 specialView = glm::transpose(glm::mat4(1.0));
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(10.2, 10.2, 10.2)); 
	transformationMatrix = glm::translate(transformationMatrix, posI);
	
	transformationMatrix *= specialView;
	
	//Uniform
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glDisable(GL_BLEND);
};

float Particle::calc(float val, std::list<term>* baseShape) {
	float sum = 0;
	for (term t : *function)
		sum += t.coeff * pow(val, t.exponent);

	return sum; //sum = f(z) now
};

//for Wormhole to check if the particle should be rendered
bool Particle::isAlive(){
	return living;
}; 

//sets the new shaping function for an individual particle, called once particle "resets" back to 0 position
void Particle::setFunc(){

};
