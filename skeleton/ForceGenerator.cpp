#include "ForceGenerator.h"

GravityGenerator::GravityGenerator(Vector3& gravity, double t) {
	gravedad = gravity;
	time = t;
}

void GravityGenerator::updateForce(Particle* particle, double duration) {
	if (1/particle->getMass() <= 0.0f)
		return;
	particle->addForce(gravedad * particle->getMass());
}