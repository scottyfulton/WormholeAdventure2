#pragma once
#include "Particle.h"
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include "Asteroid.h"


#include <random>
=======
#include "Term.h"
#include <list>
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
=======
#include "Asteroid.h"


>>>>>>> Implemented Asteroids
#include <random>
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.

class Wormhole {
	public:
		Wormhole();
<<<<<<< HEAD
<<<<<<< HEAD
		Wormhole(std::vector<GLuint> * shaderID, std::vector<GLuint> * textureID, 
			std::vector<GLuint> * vaoID, std::vector<GLsizei> *vertexCount, 
			GLsizei particleCount, GLsizei asteroidCount, glm::vec3 pos);
=======
		Wormhole(GLuint shaderID, GLuint textureID, GLuint vaoID, GLsizei vertexCount, GLsizei particleCount, glm::vec3 pos);
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
		Wormhole(std::vector<GLuint> * shaderID, std::vector<GLuint> * textureID, std::vector<GLuint> * vaoID, std::vector<GLsizei> *vertexCount, GLsizei particleCount, GLsizei asteroidCount, glm::vec3 pos);
>>>>>>> Implemented Asteroids
		~Wormhole();

		void update(double time, double dt);
		void render(double alpha);
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
		void setviewMat(glm::mat4 *viewMat);
		float getPhi();
>>>>>>> Updated Camera to adjust its position to move with the center of the wormhole. Updated Particles & Asteroids to not use the transpose of the Camera's view matrix & directly use the Camera's view matrix (passed to each Particle/Asteroid). Got keyboard input working how we want with Blane.

	private:
		bool isLight;
		const float dTheta = 0.01; //rate of increase in theta for each particle, causes spiraling
		float currTheta, phi, dPhi, ddPhi, particleTimer, asteroidTimer; //passed in construction of a Particle, designates orientation on circumference of the Wormhole - phi = direction of shaping function
		std::vector<GLuint> *textures, *shaders, *vaos;
		GLuint numParticles, numAsteroids; // simply a reference to the correct vao/vbo to use for each GObject drawn
		//GLsizei numVertices;		// when glDrawElements called, pass each object's "texture", "shader", etc. which simply reference the already loaded & bound data
		std::vector<GLsizei> *vertexCounts;
		//Matricies

<<<<<<< HEAD
<<<<<<< HEAD
		glm::mat4 transformationMatrix;
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
		glm::mat4 transformationMatrix, viewMatTransposed = glm::transpose(glm::mat4(1.0));
>>>>>>> Changed particles to not spiral so they are easier to see when looking directly down the z axis. Might change back once the camera is looking down the curve of the Wormhole rather than at its base.
=======
		glm::mat4 transformationMatrix, viewMat;
>>>>>>> Updated Camera to adjust its position to move with the center of the wormhole. Updated Particles & Asteroids to not use the transpose of the Camera's view matrix & directly use the Camera's view matrix (passed to each Particle/Asteroid). Got keyboard input working how we want with Blane.
		//pos, vel, acc
		glm::vec3 pos;
		/*glm::vec3 vel;
		glm::vec3 acc;*/

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		//std::random_device r;
		std::list<term> cone = {{1.0f,2.0f}}; // function to define the initial cone shape of the wormhole
		std::list<term> shaping; //if changed, only passed to a particle when the particle reaches the maximum height of the wormhole (max z)
		std::list<Particle*> particles;
		std::list<Asteroid*> asteroids;
	
		void updateP(float* theta, glm::vec3* objPos, glm::vec3* vel);
		void updateA(float* theta, glm::vec3* objPos, glm::vec3* vel);
=======
		const std::list<term> cone; // function to define the initial cone shape of the wormhole
=======
		std::random_device r;
=======
		//std::random_device r;
>>>>>>> This is MUCH closer to the wormhole effect that we wanted in the beginning.
		std::list<term> cone = {{1,2}}; // function to define the initial cone shape of the wormhole
>>>>>>> Added emit timers to particles based on RNG. Problem: Particle's isAlive() either doesn't perform proper status check or use of isAlive() in Wormhole class is improper/invalid. Movement of more than one "ring" of Particle's solely dependent on RNG - not the intent of the logic.
		std::list<term> shaping; //if changed, only passed to a particle when the particle reaches the maximum height of the wormhole (max z)
		std::list<Particle*> particles;
		std::list<Asteroid*> asteroids;

	

<<<<<<< HEAD
		void setNewShapingFunc(); //rng a new shaping function (always a quadratic function) to give a "new" particle
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
		//void setNewShapingFunc(); //rng a new shaping function (always a quadratic function) to give a "new" particle
>>>>>>> This is MUCH closer to the wormhole effect that we wanted in the beginning.
};