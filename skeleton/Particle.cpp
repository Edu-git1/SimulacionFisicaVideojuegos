#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, double damping, Vector3 aceleracion, double mass, double time)
{
	velocidad = vel;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);

	posi = pos;

	damp = damping;

	acc = aceleracion;

	masa = mass;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 0.5, 0, 0.5, 1 });

	startTime = time;

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::Update(double t)
{
	velocidad += acc * t *masa;
	velocidad *= pow(damp, t);
	posi += velocidad*t;
	pose = physx::PxTransform(posi);
	if (startTime != 0) {
		decreaseTime();
	}
}
