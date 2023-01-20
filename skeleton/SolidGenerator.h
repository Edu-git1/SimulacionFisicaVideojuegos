#include "SolidParticle.h"
#include "Barco.h"
#include "core.hpp"
#include <list>
#include <string>
#include <random>
#include <iostream>
using namespace physx;
using namespace std;

class SolidGenerator
{
public:
	virtual PxRigidBody* generateParticles(double t) = 0;

	Vector3 getPos() { return pose; };
	Vector3 getVel() { return velocidad; };
	Vector4 getColor() { return color; };
	double getSpawn() { return spawnTime; };
	double getRigidTime() { return rigidTime; };
	string getName() { return name; }
	PxShape* getShape() { return shape; };
	bool isActive() { return active; };

	void setPos(Vector3 pos) { pose = pos; };
	void setVel(Vector3 vel) { velocidad = vel; };
	void setColor(Vector4 colour) { color = colour; };
	void setSpawn(double spawn) { spawnTime = spawn; };
	void setRigidTime(double t) { rigidTime = t; };
	void setName(string nombre) { name = nombre; }
	void setShape(PxShape* newShape) {
		if (shape != nullptr) shape->release();
		shape = newShape;
	};
	void setActive(bool ac) { active = ac; }
	virtual ~SolidGenerator() {};

protected:
	Vector3 pose = { 0, 0, 0 }, velocidad = { 0, 0 ,0 };
	Vector4 color = { 1, 1, 1, 1 };
	double spawnTime = 2;
	double rigidTime = 10;
	double time;
	string name = "";
	PxShape* shape = CreateShape(physx::PxSphereGeometry(1));
	bool active = true;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
};

class GaussianSolid : public SolidGenerator {

public:

	GaussianSolid(PxScene* escena, PxPhysics* physics);
	~GaussianSolid() {};
	PxRigidBody* generateParticles(PxRigidBody* p, PxShape* sh, double t);
	Vector3 getDevPos() { return dev_pos; };
	Vector3 getDevVel() { return dev_vel; };
	void setDevPos(Vector3 pos) { dev_pos = pos; };
	void setDevVel(Vector3 vel) { dev_vel = vel; };

protected:
	Vector3 dev_pos = { 0, 0, 0 }, dev_vel = { 0, 0, 0 };
	normal_distribution<float> dist;
	mt19937 random_generator;
};

class GaussianBoats{

public:

	GaussianBoats(PxScene* escena, PxPhysics* physics);
	~GaussianBoats() {};
	Barco* generateParticles(double t);

protected:
	GaussianSolid* gaussian;
	Barco* barco;
	Vector3 dev_pos = { 0, 0, 0 }, dev_vel = { 0, 0, 0 };
	normal_distribution<float> dist;
	mt19937 random_generator;
	Vector3 pose = { 0, 0, 0 }, velocidad = { 0, 0 ,0 };
	Vector4 color = { 1, 1, 1, 1 };
	double spawnTime = 0;
	double rigidTime = 10;
	double time;
	string name = "";
	PxShape* shape = CreateShape(physx::PxSphereGeometry(1));
	bool active = true;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
};