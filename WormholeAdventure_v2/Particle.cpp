#include "Particle.h"


Particle::Particle(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, 
					glm::vec3 pos, std::list<term>* baseShape){
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

Particle::~Particle(){
	delete this;
};

//z increments by velocity of a particle
//x and y increment based on radius (pos[0], pos[1], pos[2]) = (x, y, z)
//radius increments based on predefined function of z
void Particle::update(float dTheta, float phi, double time, double dt){
	if (this->pos[2] >= 50) {
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
	
	//Setting Uniform Value
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glDisable(GL_BLEND); //other textures aren't transparent and don't have an alpha value (0)
};

void Particle::reset(float particleCount) {
	this->pos[0] = 0;
	this->vel = glm::vec3(0, 0, 0.1);
	this->acc = glm::vec3(0, 0, 0.045);
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

	return billboardMat;
}
