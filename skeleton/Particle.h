#include "core.hpp"
#include "RenderUtils.hpp"

enum shotType { PISTOL, FIREBALL, CANONBALL };

class Particle {
public:
	Particle(Vector3 pos, Vector3 vel, double damp, Vector3 aceleracion, double mass, double time);

	~Particle();

	void Update(double t);

	void setPosition(physx::PxTransform pos) { pose = pos; };
	void setMass(double mass) { masa = mass; };
	void setVelocity(Vector3 vel) { velocidad = vel; };
	void setAcceleration(Vector3 ace) { acc = ace; };
	void setDamping(double damping) { damp = damping; };
	Vector3 getPosition() { return posi; };
	double getTime() { return startTime; };
	void decreaseTime() { startTime--; };
	void setColor(Vector4 color) { renderItem->color = color; };

private:

	double damp;
	Vector3 velocidad;
	Vector3 acc;
	Vector3 posi;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double masa;
	double startTime = 0;
};