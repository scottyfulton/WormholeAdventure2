#include "Player.h"

using namespace glm;

Player::Player() {};
Player::Player(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, 
	glm::vec3 pos, glm::vec3 rotate)
{
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = numVertices;
	this->pos = pos;
	this->rot = rotate;
	//this->valY;
	this->vel = glm::vec3(0.0f);
	this->acc = glm::vec3(0.0f);
	this->phi = 90.0f;
	this->theta = 0.0f;
	this->movFriction = 0.1f;
	this->force = 0.0f;
	this->mass = 50.0f;
	   
	//initialize new gobj on heap -> pass ids to constr
	};

Player::~Player()
{
	delete this;
}

void Player::update(double time, double dt, bool arr[4]) { //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
//input cases determine theta&phi for rot in 3d space	

	//bool boolArr[] = { false, false, false,false };
	bool *boolArr = arr;
	int inVal = 0;
	
	/*this places values for:
	Up Left Down Right
	U = 2^0
	L = 2^1
	D = 2^2
	R = 2^3
	adds values to inVal and bases cases off values for */	
	for (int i = 0; i < 4; i++)
	{
		if (boolArr[i] == true)
		{
			inVal += pow(2.0, i);
		}
	}

	//std::cout << "Up: " << boolArr[0] << "Left: " << boolArr[1] << "Down: " << boolArr[2] << "Right: " << boolArr[3] << std::endl;
	//vars for adding velocity, to update all cases
	float zero = 0.0;
	float incr = 0.1;

	//phi in horizontal axis
	//theta in vertical axis
	//sin(theta)*cos(phi) for x
	//sin(theta) for y

	switch (inVal)
	{
		case 0:					//nothing;      
			//acc.x =  zero;
			//acc.y =  zero;
			force = zero;
			acc[0] =  zero;
			break;
		case 1:					//U
			/*acc.y =  incr;*/ 
			phi = 90.0f;
			theta = 90.0f;
			force = incr;
			break;
		case 2:				 //L
			//acc.x = -incr;
			phi = 180.0f;		//using phi as dir instead or pos/neg
			theta = 180.0f;
			force = incr;
			break;
		case 3: 
			//acc.y =  incr; //U
			//acc.x = -incr; //L
			phi = 180.0f;
			theta = 90.0f;
			force = incr;
			break;
		case 4:
			//acc.y = -incr; //D
			phi = 90.0f;
			theta = -90.0f;
			force = incr;
			break;
		case 5:
			//acc.y =  zero; //UD
			force = zero;
			phi = 90.0f;
			theta = 0.0f;
			break;
		case 6: 
			//acc.x = -incr; //L
			//acc.y = -incr; //D
			phi = 180.0f;
			theta = -90.0f;
			break;
		case 7:
			//acc.x = -incr; //L
			//acc.y =  zero; //UD
			phi = 180.0f;		
			theta = 0.0f;
			force = incr;
			break;
		case 8:
			//acc.x =  incr; //R
			phi = 0.0f;
			theta = 0.0f;
			force = incr;
			break;
		case 9:
			//acc.x =  incr; //R
			//acc.y =  incr; //U
			phi = 0.0f;
			theta = 90.0f;
			break;
		case 10:
			//acc.x =  zero; //LR
			force = zero;
			phi = 90.0f;
			theta = 0.0f;
			break;
		case 11:
			//acc.x =  zero; //LR 
			//acc.y =  incr; //U
			phi = 90.0f;
			theta = 90.0f;
			force = incr;
			break;
		case 12:
			//acc.x =  incr; //R
			//acc.y = -incr; //D
			phi = 0.0f;
			theta = -90.0f;
			force = incr;
			break;
		case 13:
			//acc.x =  incr; //R
			//acc.y =  zero; //DU
			phi = 0.0f;
			theta = 0.0f;
			force = incr;
			break;
		case 14:
			//acc.x =  zero; //LR
			//acc.y = -incr; //D
			theta = -90.0f;
			phi = 90.0f;
			force = incr;
			break;
		case 15:
			//acc.x =  incr; //LR
			//acc.y =  zero; //UD
			force = zero;
			phi = 90.0f;
			theta = 0.0f;
			break;

		default:
			break;
	}
	resetNetForce();
	addForce(force, theta, phi);
	addForceVec(-vel.x * movFriction, -vel.y * movFriction, -vel.z * movFriction);

	acc.x = netForce.x / mass;
	acc.y = netForce.y / mass;
	acc.z = netForce.z / mass;
	vel.x = vel.x + acc.x;
	vel.y = vel.y + acc.y;
	vel.z = vel.z + acc.z;
	if((pos.x + vel.x) <= 7.3 && (pos.x + vel.x) >= -7.3)
		pos.x = pos.x + vel.x;
	if((pos.y + vel.y) <= 6.0 && (pos.y + vel.y) >= -6.0)
		pos.y = pos.y + vel.y;
	//pos.z = pos.z + vel.z;
	//std::cout << pos.x << " " << pos.y << " " << pos.z << " " << std::endl;
};

