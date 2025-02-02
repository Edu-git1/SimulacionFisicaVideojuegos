#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include <memory>
#include "ParticleGenerator.h"
#include <iostream>
using namespace std;

class Particle {
public:
	Particle(Vector3 pos, Vector3 vel, double damp, Vector3 aceleracion, float mass, double time, physx::PxShape* sh = CreateShape(physx::PxSphereGeometry(1)));

	virtual ~Particle();

	void Update(double t);

	void setPosition(Vector3 pos) { posi = pos; };
	void setMass(float mass) { masa = mass; };
	void setVelocity(Vector3 vel) { velocidad = vel; };
	void setAcceleration(Vector3 ace) { acc = ace; };
	void setDamping(double damping) { damp = damping; };
	Vector3 getPos() { return posi; };
	Vector3 getVel() { return velocidad; };
	Vector3 getAcc() { return acc; };
	double getMass() { return masa; };
	double getDamp() { return damp; };
	double getTime() { return startTime; };
	Vector4 getColor() { return renderItem->color; };
	void decreaseTime() { startTime--; };
	void setColor(Vector4 color) { renderItem->color = color; };
	bool isAlive() { return alive; };
	void addForce(Vector3 force) { fuerza += force; };
	void eraseForce() { fuerza = Vector3{ 0, 0, 0 }; };
	void deregister(){
		DeregisterRenderItem(renderItem);
		renderItem = nullptr;
	}

private:

	double damp;
	Vector3 velocidad;
	Vector3 acc;
	Vector3 posi;
	Vector3 fuerza = {0, 0, 0};
	physx::PxTransform pose;
	physx::PxShape* shape;
	RenderItem* renderItem;
	float masa;
	double startTime = 0;
	bool alive = true;
};

class Firework : public Particle
{
public:

	Firework(Particle* part, shared_ptr<ParticleGenerator> gen) : Particle(part->getPos(), part->getVel(), part->getDamp(), part->getAcc(), part->getMass(), part->getTime()), generator(gen) {}
	virtual ~Firework() {};

	list<Particle*> explosiones()
	{
		list<Particle*> lista;
		for (auto p : generator->generateParticle())
				lista.push_back(p);
		return lista;
	}
	void updateGenerator(shared_ptr<ParticleGenerator> gen) { generator = gen; };

protected:
	shared_ptr<ParticleGenerator> generator;
};

