#pragma once
#include "core.hpp"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include <list>
#include <random>
#include <complex>
#include <vector>
#include <string>
#include "ForceGenerator.h"

//Create a particle with the cylinder shape that shoots other particles out when keys are pressed
class Cannon
{
public:
	Cannon();
	~Cannon();
	void update(float t, Vector3 pos, PxVec3 dir);
	void draw();
	void shoot(Vector3 pos, Vector3 dir);
private:
	//shape
	physx::PxShape* shape;
	//pose
	physx::PxTransform pose;
	physx::PxQuat ogdir = physx::PxQuat(-45, physx::PxVec3(0, 1, 0));
	//render item
	RenderItem* renderItem;
	//explosion generator
	ForceGenerator* explosion;
	//particle generator
	ParticleGenerator* particleGenerator;
	
};

