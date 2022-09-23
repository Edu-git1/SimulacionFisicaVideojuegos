#include "core.hpp"
#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3 pos, Vector3 vel, double damp, double aceleracion, double mass);

	~Particle();

	virtual void Update(double t);

private:

	double damp;
	Vector3 velocidad;
	double acc;
	Vector3 posi;
	physx::PxTransform pose;
	RenderItem* renderItem;
};