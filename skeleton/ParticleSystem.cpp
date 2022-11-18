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
	//particles.clear();
	//generators.clear();
}

void ParticleSystem::update(double t)
{

	if (uniformActive)
	{
		for (auto p : uniformGenerator->generateParticle())
			particles.push_back(p);
	}
	if (gaussActive)
	{
		for (auto p : gaussianGenerator->generateParticle())
			particles.push_back(p);
	}

	forces.updateForces(t);

	for (auto it = particles.begin(); it != particles.end();) {
		(*it)->Update(t);		
		if (!(*it)->isAlive()) {
			Firework* firework = dynamic_cast<Firework*>(*it);
			if (firework != nullptr)
			{
				for (auto i : firework->explosiones())
					particles.push_back(i);

			}
			forces.eraseRegistry(*it);
			delete (*it);
			it = particles.erase(it);
		}
		else {
			Firework* firework = dynamic_cast<Firework*>(*it);
			if (firework != nullptr)
			{
				shared_ptr<FireworkGenerator> generator;
				Particle* particle = new Particle(firework->getPos(), particleBase->getVel(), particleBase->getDamp(), particleBase->getAcc(), particleBase->getMass(), particleBase->getTime());
				generator.reset(new FireworkGenerator(particle, particle->getPos(), 200));
				firework->updateGenerator(generator);
			}
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
	Vector3 pose = { 0.0, 10.0, 0.0 };
	Vector3 vel = { 0, 30.0, 0 };
	Vector3 acc = { 0.0f, -9.8f, 0.0f };
	double time = 5.0;
	double mass = 0.5;
	double damp = 0.95;
	Particle* p = new Particle(pose, vel, damp, acc, mass, time);
	p->setColor(Vector4{ 0.0f, 0.0f, 1.f, 1 });

	uniformGenerator = new UniformParticleGenerator(p, 0.9, { 5, 0, 5 }, { 10, 0, 10 }, 5);

	generators.push_back(uniformGenerator);
}

void ParticleSystem::fogSystem()
{
	Vector3 pose = { 0.0, 10.0, 0.0 };
	Vector3 vel = { 0, 0, 0 };
	Vector3 acc = { 0.0f, 0.f, 0.0f };
	double time = 10.0;
	double mass = 1;
	double damp = 0.85;
	Particle* p = new Particle(pose, vel, damp, acc, mass, time);
	p->setColor(Vector4{ 0.49f, 0.49f, 0.49f, 1 });

	gaussianGenerator = new GaussianParticleGenerator(p, 0.7, { 5, 5, 5 }, { 2, 2, 2 }, 1000);

	generators.push_back(gaussianGenerator);
}

void ParticleSystem::fireworkSystem()
{
	Vector3 pose = { 0.0, 10.0, 0.0 };
	Vector3 vel = { 0, 20, 0 };
	Vector3 acc = { 0.0f, 0.f, 0.0f };
	double time = 2.0;
	double mass = 1;
	double damp = 0.85;
	Particle* particle = new Particle(pose, vel, damp, acc, mass, time);
	particleBase = new Particle(pose, vel, damp, acc, mass, time);

	shared_ptr<FireworkGenerator> generator;
	generator.reset(new FireworkGenerator(particle, particle->getPos(), 200));

	Particle* particle2 = new Particle(pose, vel, damp, acc, mass, time);
	Firework* fire = new Firework(particle2, generator);
	particles.push_back(fire);
}

void ParticleSystem::gravitySystem() {
	Particle* part = new Particle({ 10, 10, 10 }, { 0, 0, 0 }, 0.99, { 0, 0, 0 }, 1, 5);
	GravityGenerator* generator = new GravityGenerator(Vector3(0, -9.8, 0), 100);
	forces.addRegistry(generator, part);
	particles.push_back(part);
}
