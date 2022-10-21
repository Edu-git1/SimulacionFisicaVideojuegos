#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>

class Particle;
class ParticleGenerator;

class PartycleSystem {
public:
	std::list<Particle*> particles;
	ParticleGenerator* generator;
	void update(double t);
	void generateParticle();

protected:
	bool outOfBounds(Particle* particle);
};