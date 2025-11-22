#pragma once

#include "Simulation.h"
#include <map>
#include <string>
#include <vector>

namespace sim {

class SimulationRegistry {
public:
	// create a type-alias named Factory whose type is pointer to function of return type Simulation *
	typedef Simulation* (*Factory)();

	// call this instead of the constructor. creates a SimulationRegistry on first call.
	// subsequent calls return the initially created object; it does not create another.
	// ensures only one instance of SimulationRegistry exists (singleton pattern)
	static SimulationRegistry& instance() {
		static SimulationRegistry s_instance;
		return s_instance;
	}

	// register a sim by passing in a string id and a factory function 
	// each physics .cpp file in directory src/sim registers itself through this method
	bool registerSimulation(const std::string& id, Factory factory) {
		if (factories_.find(id) != factories_.end()) return false;
		factories_[id] = factory;
		return true;
	}

	// create a Simulation from one of the registered factories
	Simulation* create(const std::string& id) {
		auto f = factories_.find(id);
		if (f == factories_.end()) return nullptr;
		return (f->second)();
	}

	// get registered ids
	std::vector<std::string> const list() {
		std::vector<std::string> ids;
		for (const auto& f : factories_) ids.push_back(f.first);
		return ids;
	}

private:
	// constructor can only be called through the instance() method
	SimulationRegistry() = default;
	// disable copy constructor
	SimulationRegistry(const SimulationRegistry&) = delete;
	// disable move operation
	SimulationRegistry& operator=(const SimulationRegistry&) = delete;
	std::map<std::string, Factory> factories_;
};

}