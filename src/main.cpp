#include "sim/Simulation.h"
#include "sim/SimulationRegistry.h"
#include "app/MainHelpers.h"
#include "config.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ app::config::kHDisplaySize, app::config::kVDisplaySize }), "SFML Physics Simulations");
    window.setFramerateLimit(app::config::kDisplayRate);

    sim::SimulationRegistry& reg = sim::SimulationRegistry::instance();
    std::vector<std::string> list = reg.list();

    std::cout << "List of simulations available:\n";
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << i << ": " << list[i] << "\n";
    }
    std::cout << "Press a key from 1 through " << (list.empty() ? "1" : std::to_string(list.size())) << " to run that simulation. Press Esc to quit.\n";

    sim::Simulation* currentSim = nullptr;
    sf::Clock clock;
    // The time taken to render each frame is added to this value. Once it reaches a user-specified threshold
    // the simulation will update its state and the value of that threshold is subtracted.
    float accumulatedTime = 0.f;

    while (window.isOpen()) {
        app::handleEvents(window, currentSim, list, reg);
        app::nextFrame(window, currentSim, clock, accumulatedTime);
    }

    if (currentSim) { app::unloadSim(currentSim); }
    return 0;
}
