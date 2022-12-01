#pragma once
#include "Particle.h"
#include <list>
#include <string>
using namespace std;

class ForceGenerator
{
public:
	virtual void updateForce(Particle* part) = 0;
	string name;
	virtual bool isActive() { return active; };
	virtual void setActive() { active = !active; };
	string getName() { return name; };
protected:
	bool active = false;
	double time = -1;
};

class GravityGenerator : public ForceGenerator {
public:
	GravityGenerator(Vector3& gravity, double t, string nombre);
	virtual ~GravityGenerator() {};
	void updateForce(Particle* part) override;
protected:
	Vector3 gravedad;
};

class DragGenerator : public ForceGenerator {
public:
	DragGenerator(float k, string nombre) : k(k) { name = nombre; };
	virtual ~DragGenerator() {};
	void updateForce(Particle* part) override;
protected:
	float k;
};

class WindGenerator : public ForceGenerator {
public:
	WindGenerator(Vector3& vel, float k1, float k2, string nombre) : velocidad(vel), _k1(k1), _k2(k2) { name = nombre; };
	virtual ~WindGenerator() {};
	void updateForce(Particle* part) override;
protected:
	Vector3 velocidad;
	float _k1;
	float _k2;
};

class WhirlwindGenerator : public WindGenerator {
public:
	WhirlwindGenerator(Vector3 center, float k1, float k2, float kt, string nombre) : WindGenerator(Vector3(0), k1, k2, ""), ojo(center), _Kt(kt) { name = nombre; };
	~WhirlwindGenerator() {};
	void updateForce(Particle* part) override;
protected:
	Vector3 ojo;
	float _Kt;
};

class ExplosionGenerator : public ForceGenerator {
public:
	ExplosionGenerator(Vector3 centro, float radius, float k, double kt, string nombre) : center(centro), radio(radius), _k(k), _kt(kt), tiempo(0.0) { name = nombre; };
	~ExplosionGenerator() {};
	void updateForce(Particle* part) override;
protected:
	Vector3 center;
	float radio;
	float _k;
	double _kt;
	double tiempo;
};

class SpringGenerator : public ForceGenerator {
public:
	SpringGenerator(double k, double restingLength, Particle* otra, string nombre) : _k(k), resting_length(restingLength), other(otra) { name = nombre; };
	~SpringGenerator() {};
	void updateForce(Particle* part) override;
	inline void setK(double k) { _k = k; };
protected:
	double _k;
	double resting_length;
	Particle* other;
};


class AnchoredSpring : public SpringGenerator {
public:
	AnchoredSpring(double k, double restingLength, const Vector3& anchorPos, string nombre): SpringGenerator(k, restingLength, nullptr, "") {
		name = nombre;
		other = new Particle(anchorPos, { 0,0,0 }, 0, { 0,0,0 }, 0, 100);
	};
	virtual ~AnchoredSpring() { delete other; };
};


class BungeeGenerator : public SpringGenerator {
public:
	BungeeGenerator(double k, double resting_length, Particle* other, string nombre): SpringGenerator(k, resting_length, other, "") {};
	virtual ~BungeeGenerator() {};
	void updateForce(Particle* part) override;
};

class BuoyancyGenerator : public ForceGenerator {
public:
	BuoyancyGenerator(float h, float v, float d, Particle* liquid_surface, string nombre) :
		height(h), volume(v), density(d), liquid_particle(liquid_surface)
	{
		name = nombre;
	};
	virtual ~BuoyancyGenerator() {};
	void updateForce(Particle* part) override;

protected:
	float height;
	float volume;
	float density;
	Particle* liquid_particle;
};

