#ifndef __PARTICULAGENERATOR_H__
#define __PARTICULAGENERATOR_H__


#include "core.hpp"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include <list>
#include <random>
#include <complex>
#include <vector>
#include <string>

using namespace std;

class Particle;
class ParticleGenerator {
public:
	virtual list<Particle*> generateParticle() = 0;
	~ParticleGenerator();
	void setParticle(Particle* part) { particle = part; };
	virtual void setOrigin(Vector3 pose) { origin = physx::PxTransform(pose); };
	virtual physx::PxTransform getOrigin() { return origin; };
	void setAlive() { alive = !alive; };
	bool isAlive() { return alive; };
	string getName() { return name; };
	default_random_engine generation;
	uniform_real_distribution<> unimDist{ -1,1 };
	normal_distribution<> normalDist{ 0.5, 0.5 };

protected:
	physx::PxTransform origin{ 0,0,0 };
	Particle* particle;
	bool alive = false;
	std::string name;
	Vector3 pos;
	Vector3 vel;
	Vector3 acc;
	double probability;
	int nParticles;
};

class UniformParticleGenerator : public ParticleGenerator
{
public:

	UniformParticleGenerator(Particle* part, double probab, Vector3 pose, Vector3 veloci, int num);
	std::list<Particle*> generateParticle() override;
protected:

	bool uniformActive;
	Vector3 uniformPos, uniformVel;
	std::mt19937 rng;

};

#endif