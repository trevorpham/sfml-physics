#pragma once

#include "sim/Simulation.h"
#include "sim/SimulationRegistry.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace app {

void handleEvents(sf::RenderWindow& window,
    sim::Simulation*& currentSim,
    const std::vector<std::string>& list,
    sim::SimulationRegistry& reg);

void nextFrame(sf::RenderWindow& window,
    sim::Simulation*& currentSim,
    sf::Clock& clock,
    float& accumulator);

void printInstructions();

void unloadSim(sim::Simulation*& s);

}