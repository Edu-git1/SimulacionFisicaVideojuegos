#pragma once
#include "Particle.h"
#include "SolidParticle.h"
#include "core.hpp"
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
	WhirlwindGenerator(Vector3 center, float k1, float k2, float kt, double radio, string nombre) : WindGenerator(Vector3(0), k1, k2, ""), ojo(center), _Kt(kt), radius(radio) { name = nombre; };
	~WhirlwindGenerator() {};
	void updateForce(Particle* part) override;
protected:
	Vector3 ojo;
	float _Kt;
	double radius;
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
	SpringGenerator(double k, double restingLength, Particle* otra, double min, double max, double rup, string nombre) : _k(k), resting_length(restingLength), other(otra), minX(min), maxX(max), rupturaX(rup) { name = nombre; };
	~SpringGenerator() {};
	void updateForce(Particle* part) override;
	inline void setK(double k) { _k = k; };
protected:
	double _k;
	double resting_length;
	double minX;
	double maxX;
	double rupturaX;
	Particle* other;
};


class AnchoredSpring : public SpringGenerator {
public:
	AnchoredSpring(double k, double restingLength, const Vector3& anchorPos, double min, double max, double rup, string nombre): SpringGenerator(k, restingLength, nullptr, min, max, rup, "") {
		name = nombre;
		other = new Particle(anchorPos, { 0,0,0 }, 0, { 0,0,0 }, 0, 100);
	};
	virtual ~AnchoredSpring() { delete other; };
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

class SolidForceGenerator
{
public:
	virtual void updateForce(PxRigidBody* rb, double t) = 0;
	std::string name;
	double t = -1;
};

class SolidWindGenerator : public SolidForceGenerator {
public:
	SolidWindGenerator(Vector3 windVel, float k1, float k2);
	void updateForce(PxRigidBody* rb, double t) override;
	void changeWind() { _windVel = -_windVel; };
protected:
	float _k1, _k2;
	Vector3 _windVel;
};

class SolidExplosionGenerator : public SolidForceGenerator {
public:
	SolidExplosionGenerator(Vector3 centro, float radius, float k, double kt) : center(centro), radio(radius), _k(k), _kt(kt), tiempo(0.0) {};
	~SolidExplosionGenerator() {};
	void updateForce(PxRigidBody* part, double t) override;
protected:
	Vector3 center;
	float radio;
	float _k;
	double _kt;
	double tiempo;
};

class SolidBuoyancy : public SolidForceGenerator {
public:
	SolidBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity = 1000.0f, float viscosity = 0.5f) {
		_maxDepth = maxDepth;
		_volume = volume;
		_waterHeight = waterHeight;
		_liquidDensity = liquidDensity;
		_viscosity = viscosity;
		name = "Buoyancy";
	};
	void updateForce(PxRigidBody* rb, double t) override;
	Vector3 calcForce(float depth, PxRigidBody* rb);

protected:
	float _maxDepth, _volume, _waterHeight, _liquidDensity, _viscosity;

};

