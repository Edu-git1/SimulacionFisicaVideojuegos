#include "ParticleSystem.h"
#include "Particle.h"

void PartycleSystem::update(double t)
{
	for (auto it = particles.begin(); it != particles.end();) {
		(*it)->Update(t);
		if (outOfBounds((*it)) || !(*it)->isAlive()) {
			delete (*it);
			it = particles.erase(it);
		}
		else {
			it++;
		}
	}
}

void PartycleSystem::generateParticle()
{
	
}

bool PartycleSystem::outOfBounds(Particle* part)
{
	if (part->getPosition().y < 0.0f ||part->getPosition().z > 200.0f) {
		return true;
	}
	return false;
}
