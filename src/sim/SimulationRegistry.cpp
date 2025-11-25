#include "sim/SimulationRegistry.h"
#include <map>
#include <string>
#include <vector>

// call this instead of the constructor. creates a SimulationRegistry on first call.
// subsequent calls return the initially created object; it does not create another.
// ensures only one instance of SimulationRegistry exists (singleton pattern)
sim::SimulationRegistry& sim::SimulationRegistry::instance()
{
    static SimulationRegistry s_instance;
    return s_instance;
}

// register a sim by passing in a string id and a factory function
// each physics .cpp file in directory src/sim registers itself through this method
bool sim::SimulationRegistry::registerSimulation(const std::string &id, Factory factory)
{
    if (factories_.find(id) != factories_.end())
        return false;
    factories_[id] = factory;
    return true;
}

// create a Simulation from one of the registered factories
sim::Simulation* sim::SimulationRegistry::create(const std::string &id)
{
    auto f = factories_.find(id);
    if (f == factories_.end())
        return nullptr;
    return (f->second)();
}

// get registered ids
std::vector<std::string> const sim::SimulationRegistry::list()
{
    std::vector<std::string> ids;
    for (const auto &f : factories_)
        ids.push_back(f.first);
    return ids;
}