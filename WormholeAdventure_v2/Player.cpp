#include "Player.h"

using namespace glm;

<<<<<<< HEAD
Player::Player() {};
Player::Player(std::vector<GLuint> * shaderID, std::vector<GLuint> *textureID,
	std::vector<GLuint> *vaoID, std::vector<GLsizei> *vertexCount,
	glm::vec3 pos, glm::vec3 rotate)
{
	this->shaders = shaderID;
	this->textures = textureID;
	this->vaos = vaoID;
	this->numVertices = (*vertexCount)[0];
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
=======
//typedef enum
//{
//	L = 0100,
//	LF = 1100,
//	LB = 0110,
//	LR = 0101,
//
//	R = 0001,
//	RB = 0011,
//	RF = 1010,
//	RL = 0101,
//
//	F = 1000,
//	FB = 1010,
//	FR = 1001,
//	FL = 1100,
//
//	B = 0010,
//	BR = 0011,
//	BL = 0110,
//	BF = 1010
//
//} inputValues;



//		F L B R


Player::Player() {};
Player::Player(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos, glm::vec3 rotate)
{
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = numVertices;
	this->pos = pos;
	this->rot = rotate;



	//initialize new gobj on heap -> pass ids to constr

};
>>>>>>> updated player class with input switch case

Player::~Player()
{
	delete this;
}

<<<<<<< HEAD
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
=======

void Player::update(double time, double dt) { //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
//input cases determine theta&phi for rot in 3d space	
//call gobj update method

	bool boolArr[] = { false, false, false,false };
	int inVal = 0;

	for (int i = 0; i < 4; i++)
	{
		if (boolArr[i] == true) 
>>>>>>> updated player class with input switch case
		{
			inVal += pow(2.0, i);
		}
	}

<<<<<<< HEAD
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
	//if ((pos.x + vel.x) <= 6.3 && (pos.x + vel.x) >= -6.3)
		pos.x = pos.x + vel.x;
	if ((pos.y + vel.y) <= 6.0 && (pos.y + vel.y) >= -6.0)
	//if((pos.y + vel.y) <= 5.0 && (pos.y + vel.y) >= -5.0)
		pos.y = pos.y + vel.y;
	//pos.z = pos.z + vel.z;
	//std::cout << pos.x << " " << pos.y << " " << pos.z << " " << std::endl;
};

void Player::render(double alpha, bool isHit) {


	//call gobj render(alpha)
	//Shader
	
	//posI.x = pos.x + vel.x* alpha;
	//posI.y = pos.y + vel.y* alpha;
	//posI.z = pos.z + vel.z * alpha;
		glUseProgram((*shaders)[0]);
	if (!isHit) 
	{
	////	//VAO for ship
		//glUseProgram((*shaders)[0]);
		//glBindVertexArray((*vaos)[0]);
		glBindVertexArray((*vaos)[0]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		//Texture
		glActiveTexture(GL_TEXTURE0);
		/*glBindTexture(GL_TEXTURE_2D, (*textures)[0]);*/
		glBindTexture(GL_TEXTURE_2D, (*textures)[0]);
		glEnable(GL_DEPTH_TEST);
		//Uniform
		//glUniform1i((*textures)[0], 0);
		glUniform1i((*textures)[0], 0);
		//Interpolate
		//posI[0] = pos[0] + vel[0] * alpha;
		if ((pos.x + vel.x * alpha) <= 6.3 && (pos.x + vel.x * alpha) >= -6.3)
			posI.x = pos.x + vel.x* alpha;
		//posI[1] = pos[1] + vel[1] * alpha;
		if ((pos.y + vel.y* alpha) <= 5.0 && (pos.y + vel.y* alpha) >= -5.0)
			posI.y = pos.y + vel.y* alpha;
		//posI[2] = pos[2] + vel[2] * alpha;

		valX = rot[0];
		valY = rot[1];
		valZ = rot[2];

		transformationMatrix = glm::mat4(1.0);

		transformationMatrix = glm::translate(transformationMatrix, pos);
		transformationMatrix = glm::rotate(transformationMatrix,
			valY + glm::radians(30.0f), glm::vec3(0, 1, 0));
		transformationMatrix = glm::scale(transformationMatrix, glm::vec3(0.1));


		glUniformMatrix4fv(glGetUniformLocation((*shaders)[0], "transformationMatrix"),
			1, false, glm::value_ptr(transformationMatrix));

		//Draw
		glDrawArrays(GL_TRIANGLES, 0, numVertices);

	}else 
	{

		glBindVertexArray((*vaos)[1]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		//Texture
		glActiveTexture(GL_TEXTURE0);
		/*glBindTexture(GL_TEXTURE_2D, (*textures)[0]);*/
		glBindTexture(GL_TEXTURE_2D, (*textures)[3]);
		glEnable(GL_DEPTH_TEST);
		//Uniform
		//glUniform1i((*textures)[0], 0);
		glUniform1i((*textures)[3], 0);
		//Interpolate
		//posI[0] = pos[0] + vel[0] * alpha;
		if ((pos.x + vel.x * alpha) <= 6.3 && (pos.x + vel.x * alpha) >= -6.3)
			posI.x = pos.x + vel.x* alpha;
		//posI[1] = pos[1] + vel[1] * alpha;
		if ((pos.y + vel.y* alpha) <= 5.0 && (pos.y + vel.y* alpha) >= -5.0)
			posI.y = pos.y + vel.y* alpha;
		//posI[2] = pos[2] + vel[2] * alpha;

		valX = rot[0];
		valY = rot[1];
		valZ = rot[2];

		transformationMatrix = glm::mat4(1.0);

		transformationMatrix = glm::translate(transformationMatrix, pos);
		//transformationMatrix = glm::rotate(translationMatrix,
		//	valY + glm::radians(30.0f), glm::vec3(0, 1, 0));
		transformationMatrix = glm::scale(transformationMatrix, glm::vec3(3.0f));


		glUniformMatrix4fv(glGetUniformLocation((*shaders)[0], "transformationMatrix"),
			1, false, glm::value_ptr(transformationMatrix));

		//Draw
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//VAO for kaboom/particle
		/*glUseProgram((*shaders)[0]);*/

		//glBindVertexArray((*vaos)[0]);
		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);

		//glBindVertexArray((*vaos)[1]);
		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);
		////Texture
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, (*textures)[3]);
		//glEnable(GL_DEPTH_TEST);
		////Uniform
		//glUniform1i((*textures)[3], 0);
		//isHit = false;
		//////Interpolate
		////posI[0] = pos[0] + vel[0] * alpha;
		////if ((pos.x + vel.x * alpha) <= 6.3 && (pos.x + vel.x * alpha) >= -6.3)
		//	//posI.x = pos.x + vel.x;
		////posI[1] = pos[1] + vel[1] * alpha;
		////if ((pos.y + vel.y* alpha) <= 5.0 && (pos.y + vel.y* alpha) >= -5.0)
		//	//posI.y = pos.y + vel.y;
		////posI[2] = pos[2] + vel[2] * alpha;

		////valX = rot[0];
		////valY = rot[1];
		////valZ = rot[2];

		////setviewMat(&viewMat);

		//transformationMatrix = glm::mat4(1.0);
		////transformationMatrix *= getBillboardMat(&viewMat);
		////transformationMatrix = glm::translate(transformationMatrix, glm::vec3(pos.x, pos.y, 300.0f)); //mock pos
		//transformationMatrix = glm::scale(transformationMatrix, glm::vec3(50.0f));
		//transformationMatrix = glm::translate(transformationMatrix, pos); //mock pos


		////transformationMatrix = glm::rotate(translationMatrix,
		////	valY + glm::radians(30.0f), glm::vec3(0, 0, 0));


		//glUniformMatrix4fv(glGetUniformLocation((*shaders)[0], "transformationMatrix"),
		//	1, false, glm::value_ptr(transformationMatrix));

		////Draw
		//glDrawArrays(GL_TRIANGLES, 0, 6);

	}
	

}

