#include "Barco.h"

Barco::Barco(PxScene* scene, PxPhysics* physics, Vector3 pos, float t)
{
	physx::PxTransform posBarco = physx::PxTransform({ -10, 5, 0 });
	posBarco.q = physx::PxQuat(-45, physx::PxVec3(0, 1, 0));
	boat = physics->createRigidDynamic(posBarco);
	PxRigidBodyExt::updateMassAndInertia(*boat, 200);
	boatShape = CreateShape(physx::PxBoxGeometry(Vector3(10, 2.5, 10)));
	boat->attachShape(*boatShape);
	boat->setName("barco");
	scene->addActor(*boat);
	boatRender = new RenderItem(boatShape, boat, { 0.5, 0.25, 0, 1 });
	
	physx::PxTransform posVela = physx::PxTransform({ -10, 13, 0 });
	posVela.q = physx::PxQuat(-45, physx::PxVec3(0, 1, 0));
	sail = physics->createRigidDynamic(posVela);
	physx::PxRigidBodyExt::updateMassAndInertia(*sail, 50);
	sailShape = CreateShape(physx::PxBoxGeometry(Vector3(10, 5, 0.1)));
	sail->attachShape(*sailShape);
	sail->setName("barco");
	sail->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	scene->addActor(*sail);
	sailRender = new RenderItem(sailShape, sail, { 0.8, 0.9, 0.7, 1 });
	
	startTime = t;
}

Barco::~Barco()
{
	boat->release();
	DeregisterRenderItem(boatRender);
	boatRender = nullptr;
	sail->release();
	DeregisterRenderItem(sailRender);
	sailRender = nullptr;
}

void Barco::update(double t) {
	startTime -= t;
	if (startTime < 0.0021) {
		alive = false;
	}
}
