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
		float z = this->pos[2];
		this->radius = calc(z-2, baseShape); //pass in z to baseShape function
		this->vel += this->acc;
		this->pos += this->vel;
		this->pos[0] = cos(theta) * radius; //ensure x and y coordinates of each particle are on circumference of Wormhole on each z plane,
		this->pos[1] = sin(theta) * radius; // multiplied by cos & sin of phi to implement shaping direction phi
		this->pos[0] += cos(phi) * sin(z/12.75) * 30 * z; //shift of x
		this->pos[1] += sin(phi) * sin(z/12.75) * 30 * z; //shift of y
		this->theta += dTheta;
};

void Particle::render(glm::mat4 *viewMatInv, float dTheta, float phi, double alpha){	
	//Interpolate
	this->posI = pos + vel*(float)alpha;
	this->thetaI = theta + dTheta * (float)alpha;

	//transformationMatrix = glm::scale(transformationMatrix, glm::vec3(0.5, 0.5, 0.5));
	transformationMatrix = glm::translate(glm::mat4(1.0), posI);
	//multiplying by the transpose of the view matrix of Camera to counteract skewing caused by persepective
	transformationMatrix *= *viewMatInv; //won't work if camera's view matrix is adjusted
	
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
