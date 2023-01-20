#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "SolidParticle.h"
using namespace physx;

class Barco{
public:
	Barco(PxScene* scene, PxPhysics* physics, Vector3 pos, float t);
	~Barco();
	void update(double t);
	PxRigidBody* getSail() { return sail; };
	PxRigidBody* getBoat() { return boat; };
	RenderItem* getSailRender() { return sailRender; };
	RenderItem* getBoatRender() { return boatRender; };
	bool isAlive() { return alive; };
	void setAlive(bool a) { alive = a; };
	
private:
	PxRigidDynamic* boat;
	PxRigidDynamic* sail;
	PxShape* boatShape;
	RenderItem* boatRender;
	PxShape* sailShape;
	RenderItem* sailRender;
	float startTime = 0;
	bool alive = true;
};