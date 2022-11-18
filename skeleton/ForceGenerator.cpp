#include "ForceGenerator.h"

GravityGenerator::GravityGenerator(Vector3& gravity, double t) {
	gravedad = gravity;
	time = t;
	name = "gravity";
}

void GravityGenerator::updateForce(Particle* particle, double duration) {
	if (1/particle->getMass() <= 0.f)
		return;
	particle->addForce(gravedad * particle->getMass());
}

void WindGenerator::updateForce(Particle* particle, double duration)
{
	if (1/particle->getMass() <= 0.0f) return;
	Vector3 pVel = particle->getVel();
	Vector3 diffVel = velocidad - pVel;
	Vector3 force = _k1 * diffVel + _k2 * diffVel.magnitude() * diffVel;
	particle->addForce(force);
}

void DragGenerator::updateForce(Particle* particle, double duration)
{
	if (1 / particle->getMass() <= 0.f) return;

	particle->addForce(k * particle->getVel());
}

void WhirlwindGenerator::updateForce(Particle* particle, double duration)
{
	Vector3 dist = ojo - particle->getPos();
	velocidad = _Kt * Vector3(-(dist.z) - (dist.x), 50 - (dist.y), dist.x - (dist.z));
	WindGenerator::updateForce(particle, duration);
}

