#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
	for (auto p : particles)
	{
		delete p;
		p = nullptr;
	}
	for (auto f : generators) {
		delete f;
		f = nullptr;
	}
	particles.clear();
	generators.clear();
}

void ParticleSystem::update(double t)
{

	if (uniformActive)
	{
		for (auto p : uniformGenerator->generateParticle())
			particles.push_back(p);
	}

	for (auto it = particles.begin(); it != particles.end();) {
		(*it)->Update(t);
		if (!(*it)->isAlive()) {
			if ((*it) != nullptr) 
			{
				delete (*it);
			}
			it = particles.erase(it);
		}
		else {
			it++;
		}
	}
}

ParticleGenerator* ParticleSystem::getParticleGenerator(string name)
{
	for (auto g : generators)
	{
		if (g->getName() == name)
			return g;
	}
}

void ParticleSystem::fountainSystem()
{
	Vector3 pose = { 0.0, 3.0, 0.0 };
	Vector3 vel = { 2.0, 5.0, 2.0 };
	Vector3 acc = { 0.0f, -0.08f, 0.0f };
	double time = 100.0;
	double mass = 0.5;
	double damp = 0.95;
	Particle* p = new Particle(pose, vel, damp, acc, mass, time);
	p->setColor(Vector4{ 0.0f, 0.0f, 0.f, 1 });

	uniformGenerator = new UniformParticleGenerator(p, 0.9, { 5, 0, 5 }, { 5, 0, 0.01 }, 400);

	generators.push_back(uniformGenerator);
}
