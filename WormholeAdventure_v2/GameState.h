#pragma once
// Include GLEW
#include <GL/glew.h>
//#include <GL/glut.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>
// to scale
//#include <glm/gtc/matrix_transform.hpp> 
//#include "common\shader.hpp"
//#include "common\controls.hpp"
//#include "common/objloader.hpp"
#include "GObject.h"
#include "Wormhole.h"
#include "Player.h"
#include <list>
#include "Camera.h"
//#include "Include.h"

//for audio 
#include <irrKlang.h>
using namespace irrklang;
#include <ik_ISound.h>


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

	void addPlayer(Player* obj);
	void removePlayer(Player* obj);

	//void addInput(Input* obj);
	//void removeInput(Input* obj);

private:
	bool collisionDetection(Player* obj1, Asteroid* obj2);
	bool isHit;
	std::list<Camera*> cameras;
	std::list<GObject*> gObjects;
	std::list<Wormhole*> wormholes;
	std::list<Player*> players;

	//Audio Engine
	ISoundEngine* engine;
	ISound* soundWalking;
};