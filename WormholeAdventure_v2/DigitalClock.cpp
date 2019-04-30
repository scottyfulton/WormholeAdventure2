#include "DigitalClock.h"

using namespace glm;


DigitalClock::DigitalClock()
{
}

DigitalClock::DigitalClock(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei numVertices, glm::vec3 pos) :
	GObject(shaderID, textureID, vaoID, numVertices, pos, vec3(0.0f, 0.0f, 0.0f))
{
	seconds = minutes = 0;
}


DigitalClock::~DigitalClock()
{
}

void DigitalClock::update(double time, double dt)
{
	seconds = int(time / 1000000000.0);
	minutes = seconds / 60 % 60;	// nmo more than 60 seconds
	seconds = seconds % 60;

}

void DigitalClock::render(double alpha)
{
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
	/*
	//Interpolate
	posI.x = (float) (pos.x + (vel.x * alpha));
	posI.y = (float) (pos.y + (vel.y * alpha));
	posI.z = (float) (pos.z + (vel.z * alpha));
	*/


	//translation
	translateMatrix = glm::mat4(1.0);


	//Transformation
	transformationMatrix = glm::mat4(1.0);
	transformationMatrix = glm::translate(transformationMatrix, pos);

	//Uniform
	glUniform1i(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));

	//Draw
	int a = minutes / 10 % 10;
	glDrawArrays(GL_TRIANGLES, a * 6, 6);

	float dx = 15.0f;
	a = minutes % 10;
	transformationMatrix = glm::translate(transformationMatrix, glm::vec3(dx, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));
	glDrawArrays(GL_TRIANGLES, a * 6, 6);

	a = 10;
	transformationMatrix = glm::translate(transformationMatrix, glm::vec3(dx, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));
	glDrawArrays(GL_TRIANGLES, a * 6, 6);

	a = seconds / 10;
	transformationMatrix = glm::translate(transformationMatrix, glm::vec3(dx, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));
	glDrawArrays(GL_TRIANGLES, a * 6, 6);

	a = seconds % 10;
	transformationMatrix = glm::translate(transformationMatrix, glm::vec3(dx, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, false, glm::value_ptr(transformationMatrix));
	glDrawArrays(GL_TRIANGLES, a * 6, 6);
}

