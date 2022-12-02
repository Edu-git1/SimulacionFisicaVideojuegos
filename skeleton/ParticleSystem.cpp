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
	for (auto f : forceGenerators) {
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
		if (f->isActive()) {
			for (auto it = particles.begin(); it != particles.end();) {
				forces.addRegistry(f, (*it));
				it++;
			}
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
				generator.reset(new FireworkGenerator("firework", particle, particle->getPos(), 200));
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
	Vector3 vel = { 0, 10.0, 10.0 };
	Vector3 acc = { 0.0f, 0.f, 0.0f };
	double time = 5.0;
	double mass = 50;
	double damp = 0.95;
	Particle* p = new Particle(pose, vel, damp, acc, mass, time);
	p->setColor(Vector4{ 0.0f, 0.0f, 1.f, 1 });

	fountainGenerator = new UniformParticleGenerator("fountain", p, 0.9, { 5, 0, 5 }, { 10, 0, 10 }, 5);

	generators.push_back(fountainGenerator);
}

void ParticleSystem::fogSystem()
{
	Vector3 pose = { 0.0, 10.0, 0.0 };
	Vector3 vel = { 0, 0, 0 };
	Vector3 acc = { 0.0f, 0.f, 0.0f };
	double time = 10.0;
	double mass = 10;
	double damp = 0.85;
	Particle* p = new Particle(pose, vel, damp, acc, mass, time);
	p->setColor(Vector4{ 0.49f, 0.49f, 0.49f, 1 });

	fogGenerator = new GaussianParticleGenerator("niebla", p, 0.7, { 5, 5, 5 }, { 2, 2, 2 }, 2);

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
	generator.reset(new FireworkGenerator("firework", particle, particle->getPos(), 200));

	Particle* particle2 = new Particle(pose, vel, damp, acc, mass, time);
	Firework* fire = new Firework(particle2, generator);
	particles.push_back(fire);
}

void ParticleSystem::gravitySystem() {
	gravityGenerator = new GravityGenerator(Vector3(0, -9.8, 0), 100, "gravity1");
	forceGenerators.push_back(gravityGenerator);
}

void ParticleSystem::dragSystem()
{

}

void ParticleSystem::windSystem()
{
	windGenerator = new WindGenerator(Vector3(5, 0, 0), 1, 0, "wind1");
	forceGenerators.push_back(windGenerator);
}

void ParticleSystem::whirlwindSystem()
{
	whirlwindGenerator = new WhirlwindGenerator(Vector3(0, 0, 0), 1, 0.1, 1, "whirlwind1");
	forceGenerators.push_back(whirlwindGenerator);
}

void ParticleSystem::explosionSystem() {
	ExplosionGenerator* exp = new ExplosionGenerator({ 0,0,0 }, 20, 100, .15, "explosion1");
	for (auto it = particles.begin(); it != particles.end();) {
		forces.addRegistry(exp, (*it));
		it++;
	}
}

void ParticleSystem::springSystem()
{
	Particle* p1 = new Particle({ -10, 10, 0 }, { 0, 0, 0 }, 0.85, { 0, 0, 0 }, 2.0, 100);
	Particle* p2 = new Particle({ 10, 10, 0 }, { 0, 0, 0 }, 0.85, { 0, 0, 0 }, 2.0, 100);

	SpringGenerator* f1 = new SpringGenerator(1, 10, p2, "spring1");
	f1->setActive();
	forces.addRegistry(f1, p1);
	SpringGenerator* f2 = new SpringGenerator(1, 10, p1, "spring2");
	f2->setActive();
	forces.addRegistry(f2, p2);
	particles.push_back(p1);
	particles.push_back(p2);

}

void ParticleSystem::anchoredSystem()
{
	Particle* p = new Particle({ 0,0,0 }, { 0,0,0 }, 0.99, { 0,0,0 }, 5, 20);
	AnchoredSpring* spring = new AnchoredSpring(1, 1, Vector3(0, 10, 0), "anchor1");
	forces.addRegistry(spring, p);
	DragGenerator* drag = new DragGenerator(0.5, "drag1");
	forces.addRegistry(drag, p);
	particles.push_back(p);
	forceGenerators.push_back(drag);
	forceGenerators.push_back(spring);
}

void ParticleSystem::buoyancySystem() {
	Particle* liquid = new Particle({ 0,0,0 }, { 0,0,0 }, 0.99, { 0,0,0 }, 0, 20, CreateShape(physx::PxBoxGeometry(20, 2, 20)));
	liquid->setColor(Vector4(0, 0, 1, 1));
	Particle* p = new Particle({ 0,-5, 0 }, { 0,0,0 }, 0.99, { 0,0,0 }, 5, 20, CreateShape(physx::PxBoxGeometry(3, 3, 3)));
	BuoyancyGenerator* bg = new BuoyancyGenerator(5, 27, 1, liquid, "boya1");
	forces.addRegistry(bg, p);
	forceGenerators.push_back(bg);
	particles.push_back(p);
}

ParticleGenerator* ParticleSystem::getGenerator(string nombre)
{
	for (auto it = generators.begin(); it != generators.end();)
	{
		if ((*it)->getName() == nombre) {
			return (*it);
		}
		else
			it++;
	}
	return nullptr;
}

ForceGenerator* ParticleSystem::getForce(string nombre)
{
	for (auto it = forceGenerators.begin(); it != forceGenerators.end();)
	{
		if ((*it)->getName() == nombre) {
			return (*it);
		}
		else
			it++;
	}
	return nullptr;
}

void ParticleSystem::eraseGenerator(string nombre) {
	for (auto it = generators.begin(); it != generators.end();)
	{
		if ((*it)->getName() == nombre) {
			if((*it)->isActive())
				(*it)->setActive();
			it = generators.erase(it);
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
			if ((*it)->isActive())
				(*it)->setActive();
			it = forceGenerators.erase(it);
			it = forceGenerators.end();
		}		
		else
			it++;
	}
}
