#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include "SolidGenerator.h"
#include "ForceGenerator.h"
#include "ForceRegistry.h"
#include "Cannon.h"

using namespace physx;
using namespace std;


class ZaWarudo
{
public:
	ZaWarudo(physx::PxScene* scene, physx::PxPhysics* physics);
	void update(double t);
	void generatorDemo();
	~ZaWarudo();
protected:
	PxScene* gScene;
	PxPhysics* gPhysics;
	list<SolidParticle*> solidParts;
	list<SolidForceGenerator*> forceGens;
	list<SolidGenerator*> generators;
	SolidForceRegistry forces;
	SolidGenerator* gen = nullptr;
	PxRigidStatic* suelo;
	RenderItem* sueloRender;
	Cannon* cannon;
};