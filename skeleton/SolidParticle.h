#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "ParticleGenerator.h"
using namespace physx;

	enum Shape {
		Box,
		Sphere,
		Capsule
	};

class SolidParticle
{
public:
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
	bool isAlive() { return alive; };
	void setAlive(bool a) { alive = a; };
	bool checkTime() { if (startTime < time) return false; return true; };
	double getTime() { return time; };
	Vector3 getOriginalPos() { return originalPos; };
	float getDist() {
		Vector3 distV = getPosition() - originalPos;

		float dist = abs(distV.normalize());
		
		return dist;
	}
	RenderItem* getRender() { return render; };
	PxRigidBody* getBody() { return rigid; };

protected:
	PxRigidDynamic* rigid;
	RenderItem* render;
	double time;
	double startTime;
	bool alive = true;
	Vector3 originalPos;
};