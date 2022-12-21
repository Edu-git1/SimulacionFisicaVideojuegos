#include "SolidGenerator.h"


GaussianSolid::GaussianSolid(PxScene* scene, PxPhysics* physics)
{
	gScene = scene;
	gPhysics = physics;
	random_device r;
	random_generator = std::mt19937(r());
	dist = std::normal_distribution<float>(0, 1);
}

SolidParticle* GaussianSolid::generateParticles(double t)
{
	time += t;
	if (time > spawnTime) return nullptr;
	time = 0;
	PxRigidDynamic* rigid = gPhysics->createRigidDynamic({ 0,0,0 });
	rigid->attachShape(*shape);
	gScene->addActor(*rigid);
	Vector3 pos = { pose.x + dev_pos.x + dist(random_generator), pose.y + dev_pos.y + dist(random_generator) ,pose.z + dev_pos.z + dist(random_generator) };
	rigid->setGlobalPose(PxTransform(pos));
	Vector3 vel = { velocidad.x + dev_vel.x + dist(random_generator), velocidad.y + dev_vel.y + dist(random_generator) ,velocidad.z + dev_vel.z + dist(random_generator) };

	return new SolidParticle(rigid, rigidTime, color);
}