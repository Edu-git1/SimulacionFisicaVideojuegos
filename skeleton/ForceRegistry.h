#pragma once
#include "ForceGenerator.h"
#include <map>
using namespace std;

typedef pair<ForceGenerator*, Particle*> Par;

class ForceRegistry : public multimap<ForceGenerator*, Particle*>
{
public:

	bool alreadyRegistered(ForceGenerator* generator, Particle* part) {
		for (auto it = begin(); it != end();) {
			if (it->first == generator && it->second == part) {
				return true;
			}
			else
				it++;
		}
		return false;
	}

	void updateForces(float duracion) {
		for (auto it = begin(); it != end(); ++it) {
			it->first->updateForce(it->second);
		}
	}

	void addRegistry(ForceGenerator* generator, Particle* part) {
		if(!alreadyRegistered(generator, part))
			insert({ generator, part });
	}

	void eraseRegistry(Particle* part) {
		for (auto it = begin(); it != end();) {
			if (it->second == part) {
				it = erase(it);
			}
			else
				it++;
		}
	}
};
