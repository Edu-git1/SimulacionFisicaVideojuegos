#include "SolidGenerator.h"


GaussianSolid::GaussianSolid(PxScene* scene, PxPhysics* physics)
{
	gScene = scene;
	gPhysics = physics;
	random_device r;
	random_generator = std::mt19937(r());
	dist = std::normal_distribution<float>(0, 1);
}

PxRigidBody* GaussianSolid::generateParticles(PxRigidBody* p, PxShape* sh, double t)
{
	time += t;
	if (time > spawnTime) return nullptr;
	time = 0;
	shape = sh;
	p->attachShape(*shape);
	gScene->addActor(*p);
	Vector3 pos = { pose.x + dev_pos.x + dist(random_generator), pose.y + dev_pos.y + dist(random_generator) ,pose.z + dev_pos.z + dist(random_generator) };
	p->setGlobalPose(PxTransform(pos));
	Vector3 vel = { velocidad.x + dev_vel.x + dist(random_generator), velocidad.y + dev_vel.y + dist(random_generator) ,velocidad.z + dev_vel.z + dist(random_generator) };

	return p;
}

GaussianBoats::GaussianBoats(PxScene* escena, PxPhysics* physics)
{
	gScene = escena;
	gPhysics = physics;
	random_device r;
	random_generator = std::mt19937(r());
	dist = std::normal_distribution<float>(0, 1);
}

Barco* GaussianBoats::generateParticles(double t)
{
	spawnTime -= t;
	if (spawnTime > 0.0021) return nullptr;
	spawnTime = 5;
	Vector3 pos = { pose.x + dev_pos.x + dist(random_generator), pose.y + dev_pos.y + dist(random_generator) ,pose.z + dev_pos.z + dist(random_generator) };
	barco = new Barco(gScene, gPhysics, pos, 6);
	
	return barco;
}