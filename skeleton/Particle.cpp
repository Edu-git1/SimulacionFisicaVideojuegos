#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, double damping, Vector3 aceleracion, float mass, double time, physx::PxShape* forma)
{
	shape = forma;

	velocidad = vel;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);

	posi = pos;

	damp = damping;

	acc = aceleracion;

	masa = mass;

	renderItem = new RenderItem(shape, &pose, { 0.5, 0, 0.5, 1 });

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
	float invMass = 1.f / masa;

	auto momentAcc = fuerza * invMass;
	velocidad += momentAcc * t;
	velocidad *= pow(damp, t);
	startTime -= t;
	posi += velocidad * t;
	pose = physx::PxTransform(posi);
	if (startTime < 0) {
		alive = false;
	}
	std::cout << momentAcc.y<<endl;
	eraseForce();
}
