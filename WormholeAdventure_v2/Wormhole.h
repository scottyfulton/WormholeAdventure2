#pragma once
#include "Particle.h"
#include "Term.h"
#include <list>

class Wormhole {
	public:
		Wormhole();
		Wormhole(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei vertexCount, GLsizei particleCount, glm::vec3 pos);
		~Wormhole();

		void update(double time, double dt);
		void render(double alpha);

	private:
		bool isLight;
		GLuint texture, shader, vao; // simply a reference to the correct vao/vbo to use for each GObject drawn
		GLsizei numVertices;		// when glDrawElements called, pass each object's "texture", "shader", etc. which simply reference the already loaded & bound data
		//Matricies
		glm::mat4 transformationMatrix;
		//pos, vel, acc
		glm::vec3 pos;
		/*glm::vec3 vel;
		glm::vec3 acc;*/

		const std::list<term> cone; // function to define the initial cone shape of the wormhole
		std::list<term> shaping; //if changed, only passed to a particle when the particle reaches the maximum height of the wormhole (max z)
		std::list<Particle*> particles;

		void setNewShapingFunc(); //rng a new shaping function (always a quadratic function) to give a "new" particle
};