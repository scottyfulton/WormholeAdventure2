#pragma once
#include "Particle.h"
#include <random>

class Wormhole {
	public:
		Wormhole();
		Wormhole(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei vertexCount, GLsizei particleCount, glm::vec3 pos);
		~Wormhole();

		void update(double time, double dt);
		void render(double alpha);

	private:
		bool isLight;
		const float dTheta = 0.2; //rate of increase in theta for each particle, causes spiraling
		float currTheta, phi, dPhi; //passed in construction of a Particle, designates orientation on circumference of the Wormhole - phi = direction of shaping function
		GLuint texture, shader, vao, numParticles; // simply a reference to the correct vao/vbo to use for each GObject drawn
		GLsizei numVertices;		// when glDrawElements called, pass each object's "texture", "shader", etc. which simply reference the already loaded & bound data
		//Matricies
		glm::mat4 transformationMatrix;
		//pos, vel, acc
		glm::vec3 pos;
		/*glm::vec3 vel;
		glm::vec3 acc;*/

		std::random_device r;
		std::list<term> cone = {{1,2}}; // function to define the initial cone shape of the wormhole
		std::list<term> shaping; //if changed, only passed to a particle when the particle reaches the maximum height of the wormhole (max z)
		std::list<Particle*> particles;

		void setNewShapingFunc(); //rng a new shaping function (always a quadratic function) to give a "new" particle
};