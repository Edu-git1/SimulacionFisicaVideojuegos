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
	if (particles.size() < 100) {
		for (auto g : generators) {
			if (g->isActive()) {
				for (auto p : g->generateParticle()) {
					particles.push_back(p);
				}
			}
		}
	}
	for (auto f : forceGenerators) {
		for (auto it = particles.begin(); it != particles.end();) {
			if (f->isActive()) {
				forces.addRegistry(f, (*it));
			}
			it++;
		}
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
			forces.eraseRegistry((*it));
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
	Vector3 vel = { 0, 30.0, 30.0 };
	Vector3 acc = { 0.0f, 0.f, 0.0f };
	double time = 5.0;
	double mass = 0.5;
	double damp = 0.95;
	Particle* p = new Particle(pose, vel, damp, acc, mass, time);
	p->setColor(Vector4{ 0.0f, 0.0f, 1.f, 1 });

	fountainGenerator = new UniformParticleGenerator(p, 0.9, { 5, 0, 5 }, { 10, 0, 10 }, 5);

	generators.push_back(fountainGenerator);
}

void ParticleSystem::fogSystem()
{
	Vector3 pose = { 0.0, 10.0, 0.0 };
	Vector3 vel = { 0, 0, 0 };
	Vector3 acc = { 0.0f, 0.f, 0.0f };
	double time = 1.0;
	double mass = 1;
	double damp = 0.85;
	Particle* p = new Particle(pose, vel, damp, acc, mass, time);
	p->setColor(Vector4{ 0.49f, 0.49f, 0.49f, 1 });

	fogGenerator = new GaussianParticleGenerator(p, 0.7, { 5, 5, 5 }, { 2, 2, 2 }, 10);

	generators.push_back(fogGenerator);
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
	gravityGenerator = new GravityGenerator(Vector3(0, -9.8, 0), 100);
	forceGenerators.push_back(gravityGenerator);
}

void ParticleSystem::dragSystem()
{

}

void ParticleSystem::windSystem()
{
	windGenerator = new WindGenerator(Vector3(5, 0, 0), 1, 0.1);
	forceGenerators.push_back(windGenerator);
}

void ParticleSystem::whirlwindSystem()
{
	whirlwindGenerator = new WhirlwindGenerator(Vector3(0, 0, 0), 1, 0.1, 0.75);
	forceGenerators.push_back(whirlwindGenerator);
}

void ParticleSystem::eraseGenerator(string nombre) {
	for (auto it = generators.begin(); it != generators.end();)
	{
		if ((*it)->getName() == nombre) {
			generators.erase(it);
			it = generators.end();
		}
		else
			it++;
	}
}

void ParticleSystem::eraseForce(string nombre) {
	for (auto it = forceGenerators.begin(); it != forceGenerators.end();)
	{
		if ((*it)->name == nombre) {
			forceGenerators.erase(it);
			it = forceGenerators.end();
		}		
		else
			it++;
	}
}
