#pragma once
#include "GameState.h"


GameState::GameState()
{
	isHit = false;

}

GameState::~GameState()
{
	for (Camera* c : cameras) {
		c->~Camera();
		//cameras.remove(c);
<<<<<<< HEAD
	}

	for (Player* p : players) {
		p->~Player();
		//players.remove(p);
=======
>>>>>>> Changed phi value for moving player left (case 2) to 90 & commented the z-coordinate update for the player (shouldn't move in the z anyways). Weird result.
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Latest, got shiz
	float currPhi = wormholes.front()->getPhi();
	glm::mat4* view = (cameras.front())->getView();
	for (Camera* c : cameras)
		c->update(currPhi, time, dt);

<<<<<<< HEAD
<<<<<<< HEAD
	for (Player* p : players) {
		p->setviewMat(view);
		p->update(time, dt, arr);
	}

	for (GObject* g : gObjects)
		g->update(time, dt);
<<<<<<< HEAD

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
						//set bool
						isHit = true;
					}
				}
			}
		}

	}
=======
=======
	float currPhi = wormholes.front()->getPhi();
	glm::mat4 *view = (cameras.front())->getView();
	for(Camera* c: cameras)
		c->update(currPhi, time, dt);

>>>>>>> Updated Camera to adjust its position to move with the center of the wormhole. Updated Particles & Asteroids to not use the transpose of the Camera's view matrix & directly use the Camera's view matrix (passed to each Particle/Asteroid). Got keyboard input working how we want with Blane.
=======
	for (Player* p : players)
=======
	for (Player* p : players) {
		p->setviewMat(view);
>>>>>>> KABOOM WORKS!
		p->update(time, dt, arr);
	}

>>>>>>> Latest, got shiz
	for (GObject* g : gObjects)
		g->update(time, dt);

	for (Wormhole* w : wormholes) {
		w->setviewMat(view);
<<<<<<< HEAD
=======
	
	for (Player* p : players) 
		p->update(time, dt);
	
	for (Wormhole* w : wormholes)
>>>>>>> updated player class with input switch case
		w->update(time, dt);
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> Implemented update function for Particles and the new Wormhole class that manages each Particle. Implemented interpolation of Particles. Implemented alpha value (transparency ratio) in the image loader. Still need to implement the "cone" function in Wormhole.h & its passing to Particles on construction, "shaping" function in Wormhole.cpp & its passing to Particles on construction, and Particle's update based on those functions.
=======

	
	
>>>>>>> Implemented Asteroids
=======
	}
>>>>>>> Updated Camera to adjust its position to move with the center of the wormhole. Updated Particles & Asteroids to not use the transpose of the Camera's view matrix & directly use the Camera's view matrix (passed to each Particle/Asteroid). Got keyboard input working how we want with Blane.
=======
		w->update(time, dt);
	}
<<<<<<< HEAD
>>>>>>> Latest, got shiz
=======


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
						//set bool
						isHit = true;
					}
				}
			}
		}

	}
>>>>>>> Added bilboarding and moved ship closer
}

void GameState::render(double alpha)
{
	for (Camera* c : cameras)
		c->render(alpha);
<<<<<<< HEAD
<<<<<<< HEAD

	for (Player* p : players)
<<<<<<< HEAD
		p->render(alpha, isHit);
	
=======
		p->render(alpha);

>>>>>>> updated player class with input switch case
=======
>>>>>>> Latest, got shiz
=======

	for (Player* p : players)
		p->render(alpha, isHit);
	
>>>>>>> Added bilboarding and moved ship closer
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
<<<<<<< HEAD
<<<<<<< HEAD

<<<<<<< HEAD
//Player needs getPos and Asteroid needs get postion
bool GameState::collisionDetection(Player* obj1, Asteroid* obj2)
{
	//Extract Positions from player and asteroid
	glm::vec3 pos1 = obj1->getPosition();
	glm::vec3 pos2 = *(obj2->getPosition());

	//Calculate Distance
	//float distance = sqrt(pow(obj2.pos.x - obj1.pos.x, 2.0f) + pow(obj2.y - obj1.y, 2.0f) + pow(obj2.z - obj1.z, 2.0f));
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
=======
//
=======

>>>>>>> Added bilboarding and moved ship closer
//void addInput(Input* obj)
//{
//
//}
//void removeInput(Input* obj)
//{
//
//}
<<<<<<< HEAD
>>>>>>> updated player class with input switch case
=======



=======
>>>>>>> Updated wormhole to perform position calculations for each Particle/Asteroid. Made shaping function an even amplitude throughout. Sped up Asteroids. Asteroids STILL follow a DIFFERENT path than Particles for SOME UNGODLY REASON.
//Player needs getPos and Asteroid needs get postion
bool GameState::collisionDetection(Player* obj1, Asteroid* obj2)
{
	//Extract Positions from player and asteroid
	glm::vec3 pos1 = obj1->getPosition();
	glm::vec3 pos2 = *(obj2->getPosition());

	//Calculate Distance
	//float distance = sqrt(pow(obj2.pos.x - obj1.pos.x, 2.0f) + pow(obj2.y - obj1.y, 2.0f) + pow(obj2.z - obj1.z, 2.0f));
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
>>>>>>> Added bilboarding and moved ship closer
