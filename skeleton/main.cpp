#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "ParticleSystem.h"
//#include "Particle.h"

#include <iostream>


using namespace physx;
using namespace std;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;

PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;

ParticleSystem* particleSystem = NULL;

Particle* gParticula = NULL;

vector<Particle*> proyectiles;

vector<Particle*> particles;

shotType currentShot = PISTOL;

ContactReportCallback gContactReportCallback;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;

	gScene = gPhysics->createScene(sceneDesc);

	particleSystem = new ParticleSystem({ 0,0,0 });
	particleSystem->gravitySystem();
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	particleSystem->update(t);

	for (int i = 0; i < proyectiles.size(); i++) {
		proyectiles[i]->Update(t);
		if (proyectiles[i]->getPos().y < 0.0f || proyectiles[i]->getTime() <= 0 || proyectiles[i]->getPos().z > 200.0f) {
			delete proyectiles[i];
			proyectiles.erase(proyectiles.begin() + i);
		}
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	delete particleSystem;
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (key)
	{
		//case 'B': break;
		//case ' ':	break;
	case ' ':
	{
		break;
	}
	case 'p':
		if (currentShot == PISTOL) {
			currentShot = FIREBALL;
		}
		else if (currentShot == FIREBALL) {
			currentShot = CANONBALL;
		}
		else {
			currentShot = PISTOL;
		}
		break;
	case 'q':
	{
		Vector3 eye = GetCamera()->getEye();
		Vector3 dir = GetCamera()->getDir();
		switch (currentShot) {
		case PISTOL:
		{
			Particle* bullet = new Particle(eye, dir * 80.f, 0.99f, Vector3(0, -1.f, 0), 2.f, 5000);
			bullet->setColor(Vector4(0, 1, 0, 1));
			proyectiles.push_back(bullet);
			break;
		}
		case FIREBALL:
		{
			Particle* bullet = new Particle(eye, dir * 10.f, 0.9f, Vector3(0, 0.6f, 0), 1.f, 5000);
			bullet->setColor(Vector4(1, 0, 0, 1));
			proyectiles.push_back(bullet);
			break;
		}
		case CANONBALL:
		{
			Particle* bullet = new Particle(eye, dir * 35.f, 0.99f, Vector3(0, -9.8f, 0), 200.f, 5000);
			bullet->setColor(Vector4(0, 0, 1, 1));
			proyectiles.push_back(bullet);
			break;
		}
		break;
		}
		break;
	}
	case 'g':
	{
		particleSystem->activateFountain();
		if (particleSystem->isFountainActive())
			particleSystem->fountainSystem();
		break;
	}
	case 'f':
	{
		particleSystem->activateFog();
		if (particleSystem->isFogActive())
			particleSystem->fogSystem();
		break;
	}
	case 'm':
		particleSystem->fireworkSystem();
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}