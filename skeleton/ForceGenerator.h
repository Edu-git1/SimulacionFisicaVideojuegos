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
	virtual bool isActive() { return active; };
	virtual void setActive() { active = !active; };
protected:
	bool active = false;
	double time = -1;
};

class GravityGenerator : public ForceGenerator {
public:
	GravityGenerator(Vector3& gravity, double t);
	virtual ~GravityGenerator() {};
	void updateForce(Particle* part, double duracion) override;
protected:
	Vector3 gravedad;
};

class DragGenerator : public ForceGenerator {
public:
	DragGenerator(float k) : k(k) { name = "drag"; };
	virtual ~DragGenerator() {};
	void updateForce(Particle* part, double duracion) override;
protected:
	float k;
};

class WindGenerator : public ForceGenerator {
public:
	WindGenerator(Vector3& vel, float k1, float k2) : velocidad(vel), _k1(k1), _k2(k2) { name = "wind"; };
	virtual ~WindGenerator() {};
	void updateForce(Particle* part, double duracion) override;
protected:
	Vector3 velocidad;
	float _k1;
	float _k2;
};

class WhirlwindGenerator : public WindGenerator {
public:
	WhirlwindGenerator(Vector3 center, float k1, float k2, float kt) : WindGenerator(Vector3(0), k1, k2), ojo(center), _Kt(kt) { name = "whirldwind"; };
	~WhirlwindGenerator() {};
	void updateForce(Particle* part, double duracion) override;
protected:
	Vector3 ojo;
	float _Kt;
};

