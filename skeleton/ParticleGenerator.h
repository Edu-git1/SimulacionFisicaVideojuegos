#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include"Particle.h"
class ParticleGenerator {
public:
	virtual std::list<Particle*> generateParticles() = 0;
	virtual void setOrigin(Vector3 pose) { origin = physx::PxTransform(pose); };
	virtual physx::PxTransform getOrigin() { return origin; };

protected:
	physx::PxTransform origin { 0,0,0 };
};