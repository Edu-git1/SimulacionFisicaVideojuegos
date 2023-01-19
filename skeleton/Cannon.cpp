#include "Cannon.h"

//Create a cannon that places a particle on its end and creates an explosion force to launch it 
Cannon::Cannon()
{
	pose = physx::PxTransform(0, 0, 0);
	pose.q = physx::PxQuat(-45, physx::PxVec3(0, 1, 0));
	shape = CreateShape(physx::PxBoxGeometry(10, 5, 5));
	renderItem = new RenderItem(shape, &pose, { 16, 16, 16, 1 });
}

void Cannon::update(float t, Vector3 pos, PxVec3 dir)
{
	pose = physx::PxTransform(pos.x-10, pos.y-10, pos.z-16);
	pose.q = physx::PxQuat(-45, physx::PxVec3(0, 1, 0));
}
