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
	void activateFountain() { uniformActive = !uniformActive; };
	bool isFountainActive() { return uniformActive; };

	void fogSystem();
	void activateFog() { gaussActive = !gaussActive; };
	bool isFogActive() { return gaussActive; };

	void fireworkSystem();
	void fireworkGeneratorSystem();
	void activateFirework() { fireworkActive = !fireworkActive; };
	bool isFireworkActive() { return fireworkActive; };
	void gravitySystem();

protected:

	std::list<Particle*> particles;
	std::list<ParticleGenerator*> generators;
	Vector3 position;

	UniformParticleGenerator* uniformGenerator;
	bool uniformActive = false;

	GaussianParticleGenerator* gaussianGenerator;
	bool gaussActive = false;

	FireworkGenerator* fireworkGenerator;
	bool fireworkActive = false;
	float countdown = 0;
	Particle* particleBase;

	ForceRegistry forces;
};