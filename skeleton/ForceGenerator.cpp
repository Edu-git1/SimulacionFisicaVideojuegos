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
	Vector3 dist = particle->getPos();
	velocidad = _Kt * Vector3(-(dist.z) - (ojo.z), 50 - (dist.y)-ojo.y, dist.x - (ojo.x));
	WindGenerator::updateForce(particle, duration);
}


void ExplosionGenerator::updateForce(Particle* particle, double duration)
{
	if (1/particle->getMass() <= 1e-10f) return;
	Vector3 distV = particle->getPos() - center;

	float dist = distV.normalize();
	float r = dist * dist;
	if (dist == 0) dist = 1e-5;
	Vector3 force = (_k / r) * distV * exp(-time / _kt);
	if (dist <= radio) 
		particle->addForce(force);
}

