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

	for (GObject* g : gObjects) {
		gObjects.remove(g);
	}
}

void GameState::init()
{

}

void GameState::update(double time, double dt)
{

}

void GameState::render(double alpha)
{

	for (Camera* c : cameras) {
		c->render(alpha);
	}

	//Objects
	for (GObject* g : gObjects) {
		g->render(alpha);
	}
	
}

void GameState::addGObject(GObject* obj)
{
	gObjects.push_back(obj);
}

void GameState::removeGObject(GObject* obj)
{
	gObjects.remove(obj);
}

void GameState::addCamera(Camera* obj)
{
	cameras.push_back(obj);
}

void GameState::removeCamera(Camera* obj)
{
	cameras.remove(obj);
}

