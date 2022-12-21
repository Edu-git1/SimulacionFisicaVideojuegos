#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;

class SolidParticle
{
public:
	enum Shape {
		Box,
		Sphere,
		Capsule
	};
	SolidParticle(PxRigidDynamic* rigid, double time, Vector4 color);
	SolidParticle(PxScene* scene, PxPhysics*, Vector3 pos, Vector3 vel, double mass, double tiempo, Vector3 dims, Shape s, Vector4 color);
	virtual ~SolidParticle();
	
	
	void update(double t);

	void addForce(Vector3 f);
	void addTorque(Vector3 f);

	Vector3 getPosition();
	Vector3 getLinearVelocity();
	float getMass();
	float getInvMass();
	bool isAlive();

protected:
	PxRigidDynamic* rigid;
	RenderItem* render;
	double time;
	double startTime;
};