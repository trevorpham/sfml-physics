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
	static SimulationRegistry& instance();
	bool registerSimulation(const std::string& id, Factory factory);
	Simulation* create(const std::string& id);
	std::vector<std::string> const list();

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