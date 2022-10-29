#include "ParticleGenerator.h"
#include "Particle.h"

using namespace std;
ParticleGenerator::~ParticleGenerator()
{
	if (particle != nullptr)
	{
		delete particle;
		particle = nullptr;
	}
}

UniformParticleGenerator::UniformParticleGenerator(Particle* part, double probab, Vector3 pose, Vector3 veloci, int num)
{
	name = "fuente";
	particle = part;
	nParticles = num;

	uniformPos = pose / 3;
	uniformVel = veloci / 3;
	pos = particle->getPos();
	vel = particle->getVel();

	probability = probab;
	random_device random;
	rng = mt19937(random());
	uniformActive = false;
}

list<Particle*> UniformParticleGenerator::generateParticle()
{
	list<Particle*> listParticles;

	if (particle == nullptr)
		return listParticles;

	auto gen = uniform_int_distribution<int>(0, 100);
	auto px = uniform_real_distribution<float>(pos.x - uniformPos.x / 2, pos.x + uniformPos.x / 2);
	auto py = uniform_real_distribution<float>(pos.y - uniformPos.y / 2, pos.y + uniformPos.y / 2);
	auto pz = uniform_real_distribution<float>(pos.z - uniformPos.z / 2, pos.z + uniformPos.z / 2);
	auto vx = uniform_real_distribution<float>(vel.x - uniformVel.x / 2, vel.x + uniformVel.x / 2);
	auto vy = uniform_real_distribution<float>(vel.y - uniformVel.y / 2, vel.y + uniformVel.y / 2);
	auto vz = uniform_real_distribution<float>(vel.z - uniformVel.z / 2, vel.z + uniformVel.z / 2);

	for (int i = 0; i < nParticles; i++)
	{
		double cr = gen(rng);

		if (cr <= probability)
		{
			Vector3 pos = { px(rng), py(rng), pz(rng) };
			Vector3 vel = { vx(rng), vy(rng), vz(rng) };

			Particle* p = new Particle(particle->getPos(), particle->getVel(), particle->getDamp(), particle->getAcc(), particle->getMass(), particle->getTime());
			p->setVelocity(vel);
			p->setPosition(pos);
			//p->setColor(Vector4{ 0.0f, 0.0f, 1.f, 1 });
			listParticles.push_back(p);
		}
	}

	return listParticles;
}