void Player::addForce(float force, float theta, float phi) {
	theta = (float) glm::radians(theta);
	phi = (float)glm::radians(phi);
	
	netForce.x = (float)(netForce.x + (force * cos(phi)));
	netForce.y = (float)(netForce.y + (force * sin(theta)));
	//netForce.z = (float)(netForce.z + (force * sin(theta)*cos(phi)));
}

void Player::addForceVec(float x, float y, float z) {

	netForce.x = netForce.x + x;
	netForce.y = netForce.y + y;
	//netForce.z = netForce.z + z;
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
glm::mat4 Player::getBillboardMat(glm::mat4* viewMat) {
	glm::mat4 billboardMat(1.0);
	//billboardMat[0][0] = (viewMat)[0][0];
	//billboardMat[0][1] = (viewMat)[1][0];
	//billboardMat[0][2] = (viewMat)[2][0];
	//billboardMat[1][0] = (viewMat)[0][1];
	//billboardMat[1][1] = (viewMat)[1][1];
	//billboardMat[1][2] = (viewMat)[2][1];
	//billboardMat[2][0] = (viewMat)[0][2];
	//billboardMat[2][1] = (viewMat)[1][2];
	//billboardMat[2][2] = (viewMat)[2][2];


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

void Player::setviewMat(glm::mat4 *viewMat) {
	this->viewMat = *viewMat;
};
=======

	float zero = 0.0;
	float incr = 0.1;
	switch (inVal)
	{
	case 0://nothing;
		acc[0] = zero;
		acc[1] = zero;
		acc[1] = zero;
	case 1:
		acc[1] = incr; //U
	case 2:
		acc[0] = -incr; //L
	case 3: 
		acc[1] = incr; //U
		acc[0] = -incr; //L
	case 4:
		acc[1] = -incr; //D
	case 5:
		acc[1] = zero; //UD
	case 6: 
		acc[0] = -incr; //L
		acc[1] = -incr; //D
	case 7:
		acc[0] = -incr; //L
		acc[1] = zero; //UD
	case 8:
		acc[0] = incr; //R
	case 9:
		acc[0] = incr; //R
		acc[1] = incr; //U
	case 10:
		acc[0] = zero; //LR
	case 11:
		acc[0] = zero; //LR 
		acc[1] = incr; //U
	case 12:
		acc[0] = incr; //R
		acc[1] = -incr; //D
	case 13:
		acc[0] = incr; //R
		acc[1] = zero; //DU
	case 14:
		acc[0] = zero; //LR
		acc[1] = -incr; //D
	case 15:
		acc[0] = incr; //LR
		acc[1] = zero; //UD

	default:
		break;
	}



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
	valX = rot[0];
	valY = rot[1];
	valZ = rot[2];
	
	//+= radTemp;

	transformationMatrix = glm::mat4(1.0);
	rotationMatrix = glm::mat4(1.0);


	rotationXMatrix = glm::mat4(1.0);
	rotationYMatrix = glm::mat4(1.0);
	rotationZMatrix = glm::mat4(1.0);
	rotationXMatrix = glm::rotate(rotationXMatrix, (valX), glm::vec3(1.0, 0.0, 0.0));
	rotationYMatrix = glm::rotate(rotationYMatrix, (1.57f/2.0f), glm::vec3(0.0, 1.0, 0.0));
	rotationZMatrix = glm::rotate(rotationZMatrix, (valZ), glm::vec3(0.0, 0.0, 1.0));
	//rotationMatrix = rotationZMatrix * rotationYMatrix *rotationXMatrix;
	rotationMatrix =  rotationXMatrix* rotationYMatrix *rotationZMatrix;

	valX = pos[0];
	valY = pos[1];
	valZ = pos[2];

	//this->pos[0] += cos(phi) * sin(z / 12.75) * 30 * z; //shift of x
	//this->pos[1] += sin(phi) * sin(z / 12.75) * 30 * z; //shift of y
	translationMatrix = glm::translate(transformationMatrix, pos);

	scaleMatrix = glm::mat4(1.0);
	scaleMatrix = glm::scale(rotationMatrix, glm::vec3(4.0f));

	/*transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;*/
	transformationMatrix = scaleMatrix * rotationMatrix * translationMatrix;


	//chekc camera class for correct order of multiply


	//Uniform
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);


};
>>>>>>> updated player class with input switch case
