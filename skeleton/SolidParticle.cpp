#include "SolidParticle.h"
#include <iostream>

SolidParticle::SolidParticle(physx::PxRigidDynamic* body, double tiempo, Vector4 color) {
	rigid = body;
	time = tiempo;
	startTime = 0;
	PxShape* shape;
	rigid->getShapes(&shape, 1);
	render = new RenderItem(shape, rigid, color);
	originalPos = getPosition();
}

SolidParticle::SolidParticle(physx::PxScene* scene, physx::PxPhysics* physx, Vector3 pos, Vector3 vel, double mass, double tiempo, Vector3 dims, Shape s, Vector4 color)
{
	rigid = physx->createRigidDynamic(physx::PxTransform(pos));
	rigid->setLinearVelocity(vel);
	rigid->setMass(mass);
	rigid->setAngularVelocity({ 0,0,0 });
	time = tiempo;
	startTime = 0;

	physx::PxShape* shape;
	switch (s) {
	case Box:
		shape = CreateShape(physx::PxBoxGeometry(dims));
		break;
	case Sphere:
		shape = CreateShape(physx::PxSphereGeometry(dims.x));
		break;
	case Capsule:
		shape = CreateShape(physx::PxCapsuleGeometry(dims.x, dims.y));
		break;
	default:
		shape = CreateShape(physx::PxSphereGeometry(1));
		break;
	}

	rigid->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*rigid, 1);
	scene->addActor(*rigid);
	render = new RenderItem(shape, rigid, color);
	originalPos = getPosition();
}

SolidParticle::~SolidParticle() {
	rigid->release();
	DeregisterRenderItem(render);
	render = nullptr;
}

void SolidParticle::update(double t) {
	if (time > 0.0) startTime += t;
}

void SolidParticle::addForce(Vector3 f) {
	rigid->addForce(f);
}

void SolidParticle::addTorque(Vector3 f) {
	rigid->addTorque(f);
}

Vector3 SolidParticle::getPosition()
{
	return rigid->getGlobalPose().p;
}

Vector3 SolidParticle::getLinearVelocity()
{
	return rigid->getLinearVelocity();
}

float SolidParticle::getMass()
{
	return rigid->getMass();
}

float SolidParticle::getInvMass()
{
	if (rigid->getMass() <= 0) return -1;
	return rigid->getInvMass();
}