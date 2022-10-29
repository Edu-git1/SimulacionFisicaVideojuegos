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

	alive = true;

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	renderItem = nullptr;
}

void Particle::Update(double t)
{
	startTime -= t;
	pose = physx::PxTransform(posi.x, posi.y, posi.z);
	pose = physx::PxTransform(pose.p.x + velocidad.x * t, pose.p.y + velocidad.y * t, pose.p.z + velocidad.z * t);
	velocidad = Vector3(velocidad.x + acc.x * t, velocidad.y + acc.y * t, velocidad.z + acc.z * t);
	velocidad *= pow(damp, t);
	if (startTime < 0) {
		alive = false;
	}
}
