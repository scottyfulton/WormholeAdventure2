#pragma once
#include "GameState.h"

GameState::GameState()
{

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

	for (Player* p : players)
		p->update(time, dt, arr);

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
			//Check collision with Wormhole

			//Only check asteroids that are close to ship based on Z axis


			//For each astroid calculate collision with ship
			for (Wormhole* w : wormholes) {
				std::list<Asteroid*>* aList = w->getAsteroid();
				for (Asteroid* a : *aList) {
					if (collisionDetection(p, a))
					{
						//Collision - Ship hit Astroid	
						//boom game over
						std::cout << "BOOOOOOOOOOOOM" << std::endl;
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
		p->render(alpha);
	
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

	//Extract the Radius because its symmetrical!!!!!
	//std::cout << "big d " << distance << std::endl;


	//Calculate Distance
	//float distance = sqrt(pow(obj2.pos.x - obj1.pos.x, 2.0f) + pow(obj2.y - obj1.y, 2.0f) + pow(obj2.z - obj1.z, 2.0f));
	float distance = sqrt(pow(pos2.x - pos1.x, 2.0f) + pow(pos2.y - pos1.y, 2.0f) + pow(pos2.z - pos1.z, 2.0f));

	//Subtract radii
	//distance -= (obj1Radius + obj2Radius);
	distance -= (05 + 1.0);
	if (distance < 0) {
		return true;	
	}
	else {
		return false;
	}
}