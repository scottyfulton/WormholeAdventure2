#include "Player.h"

using namespace glm;

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

Player::~Player()
{
	delete this;
}


void Player::update(double time, double dt) { //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
//input cases determine theta&phi for rot in 3d space	
//call gobj update method

	bool boolArr[] = { false, false, false,false };
	std::string inputVal = NULL;
	int inVal = 0;
	//for (int i = 0; i < 4; i++) {
	//	if (boolArr[i] == false)
	//	{
	//		inputVal.push_back('0');
	//	}
	//	else 
	//	{
	//		inputVal.push_back('1');
	//	}
	//}

	for (int i = 0; i < 4; i++)
	{
		if (boolArr[i] == true) 
		{
			inVal += pow(2.0, i);
		}
	}


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
	rotationYMatrix = glm::rotate(rotationYMatrix, (radTemp + valY), glm::vec3(0.0, 1.0, 0.0));
	rotationZMatrix = glm::rotate(rotationZMatrix, (valZ), glm::vec3(0.0, 0.0, 1.0));
	rotationMatrix = rotationZMatrix * rotationYMatrix *rotationXMatrix;

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
