#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include "SolidGenerator.h"
#include "ForceGenerator.h"
#include "ForceRegistry.h"
#include "Cannon.h"
#include "ParticleSystem.h"
#include "Barco.h"


using namespace physx;
using namespace std;

class ZaWarudo
{
public:
	ZaWarudo(physx::PxScene* scene, physx::PxPhysics* physics);
	void update(double t);
	void generatorDemo();
	void shoot();
	void hit(physx::PxActor* actor1, physx::PxActor* actor2);
	~ZaWarudo();
protected:
	PxScene* gScene;
	PxPhysics* gPhysics;
	list<SolidParticle*> solidParts;
	list<SolidForceGenerator*> forceGens;
	SolidForceRegistry forces;
	SolidGenerator* gen = nullptr;
	PxRigidStatic* suelo;
	RenderItem* sueloRender;
	Cannon* cannon;
	ParticleSystem* particleSystem = nullptr;
	Particle* fireworkBase;
	SolidWindGenerator* windGenerator;
	SolidBuoyancy* bouyancyGenerator;
	GaussianBoats* boatGenerator;
	list<Barco*> barcos;
	Barco* barco;
	
	int shot = 0;
	int switchWind = 0;
};