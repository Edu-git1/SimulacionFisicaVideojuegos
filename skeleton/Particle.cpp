#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, double damping, double aceleracion, double mass)
{
	velocidad = vel;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);

	posi = pos;

	damp = damping;

	acc = aceleracion;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 0.5, 0, 0.5, 1 });

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::Update(double t)
{
	velocidad += acc * t * Vector3(1, 1, 1);
	velocidad *= pow(damp, t);
	posi += velocidad*t;
	pose = physx::PxTransform(posi);
}
