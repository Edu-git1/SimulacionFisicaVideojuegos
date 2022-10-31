#include "RenderUtils.hpp"
#include "core.hpp"
#include "Particle.h"
#include "PxPhysicsAPI.h"
#include "ParticleGenerator.h"
#include <vector>
#include <string>
#include <list>
#include <memory>

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
};