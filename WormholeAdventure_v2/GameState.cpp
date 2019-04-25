#pragma once
#include "GameState.h"

GameState::GameState()
{

}

GameState::~GameState()
{
	for (Camera* c : cameras) {
		cameras.remove(c);
	}

	for (Player* p : players) {
		players.remove(p);
	}

	for (GObject* g : gObjects) {
		gObjects.remove(g);
	}
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
}

void GameState::render(double alpha)
{
	for (Camera* c : cameras)
		c->render(alpha);
	//Objects
	for (GObject* g : gObjects)
		g->render(alpha);

	for (Wormhole* w : wormholes)
		w->render(alpha);

	for (Player* p : players)
		p->render(alpha);
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
//
//void addInput(Input* obj)
//{
//
//}
//void removeInput(Input* obj)
//{
//
//}