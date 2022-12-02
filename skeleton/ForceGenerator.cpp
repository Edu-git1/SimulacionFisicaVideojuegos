#include "ForceGenerator.h"

GravityGenerator::GravityGenerator(Vector3& gravity, double t, string nombre) {
	gravedad = gravity;
	time = t;
	name = nombre;
}

void GravityGenerator::updateForce(Particle* particle) {
	if (1/particle->getMass() <= 1e-10f)
		return;
	particle->addForce(gravedad * particle->getMass());
}

void WindGenerator::updateForce(Particle* particle)
{
	if (1/particle->getMass() <= 1e-10f) return;
	Vector3 pVel = particle->getVel();
	Vector3 diffVel = velocidad - pVel;
	Vector3 force = _k1 * diffVel + _k2 * diffVel.magnitude() * diffVel;
	particle->addForce(force);
}

void DragGenerator::updateForce(Particle* particle)
{
	if (1 / particle->getMass() <= 1e-10f) return;

	particle->addForce(k * particle->getVel());
}

void WhirlwindGenerator::updateForce(Particle* particle)
{
	Vector3 dist = particle->getPos();
	velocidad = _Kt * Vector3(-(dist.z) - (ojo.z), 50 - (dist.y)-ojo.y, dist.x - (ojo.x));
	WindGenerator::updateForce(particle);
}


void ExplosionGenerator::updateForce(Particle* particle)
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

void SpringGenerator::updateForce(Particle* particle)
{
	if (fabs(1/particle->getMass()) <= 1e-10) return;
	Vector3 force = other->getPos() - particle->getPos();

	const float length = force.normalize();
	const float deltaX= length - resting_length;

	if (deltaX <= 0.f) return;

	force *= deltaX * _k;

	particle->addForce(force);
}

void BuoyancyGenerator::updateForce(Particle* particle)
{
	if (fabs(1/particle->getMass()) <= 1e-10) return;

	float h = particle->getPos().y;
	float h0 = liquid_particle->getPos().y;

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h0 - h > height * 0.5) {
		immersed = 1.0;
	}
	else if (h - h0 > height * 0.5) {
		immersed = 0.0;
	}
	else {
		immersed = (h0 - h) / height + 0.5;
	}

	f.y = density * volume * immersed * 9.8;
	particle->addForce(f);
}
