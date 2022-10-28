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

protected:

	std::list<Particle*> particles;
	std::list<ParticleGenerator*> generators;
	Vector3 position;

	UniformParticleGenerator* uniformGenerator;
	bool uniformActive = false;
};