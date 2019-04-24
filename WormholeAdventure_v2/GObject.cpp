#pragma once
#include "GObject.h"








using namespace glm;
/*
** Each GObject's light sources should be obtained by looping through every object, determining if a GObject is a light,
** then sorting (binarySort) for the 10 closest light sources
*/

GObject *obj; 
 

GObject::GObject(){}; // implicitly called when child classes are constructed
GObject::GObject(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos) {
	this->shader = shaderID;
	this->texture = textureID;
	this->vao = vaoID;
	this->numVertices = numVertices;
	this->pos = pos;
	
	
	
	

};

GObject::~GObject() {


}

void GObject::update( double time, double dt) { //manipulates position data (particles follow wormhole, ship moves in xy-plane, asteroids follow path inside wormhole)
	

	
	
};

void GObject::render(double alpha){

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


	//Transformation
	transformationMatrix = glm::mat4(1.0);
	transformationMatrix = glm::translate(transformationMatrix, pos);

	//Uniform
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

}
