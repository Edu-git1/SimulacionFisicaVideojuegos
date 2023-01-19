#include "ZaWarudo.h"

ZaWarudo::ZaWarudo(PxScene* scene, PxPhysics* physics)
{
	gScene = scene;
	gPhysics = physics;

	suelo = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(Vector3(100, .5, 100)));
	suelo->attachShape(*shape);
	scene->addActor(*suelo);
	sueloRender = new RenderItem(shape, suelo, { 0, 0, 1, 1 });
	cannon = new Cannon();
}

ZaWarudo::~ZaWarudo()
{
	for (auto it = forceGens.begin(); it != forceGens.end(); it = forceGens.erase(it)) {
		delete* it;
	}
	for (auto it = generators.begin(); it != generators.end(); it = generators.erase(it)) {
		delete* it;
	}
	for (auto it = solidParts.begin(); it != solidParts.end(); it = solidParts.erase(it)) {
		delete* it;
	}
}

void ZaWarudo::update(double t) {
	for (auto gen : generators) {
		SolidParticle* part = gen->generateParticles(t);
		if (part != nullptr)
		{
			solidParts.push_back(part);
			for (auto force : forceGens) {
				forces.addRegistry(force, part);
			}
		}
	}
	forces.updateForces(t);
	for (auto it = solidParts.begin(); it != solidParts.end();) {
		(*it)->update(t);
		if (!(*it)->isAlive()) {
			forces.deleteRigidRegistry(*it);
			delete (*it);
			it = solidParts.erase(it);
		}
		else {
			++it;
		}
	}
	cannon->update(t, GetCamera()->getEye(), GetCamera()->getDir());
}

void ZaWarudo::generatorDemo() {

	GaussianSolid* s = new GaussianSolid(gScene, gPhysics);
	s->setDevVel(Vector3{ 10,0,0 });
	s->setPos(Vector3{ 0,10,0 });
	generators.push_back(s);

	SolidWindGenerator* wind = new SolidWindGenerator({ 10,0,0 }, 1, .1);
	forceGens.push_back(wind);
}