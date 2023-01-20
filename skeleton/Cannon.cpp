#include "Cannon.h"

//Create a cannon that places a particle on its end and creates an explosion force to launch it 
Cannon::Cannon()
{
	posi = Vector3(0, 30, 0);
	pose = physx::PxTransform(posi);
	pose.q = physx::PxQuat(-45, physx::PxVec3(0, 1, 0));
	shape = CreateShape(physx::PxBoxGeometry(10, 5, 5));
	renderItem = new RenderItem(shape, &pose, { 0.3, 0.3, 0.3, 1 });
}

void Cannon::update(float t, Vector3 pos, physx::PxVec3 dir)
{
	posi = Vector3(pos.x - 10, pos.y - 10, pos.z - 16);
	pose = physx::PxTransform(posi);
	pose.q = physx::PxQuat(-45, physx::PxVec3(0, 1, 0));
}
