#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, double damping, Vector3 aceleracion, float mass, double time)
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
	if (1.f/masa <= 0.f) return;
	startTime -= t;
	posi += velocidad * t;
	pose = physx::PxTransform(posi);
	acc = fuerza * (1.f/masa);
	//cout << acc.y << endl;
	velocidad += acc * t;
	velocidad *= pow(damp, t);
	if (startTime < 0) {
		alive = false;
	}
	eraseForce();
}
