#include "RenderUtils.hpp"
#include "core.hpp"
#include "PxPhysicsAPI.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include "ForceRegistry.h"
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;


class ParticleSystem
{
public:

	ParticleSystem(Vector3 pos) { position = pos; }
	~ParticleSystem();
	void update(double t);

	ParticleGenerator* getParticleGenerator(string name);
	void fountainSystem();
	void activateFountain() { fountainGenerator->setActive(); };
	bool isFountainActive() { return fountainGenerator->isActive(); };

	void fogSystem();
	void activateFog() { fogGenerator->setActive(); };
	bool isFogActive() { return fogGenerator->isActive(); };

	void fireworkSystem();
	void fireworkGeneratorSystem();
	void activateFirework() { fireworkGenerator->setActive(); };
	bool isFireworkActive() { return fireworkGenerator->isActive(); };

	void gravitySystem();
	void activateGravity() { gravityGenerator->setActive(); };
	bool isGravityActive() { return gravityGenerator->isActive(); };

	void dragSystem();
	void activateDrag() { dragGenerator->setActive(); };
	bool isDragActive() { return dragGenerator->isActive(); };

	void windSystem();
	void activateWind() { windGenerator->setActive(); };
	bool isWindActive() { return windGenerator->isActive(); };

	void whirlwindSystem();
	void activateWhirlwind() { whirlwindGenerator->setActive(); };
	bool isWhirlwindActive() { return whirlwindGenerator->isActive(); };

	void explosionSystem();

	void eraseGenerator(string nombre);
	void eraseForce(string nombre);

protected:

	std::list<Particle*> particles;
	std::list<ParticleGenerator*> generators;
	Vector3 position;

	UniformParticleGenerator* fountainGenerator;

	GaussianParticleGenerator* fogGenerator;

	FireworkGenerator* fireworkGenerator;
	float countdown = 0;
	Particle* particleBase;

	ForceRegistry forces;

	std::list<ForceGenerator*> forceGenerators;
	GravityGenerator* gravityGenerator;
	WindGenerator* windGenerator;
	DragGenerator* dragGenerator;
	WhirlwindGenerator* whirlwindGenerator;
};