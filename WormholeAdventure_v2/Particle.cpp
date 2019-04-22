#include "Particle.h"

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, 
					glm::vec3 pos, std::list<term>* baseShape){
=======
Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos){
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======

Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, 
					glm::vec3 pos, float theta, float emitTime, std::list<term>* baseShape){
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = numVertices;
	this->pos = pos;
<<<<<<< HEAD
<<<<<<< HEAD
	this->baseShape = baseShape;
	this->theta = theta;
	this->living = false;
	this->isLight = true;
};

Particle::~Particle(){
	delete this;
};

//z increments by velocity of a particle
//x and y increment based on radius (pos[0], pos[1], pos[2]) = (x, y, z)
//radius increments based on predefined function of z
void Particle::update(float dTheta, float phi, double time, double dt){
	if (this->pos[2] >= 25) {
		this->living = false;
	}
	//std::cout << "z value of particle: " << this->pos[2] << std::endl;
		float z = this->pos[2];
		this->radius = calc(z, baseShape); //pass in z to baseShape function
		this->vel += this->acc;
		this->pos += this->vel;
		this->pos[0] = cos(theta) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
		this->pos[1] = sin(theta) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
		this->pos[0] += 2.4*cos(phi) * sin(z/3.5) * calc(z, &shapeFunc); //shift of x
		this->pos[1] += 2.4 * sin(phi) * sin(z/3.5) * calc(z, &shapeFunc); //shift of y
		this->theta += dTheta;
};

void Particle::render(float dTheta, float phi, double alpha){	
	//Interpolate
	this->posI = pos + vel*(float)alpha;
	this->thetaI = theta + dTheta * (float)alpha;
	//this->posI[0] = cos(thetaI) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
	//this->posI[1] = sin(thetaI) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
	//this->posI[0] += (cos(phi/2) * calc(this->pos[2], &shapeFunc))*(float)alpha;
	//this->posI[1] += (sin(phi/2) * calc(this->pos[2], &shapeFunc))*(float)alpha;
	

	//Transformation
	transformationMatrix = glm::mat4(1.0);//this works NICK! it's ugly but it WORKS
	//transformationMatrix = glm::scale(transformationMatrix, glm::vec3(0.5, 0.5, 0.5));
	transformationMatrix = glm::translate(transformationMatrix, posI);
	//multiplying by the transpose of the view matrix of Camera to counteract skewing caused by persepective
	transformationMatrix *= glm::transpose(glm::mat4(1.0)); //won't work if camera's view matrix is adjusted
	
	//Setting Uniform Value
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glDisable(GL_BLEND); //other textures aren't transparent and don't have an alpha value (0)
};

//always passed the z value of a Particle
float Particle::calc(float val, std::list<term>* function) {
	float sum = 0;
	for (term t : *function)
		sum += t.coeff * pow(val, t.exponent); 

	return sum; //sum = f(z) now
};

//for Wormhole to check if the particle should be rendered
bool Particle::isAlive(){
	return this->living;
};

void Particle::reset(float particleCount){
	this->pos[2] = 0;
	this->vel = glm::vec3(0, 0, 0.0001);
	this->acc = glm::vec3(0, 0, 0.00005);
	this->setTheta(((float)360 / particleCount) * (std::rand() / (float(RAND_MAX) / 360.0f)));
	this->setLiving();
}

void Particle::setLiving() {
	this->living = true;
}

void Particle::setTheta(float newTheta) {
	this->theta = newTheta;
}

//sets the new shaping function for an individual particle, called once particle "resets" back to 0 position
void Particle::setFunc(std::list<term>* shapingFunc){
	shapeFunc = *shapingFunc;
};
=======
Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos){};
=======
	this->vel = glm::vec3(0.1,0.2,0.2);
};

>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
Particle::~Particle(){};
=======
	this->vel = glm::vec3(0,0,0.02);
	this->baseShape = baseShape;
	this->theta = theta;
	this->emitTimer = emitTime;
	this->living = false;
	this->isLight = true;
};

Particle::~Particle(){
	delete this;
};
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.

//z increments by velocity of a particle
//x and y increment based on radius (pos[0], pos[1], pos[2]) = (x, y, z)
//radius increments based on predefined function of z
void Particle::update(float dTheta, float phi, double time, double dt){
	float radius = calc(this->pos[2], baseShape); //pass in z to baseShape function
	this->pos += this->vel;
	this->pos[0] = cos(theta) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
	this->pos[1] = sin(theta) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
	this->pos[0] += cos(phi/2) * calc(this->pos[2]/2, &shapeFunc); //shift of x
	this->pos[1] += sin(phi/2) * calc(this->pos[2]/2, &shapeFunc); //shift of y
	this->theta += dTheta;
};

void Particle::render(float dTheta, float phi, double alpha){
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
	//this->posI[0] += cos(phi/4) * calc(this->pos[2]/2, &shapeFunc)*(float)alpha; --causes skipping/twitching
	//this->posI[1] += sin(phi/4) * calc(this->pos[2]/2, &shapeFunc)*(float)alpha;
	this->updateTheta(dTheta, alpha);

	//Transformation
	transformationMatrix = glm::mat4(1.0);//this works NICK! it's ugly but it WORKS
	//transformationMatrix = glm::scale(transformationMatrix, glm::vec3(0.2, 0.2, 0.2)); 
	transformationMatrix = glm::translate(transformationMatrix, posI);
	//multiplying by the transpose of the view matrix of Camera to counteract skewing caused by persepective
	transformationMatrix *= glm::transpose(glm::mat4(1.0)); //won't work if camera's view matrix is adjusted
	
<<<<<<< HEAD
<<<<<<< HEAD
};
>>>>>>> Created Particle class. Uses a list<term> to keep track of the function (list of terms) that each Particle will update based on. (term has a coefficient and exponent)
=======
	transformationMatrix *= specialView;
	
	//Uniform
=======
	//Setting Uniform Value
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glDisable(GL_BLEND); //other textures aren't transparent and don't have an alpha value (0)
};

//always passed the z value of a Particle
float Particle::calc(float val, std::list<term>* function) {
	float sum = 0;
	for (term t : *function)
		sum += t.coeff * pow(val, t.exponent); 

	return sum; //sum = f(z) now
};

void Particle::updateTheta(float dTheta, double alpha) {
	this->theta += dTheta * (float)alpha;
}

//for Wormhole to check if the particle should be rendered
bool Particle::isAlive(){
	if (this->pos[2] >= 50) {
		//this->pos[2] = 0;
		this->living = false;
	}
	return this->living;
};

void Particle::setLiving() {
	this->living = true;
}

void Particle::setTimer(float time) {
	this->emitTimer = time;
}

//sets the new shaping function for an individual particle, called once particle "resets" back to 0 position
void Particle::setFunc(std::list<term>* shapingFunc){
	shapeFunc = *shapingFunc;
};
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
