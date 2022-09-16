#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 damping)
{
	velocidad = vel;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);

	damp = damping;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 0.5, 0, 0.5, 1 });

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::Update(double t)
{
	pose = physx::PxTransform(pose.p.x + velocidad.x * t + 0.5*-damp.x*t*t, pose.p.y + velocidad.y * t + 0.5 * -damp.y * t * t, pose.p.z + velocidad.z * t + 0.5 * -damp.z * t * t);
}
