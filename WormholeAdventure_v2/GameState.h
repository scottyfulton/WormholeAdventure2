#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GObject.h"
#include "Wormhole.h"
#include <list>
#include "Camera.h"




class GameState {
public:
	GameState();
	~GameState();

	void init(); //load all the vaos, vbos, things
	void update(double time, double dt); //vaos, vbos updated with new vertex positions
	void render(double alpha);

	void addGObject(GObject* obj);
	void removeGObject(GObject* obj);

	void addCamera(Camera* obj);
	void removeCamera(Camera* obj);

	void addWormhole(Wormhole* obj);
	void removeWormhole(Wormhole* obj);
	

private:
	std::list<Camera*> cameras;
	std::list<GObject*> gObjects;
	std::list<Wormhole*> wormholes;
	
};