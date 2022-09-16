#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel)
{
	velocidad = vel;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 0.5, 0, 0.5, 1 });

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::Update(double t)
{
	pose = physx::PxTransform(pose.p.x + velocidad.x * t, pose.p.y + velocidad.y * t, pose.p.z + velocidad.z * t);
}