void Player::render(double alpha) {

	//call gobj render(alpha)
	//Shader
	glUseProgram(shader);
	//VAO
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_DEPTH_TEST);
	//Interpolate
	posI[0] = pos[0] + vel[0] * alpha;
	posI[1] = pos[1] + vel[1] * alpha;
	posI[2] = pos[2] + vel[2] * alpha;

	valX = rot[0];
	valY = rot[1];
	valZ = rot[2];
	
	transformationMatrix = glm::mat4(1.0);
	//rotationMatrix = glm::mat4(1.0);
	//rotationXMatrix = glm::mat4(1.0);
	//rotationYMatrix = glm::mat4(1.0);
	//rotationZMatrix = glm::mat4(1.0);
	//scaleMatrix = glm::mat4(1.0);

	//rotationXMatrix = glm::rotate(rotationXMatrix, (valX), glm::vec3(1.0, 0.0, 0.0));
	//rotationYMatrix = glm::rotate(rotationYMatrix, (valY+glm::radians(30.0f)) , glm::vec3(0.0, 1.0, 0.0)); // (1.57f/2.0f)
	//rotationZMatrix = glm::rotate(rotationZMatrix, (valZ), glm::vec3(0.0, 0.0, 1.0));
	//rotationMatrix = rotationZMatrix * rotationYMatrix *rotationXMatrix;
	//rotationMatrix =  rotationXMatrix* rotationYMatrix *rotationZMatrix;
	//transformationMatrix = translationMatrix * rotationMatrix; //commented for testing optimizations

	//this->pos[0] += cos(phi) * sin(z / 12.75) * 30 * z; //shift of x
	//this->pos[1] += sin(phi) * sin(z / 12.75) * 30 * z; //shift of y
	translationMatrix = glm::translate(transformationMatrix, posI);
	transformationMatrix = glm::rotate(translationMatrix, valY + glm::radians(30.0f), glm::vec3(0, 1, 0));
	//transformationMatrix = glm::rotate(transformationMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(0.1));
	//transformationMatrix = scaleMatrix * rotationMatrix *  translationMatrix;

	//Uniform
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void Player::addForce(float force, float theta, float phi) {
	theta = (float) glm::radians(theta);
	phi = (float)glm::radians(phi);
	
	netForce.x = (float)(netForce.x + (force * cos(phi)));
	netForce.y = (float)(netForce.y + (force * sin(theta)));
	netForce.z = (float)(netForce.z + (force * sin(theta)*cos(phi)));
}

void Player::addForceVec(float x, float y, float z) {

	netForce.x = netForce.x + x;
	netForce.y = netForce.y + y;
	netForce.z = netForce.z + z;
}

void Player::resetNetForce() {
	netForce.x = 0.0f;
	netForce.y = 0.0f;
	netForce.z = 0.0f;
}

glm::vec3 Player::getPosition()
{
	return this->pos;
}