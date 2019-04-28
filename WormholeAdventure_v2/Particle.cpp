#include "Particle.h"

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, 
					glm::vec3 pos, std::list<term>* baseShape){
<<<<<<< HEAD
=======
Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos){
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======

Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, 
<<<<<<< HEAD
					glm::vec3 pos, float theta, float emitTime, std::list<term>* baseShape){
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.
=======
					glm::vec3 pos, float theta, std::list<term>* baseShape){
>>>>>>> Nick gave a correct implementation to choosing when to update/render a Particle. Particles still not looping back to origin of wormhole to follow the curve of the worhole again (yet).
=======
>>>>>>> This is MUCH closer to the wormhole effect that we wanted in the beginning.
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = numVertices;
	this->pos = pos;
<<<<<<< HEAD
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
<<<<<<< HEAD
<<<<<<< HEAD
	if (this->pos[2] >= 50) {
=======
	if (this->pos[2] >= 85) {
>>>>>>> Updated Asteroids to follow correct path (was matrix order issue in render()), adjusted Player's rotation to face (0, 0, 0), adjust Player's render() for slight optimization, adjusted Player's movement cases, adjust Player's movement calculations to ignore theta in x (not needed, complicates). Slowed down Player's movement. Tweaked hit detection to be more realistic. Added conditions to Player's movement to avoid Player moving off-screen (causes bouncing on edges of screen because of interpolation and friction vector addition).
		this->living = false;
	}
	//std::cout << "z value of particle: " << this->pos[2] << std::endl;
		float z = this->pos[2];
		this->radius = calc(z, baseShape); //pass in z to baseShape function
		this->vel += this->acc;
		this->pos += this->vel;
		this->pos[0] = cos(theta) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
		this->pos[1] = sin(theta) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
		this->pos[0] += cos(phi) * sin(z/12.75) * 30 * z; //shift of x
		this->pos[1] += sin(phi) * sin(z/12.75) * 30 * z; //shift of y
		this->theta += dTheta;
};

void Particle::render(glm::mat4 *viewMat, float dTheta, float phi, double alpha){	
	//Interpolate
	this->posI = pos + vel*(float)alpha;
	this->thetaI = theta + dTheta * (float)alpha;

	transformationMatrix = glm::translate(glm::mat4(1.0), posI);
	transformationMatrix *= getBillboardMat(viewMat);
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(10, 10, 10));
	//multiplying by the transpose of the view matrix of Camera to counteract skewing caused by persepective
	//transformationMatrix *= *viewMat;
	
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
	this->vel = glm::vec3(0, 0, 0.01);
	this->acc = glm::vec3(0, 0, 0.00015);
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
<<<<<<< HEAD
=======
Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos){};
=======
	this->vel = glm::vec3(0.1,0.2,0.2);
};

>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
Particle::~Particle(){};
=======
	this->vel = glm::vec3(0,0,0.02);
=======
>>>>>>> This is MUCH closer to the wormhole effect that we wanted in the beginning.
	this->baseShape = baseShape;
	this->theta = theta;
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
<<<<<<< HEAD
	if (this->pos[2] >= 150) {
=======
	if (this->pos[0] >= 150) {
>>>>>>> Updated wormhole to perform position calculations for each Particle/Asteroid. Made shaping function an even amplitude throughout. Sped up Asteroids. Asteroids STILL follow a DIFFERENT path than Particles for SOME UNGODLY REASON.
=======
	if (this->pos[2] >= 50) {
>>>>>>> Changed phi value for moving player left (case 2) to 90 & commented the z-coordinate update for the player (shouldn't move in the z anyways). Weird result.
		this->living = false;
	}
	//std::cout << "z value of particle: " << this->pos[2] << std::endl;
		//float z = this->pos[0];
		//this->radius = calc(z, baseShape); //pass in z to baseShape function
		//radius > 80 ? radius = 80 : NULL;//limit on spread

		//this->vel += this->acc;
		//this->pos += this->vel;
		//this->pos[2] = cos(theta) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
		//this->pos[1] = sin(theta) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
		//this->pos[2] += cos(phi) * sin(z) * 5; //shift of x
		//this->pos[1] += sin(phi) * sin(z) * 5; //shift of y
		//
		//
		/*this->theta += dTheta;*/
};


void Particle::render(glm::mat4 *viewMat, float dTheta, float phi, double alpha) {
	//Interpolate
	this->posI = pos + vel * (float)alpha;
	this->thetaI = theta + dTheta * (float)alpha;

	transformationMatrix = glm::translate(glm::mat4(1.0), posI);
	transformationMatrix *= getBillboardMat(viewMat);
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(0.5, 0.5, 0.5));
	
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

void Particle::reset(float particleCount) {
	this->pos[2] = 0;
	this->vel = glm::vec3(0, 0, 0.1);
	this->acc = glm::vec3(0, 0, 0.75);
	this->setTheta(((float)360 / particleCount) * (std::rand() / (float(RAND_MAX) / 360.0f)));
	this->setLiving();
}

//always passed the z value of a Particle
//float Particle::calc(float val, std::list<term>* function) {
//	float sum = 0;
//	for (term t : *function)
//		sum += t.coeff * pow(val, t.exponent); 
//
//	return sum; //sum = f(z) now
//};

//for Wormhole to check if the particle should be rendered
bool Particle::isAlive(){
	return this->living;
};

glm::vec3* Particle::getPosition() { return &(this->pos); }
glm::vec3* Particle::getVelocity() { return &(this->vel); }
float* Particle::getTheta() { return &theta; }


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
<<<<<<< HEAD
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
=======
>>>>>>> Added bilboarding and moved ship closer

glm::mat4 Particle::getBillboardMat(glm::mat4* viewMat) {
	glm::mat4 billboardMat(1.0);
	billboardMat[0][0] = (*viewMat)[0][0];
	billboardMat[0][1] = (*viewMat)[1][0];
	billboardMat[0][2] = (*viewMat)[2][0];
	billboardMat[1][0] = (*viewMat)[0][1];
	billboardMat[1][1] = (*viewMat)[1][1];
	billboardMat[1][2] = (*viewMat)[2][1];
	billboardMat[2][0] = (*viewMat)[0][2];
	billboardMat[2][1] = (*viewMat)[1][2];
	billboardMat[2][2] = (*viewMat)[2][2];
<<<<<<< HEAD
	
	return billboardMat;
}
>>>>>>> messed with the camera to rotate it to look down the wormhole. buggy. bugs buggy.
=======

	return billboardMat;
}
>>>>>>> Added bilboarding and moved ship closer
