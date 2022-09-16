#include "core.hpp"
#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3 pos, Vector3 vel);

	~Particle();

	void Update(double t);

private:

	Vector3 velocidad;
	physx::PxTransform pose;
	RenderItem* renderItem;
};