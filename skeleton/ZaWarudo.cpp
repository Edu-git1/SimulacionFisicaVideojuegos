#include "ZaWarudo.h"

ZaWarudo::ZaWarudo(PxScene* scene, PxPhysics* physics)
{
	gScene = scene;
	gPhysics = physics;

	suelo = gPhysics->createRigidStatic(PxTransform({ 20, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(Vector3(200, .5, 200)));
	suelo->attachShape(*shape);
	scene->addActor(*suelo);
	suelo->setName("suelo");
	sueloRender = new RenderItem(shape, suelo, { 0, 0, 1, 1 });
	cannon = new Cannon();
	particleSystem = new ParticleSystem({ 0,0,0 });
	
	windGenerator = new SolidWindGenerator({ 12,0, -15 }, 1, .5);
	forceGens.push_back(windGenerator);

	bouyancyGenerator = new SolidBuoyancy(1, 1, 0, 60);
	forceGens.push_back(bouyancyGenerator);
	boatGenerator = new GaussianBoats(gScene, gPhysics);
	//barco = new Barco(gScene, gPhysics, { 0, 0, 0 }, 8);
	//barcos.push_back(barco);
	//forces.addRegistry(windGenerator, barco->getBoat());
	//forces.addRegistry(windGenerator, barco->getSail());
	//forces.addRegistry(bouyancyGenerator, barco->getBoat());
}

ZaWarudo::~ZaWarudo()
{
	for (auto it = forceGens.begin(); it != forceGens.end(); it = forceGens.erase(it)) {
		delete* it;
	}
	for (auto it = barcos.begin(); it != barcos.end(); it = barcos.erase(it)) {
		delete* it;
	}
	for (auto it = solidParts.begin(); it != solidParts.end(); it = solidParts.erase(it)) {
		delete* it;
	}
}

void ZaWarudo::update(double t) {
	particleSystem->update(t);
	Barco* part = boatGenerator->generateParticles(t);
	if (part != nullptr)
	{
		barcos.push_back(part);
		forces.addRegistry(windGenerator, part->getBoat());
		forces.addRegistry(windGenerator, part->getSail());
		forces.addRegistry(bouyancyGenerator, part->getBoat());
	}
	forces.updateForces(t);
	for (auto it = solidParts.begin(); it != solidParts.end();) {
		if ((*it)->isAlive()) {
			(*it)->update(t);
		}
		if (!(*it)->isAlive()) {
			forces.deleteRigidRegistry((*it)->getBody());
			delete (*it);
			it = solidParts.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto it = barcos.begin(); it != barcos.end();) {
		if ((*it)->isAlive()) {
			(*it)->update(t);
		}
		if (!(*it)->isAlive()) {
			forces.deleteRigidRegistry((*it)->getBoat());
			forces.deleteRigidRegistry((*it)->getSail());
			delete (*it);
			it = barcos.erase(it);
		}
		else
			++it;
	}
	cannon->update(t, GetCamera()->getEye(), GetCamera()->getDir());
	if (shot > 0) shot--;
}

void ZaWarudo::generatorDemo() {

	/*GaussianSolid* s = new GaussianSolid(gScene, gPhysics);
	s->setDevVel(Vector3{ 10,0,0 });
	s->setPos(Vector3{ 0,10,0 });
	generators.push_back(s);

	SolidWindGenerator* wind = new SolidWindGenerator({ 10,0,0 }, 1, .1);
	forceGens.push_back(wind);*/
}

void ZaWarudo::shoot()
{
	if (shot <= 0) {
		Shape s = Sphere;

		SolidParticle* fire = new SolidParticle(gScene, gPhysics, cannon->getPos() + Vector3(-2.5, 3, -4), Vector3(0, 0, 0), 10, 5, Vector3(2, 2, 2), s, Vector4(0, 0, 0, 1));

		//crea una particula solida en la punta del cañon y genera una explosion para dispararla

		SolidExplosionGenerator* exp = new SolidExplosionGenerator(cannon->getPos() - Vector3(-1.3, 3.5, -2), 10.f, 3000.f, 0.15);
		forces.addRegistry(exp, fire->getBody());
		fire->getBody()->setName("bala");
		solidParts.push_back(fire);

		shot = 1000;
	}
}

void ZaWarudo::hit(physx::PxActor* actor1, physx::PxActor* actor2)
{
	SolidParticle* bala;
	for (auto it = solidParts.begin(); it != solidParts.end(); it++) {
		if ((*it)->getBody() == actor1 || (*it)->getBody() == actor2) {
			bala = (*it);
			(*it)->setAlive(false);
			if (actor1->getName() == "suelo" || actor2->getName() == "suelo"){
				particleSystem->fireworkSystem(bala->getPosition(), { 0,0,1,1 });
			}
			else {
				for (auto it = barcos.begin(); it != barcos.end(); it++) {
					if ((*it)->getBoat() == actor1 || (*it)->getBoat() == actor2) {
						(*it)->setAlive(false);
						particleSystem->fireworkSystem(bala->getPosition(), (*it)->getBoatRender()->color);
					}
					else if ((*it)->getSail() == actor1 || (*it)->getSail() == actor2) {
						(*it)->setAlive(false);
						particleSystem->fireworkSystem(bala->getPosition(), (*it)->getSailRender()->color);
					}
				}
			}
		}
	}
}
