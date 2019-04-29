#pragma once
#include "Particle.h"
#include "Asteroid.h"


#include <random>

class Wormhole {
	public:
		Wormhole();
		Wormhole(std::vector<GLuint> * shaderID, std::vector<GLuint> * textureID, 
			std::vector<GLuint> * vaoID, std::vector<GLsizei> *vertexCount, 
			GLsizei particleCount, GLsizei asteroidCount, glm::vec3 pos);
		~Wormhole();

		void update(double time, double dt);
		void render(double alpha);
		void setviewMat(glm::mat4 *viewMat);
		float getPhi();
		//std::list<Asteroid*>* getAsteroid(int index);
		std::list<Asteroid*>* getAsteroid();


	private:
		bool isLight;
		const float dTheta = 0.01; //rate of increase in theta for each particle, causes spiraling
		float currTheta, phi, dPhi, ddPhi, particleTimer, asteroidTimer; //passed in construction of a Particle, designates orientation on circumference of the Wormhole - phi = direction of shaping function
		std::vector<GLuint> *textures, *shaders, *vaos;
		GLuint numParticles, numAsteroids; // simply a reference to the correct vao/vbo to use for each GObject drawn
		//GLsizei numVertices;		// when glDrawElements called, pass each object's "texture", "shader", etc. which simply reference the already loaded & bound data
		std::vector<GLsizei> *vertexCounts;
		//Matricies

		glm::mat4 transformationMatrix, viewMat;
		//pos, vel, acc
		glm::vec3 pos;
		/*glm::vec3 vel;
		glm::vec3 acc;*/

		//std::random_device r;
		std::list<term> cone = {{1.0f,2.0f}}; // function to define the initial cone shape of the wormhole
		std::list<term> shaping; //if changed, only passed to a particle when the particle reaches the maximum height of the wormhole (max z)
		std::list<Particle*> particles;
		std::list<Asteroid*> asteroids;
	
		void updateP(float* theta, glm::vec3* objPos, glm::vec3* vel);
		void updateA(float* theta, glm::vec3* objPos, glm::vec3* vel);
};