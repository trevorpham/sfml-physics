#include "app/MainHelpers.h"
#include "config.h"
#include <iostream>
#include <algorithm>

namespace app {

void handleEvents(sf::RenderWindow& window,
    sim::Simulation*& currentSim,
    const std::vector<std::string>& list,
    sim::SimulationRegistry& reg)
{
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();
        if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
            int const keycode = static_cast<int>(key->scancode);
            std::cout << "Key Pressed: " << keycode << "\n";
            int constexpr keyOne = static_cast<int>(sf::Keyboard::Scan::Num1);
            int constexpr keyZero = static_cast<int>(sf::Keyboard::Scan::Num0);

            if (key->scancode == sf::Keyboard::Scan::Escape) {
                window.close();
                break;
            }

            if (keycode >= keyOne && keycode <= keyZero) {
                int index = keycode - keyOne;
                if (index >= 0 && index < list.size()) {
                    if (currentSim) { unloadSim(currentSim); }
                    currentSim = reg.create(list[index]);
                    if (currentSim) {
                        std::cout << "Loading simulation: " << list[index] << "\n";
                        currentSim->init(window);
                    }
                }
            }
            else {
                std::cout << "Keystroke is unregistered in this app.\n";
            }
        }
    }
}

void nextFrame(sf::RenderWindow& window, sim::Simulation*& currentSim, sf::Clock& clock, float& accumulatedTime)
{
    float frameTime = std::min(app::config::kMaxFrameTime, clock.restart().asSeconds());
    accumulatedTime += frameTime;

    while (accumulatedTime >= app::config::kFixedTimeStep) {
        if (currentSim) currentSim->update(app::config::kFixedTimeStep);
        accumulatedTime -= app::config::kFixedTimeStep;
    }

    window.clear(sf::Color::White);
    if (currentSim) currentSim->render(window);
    window.display();
}

void printInstructions() {

}

void unloadSim(sim::Simulation*& s) {
    delete s;
    s = nullptr;
}

}