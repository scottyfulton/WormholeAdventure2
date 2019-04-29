#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GObject.h"
#include "Wormhole.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Player.h"
=======
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
#include <list>
#include "Camera.h"
//#include "Include.h"


=======
#include "Player.h"
#include <list>
#include "Camera.h"
//#include "Include.h"
>>>>>>> updated player class with input switch case


class GameState {
public:
	GameState();
	~GameState();

	void init(); //load all the vaos, vbos, things
	void update(double time, double dt, bool arr[4]); //vaos, vbos updated with new vertex positions
	void render(double alpha);

	void addGObject(GObject* obj);
	void removeGObject(GObject* obj);

	void addCamera(Camera* obj);
	void removeCamera(Camera* obj);

	void addWormhole(Wormhole* obj);
	void removeWormhole(Wormhole* obj);
	

<<<<<<< HEAD
	void addPlayer(Player* obj);
	void removePlayer(Player* obj);

	//void addInput(Input* obj);
	//void removeInput(Input* obj);

<<<<<<< HEAD
=======
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
	void addPlayer(Player* obj);
	void removePlayer(Player* obj);

	//void addInput(Input* obj);
	//void removeInput(Input* obj);

>>>>>>> updated player class with input switch case
private:
	bool collisionDetection(Player* obj1, Asteroid* obj2);
<<<<<<< HEAD
<<<<<<< HEAD
	bool isHit;
=======
>>>>>>> Added bilboarding and moved ship closer
=======
	bool isHit;
>>>>>>> KABOOM WORKS!
	std::list<Camera*> cameras;
	std::list<GObject*> gObjects;
	std::list<Wormhole*> wormholes;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	std::list<Player*> players;
=======
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======
	
>>>>>>> Implemented Asteroids
=======
	std::list<Player*> players;
>>>>>>> updated player class with input switch case
};