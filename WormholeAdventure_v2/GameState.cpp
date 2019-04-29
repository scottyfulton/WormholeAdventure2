#pragma once
#include "GameState.h"

GameState::GameState()
{
	isHit = false;
	// Start the sound engine with default parameters
	engine = createIrrKlangDevice();

	if (!engine) {
		// Error starting up the engine
		printf("Failed to initialize Sound Engine!\n");
		exit(0);
	}
	
	soundWalking = engine->play2D("Resources/Audio/Never_Gonna_Give_You_Up.mp3", 
		true, false, true, ESM_AUTO_DETECT, false);
	soundWalking->setPlaybackSpeed(0.0);
	soundWalking->setVolume(0.4f);
}

GameState::~GameState()
{
	for (Camera* c : cameras) {
		c->~Camera();
		//cameras.remove(c);
	}

	for (Player* p : players) {
		p->~Player();
		//players.remove(p);
	}

	for (GObject* g : gObjects) {
		g->~GObject();
		//gObjects.remove(g);
	}

	for (Wormhole* w : wormholes) {
		w->~Wormhole();
		//wormholes.remove(w);
	}
	delete this;
}

void GameState::init()
{
	wormholes.push_back(new Wormhole());
}

void GameState::update(double time, double dt, bool arr[4])
{
	float currPhi = wormholes.front()->getPhi();
	glm::mat4* view = (cameras.front())->getView();
	for (Camera* c : cameras)
		c->update(currPhi, time, dt);

	for (Player* p : players) {
		p->setviewMat(view);
		p->update(time, dt, arr, isHit);
	}

	for (GObject* g : gObjects)
		g->update(time, dt);

	for (Wormhole* w : wormholes) {
		w->setviewMat(view);
		w->update(time, dt);
	}


	if (time > 0) {
		//Collision Detection
		for (Player* p : players)
		{
			//For each astroid calculate collision with ship
			for (Wormhole* w : wormholes) {
				std::list<Asteroid*>* aList = w->getAsteroid();
				for (Asteroid* a : *aList) {
					if (collisionDetection(p, a))
					{
						//Collision - Ship hit Astroid	
						//boom game over
						engine->play2D("Resources/Audio/Explosion+7.mp3");
						soundWalking->setPlaybackSpeed(0.0);
						soundWalking->setVolume(0.7f);
						isHit = true;
					}
				}
			}
		}
	}
}

void GameState::render(double alpha)
{
	for (Camera* c : cameras)
		c->render(alpha);

	for (Player* p : players)
		p->render(alpha, isHit);
	
	//Objects
	for (GObject* g : gObjects)
		g->render(alpha);

	for (Wormhole* w : wormholes)
		w->render(alpha);
}

void GameState::addGObject(GObject* obj)
{
	gObjects.push_back(obj);
}

void GameState::removeGObject(GObject* obj)
{
	gObjects.remove(obj);
}

void GameState::addWormhole(Wormhole* obj){
	wormholes.push_back(obj);
}

void GameState::removeWormhole(Wormhole* obj) {
	wormholes.remove(obj);
}

void GameState::addCamera(Camera* obj)
{
	cameras.push_back(obj);
}

void GameState::removeCamera(Camera* obj)
{
	cameras.remove(obj);
}

void GameState::addPlayer(Player* obj)
{
	players.push_back(obj);
}
void GameState::removePlayer(Player* obj)
{
	players.remove(obj);
}

//Player needs getPos and Asteroid needs get postion
bool GameState::collisionDetection(Player* obj1, Asteroid* obj2)
{
	//Extract Positions from player and asteroid
	glm::vec3 pos1 = obj1->getPosition();
	glm::vec3 pos2 = *(obj2->getPosition());

	//Calculate Distance
	float distance = sqrt(pow(pos2.x - pos1.x, 2.0f) + pow(pos2.y - pos1.y, 2.0f) + pow(pos2.z - pos1.z, 2.0f));

	//Subtract radii
	//distance -= (obj1Radius + obj2Radius);
	distance -= (0.75 + 1.5);
	if (distance < 0) {
		return true;	
	}
	else {
		return false;
	}
}