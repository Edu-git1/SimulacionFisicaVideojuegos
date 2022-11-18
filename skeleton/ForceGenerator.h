#pragma once
#include "Particle.h"
#include <list>
#include <string>
using namespace std;

class ForceGenerator
{
public:
	virtual void updateForce(Particle* part, double duracion) = 0;
	string name;
protected:
	double time = -1;
};

class GravityGenerator : public ForceGenerator {
public:
	GravityGenerator(Vector3& gravity, double t);
	~GravityGenerator() {};
	void updateForce(Particle* part, double duracion) override;
protected:
	Vector3 gravedad;
};
