#pragma once
#include "core.hpp"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include <list>
#include <random>
#include <complex>
#include <vector>
#include <string>

//Create a particle with the cylinder shape that shoots other particles out when keys are pressed
class Cannon
{
public:
	Cannon();
	~Cannon();
	void update(float t, Vector3 pos, physx::PxVec3 dir);
	void draw();
	void shoot();
	Vector3 getPos() { return posi; };
private:
	//shape
	physx::PxShape* shape;
	//pose
	physx::PxTransform pose;
	physx::PxQuat ogdir = physx::PxQuat(-45, physx::PxVec3(0, 1, 0));
	//render item
	RenderItem* renderItem;
	Vector3 posi;
};

