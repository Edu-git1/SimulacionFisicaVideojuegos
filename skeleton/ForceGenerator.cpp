#include "ForceGenerator.h"

GravityGenerator::GravityGenerator(Vector3& gravity, double t) {
	gravedad = gravity;
	time = t;
	name = "gravity";
}

void GravityGenerator::updateForce(Particle* particle, double duration) {
	if (1/particle->getMass() <= 0.0f)
		return;
	particle->addForce(gravedad * particle->getMass());
}

void WindGenerator::updateForce(Particle* particle, double duration)
{
	if (1/particle->getMass() <= 0.0f) return;

	Vector3 diff = velocidad - particle->getVel();

	particle->addForce(_k1 * diff + _k2 * diff.magnitude() * diff);
}

void DragGenerator::updateForce(Particle* particle, double duration)
{
	if (1 / particle->getMass() <= 0.0f) return;

	particle->addForce(k * particle->getVel());
}

void WhirlwindGenerator::updateForce(Particle* particle, double duration)
{
	Vector3 pos = particle->getPos();
	velocidad = _Kt * Vector3(-(pos.z - ojo.z) - 0.2, 10 - (pos.y - ojo.y), pos.x - ojo.x - 0.2);
	WindGenerator::updateForce(particle, duration);
}

