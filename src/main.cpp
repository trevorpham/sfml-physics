#include "sim/Simulation.h"
#include "sim/SimulationRegistry.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1280u, 720u }), "SFML Physics Simulations");
    window.setFramerateLimit(144);

    sim::SimulationRegistry& reg = sim::SimulationRegistry::instance();
    std::vector<std::string> list = reg.list();

    std::cout << "List of simulations available:\n";
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << i << ": " << list[i] << "\n";
    }
    std::cout << "Press a key from 1 through " << (list.empty() ? "1" : std::to_string(list.size())) << " to run that simulation. Press Esc to quit.\n";

    sim::Simulation* currentSim = nullptr;
    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
                int const keycode = static_cast<int>(key->scancode);
                std::cout << "Key Pressed: " << keycode << "\n";
                int constexpr keyOne  = static_cast<int>(sf::Keyboard::Scan::Num1);
                int constexpr keyZero = static_cast<int>(sf::Keyboard::Scan::Num0);

                if (key->scancode == sf::Keyboard::Scan::Escape) {
                    window.close();
                    break;
                }

                if (keycode >= keyOne && keycode <= keyZero) {
                    int index = keycode - keyOne;
                    if (index >= 0 && index < list.size()) {
                        if (currentSim) { delete currentSim; currentSim = nullptr; }
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

        float dt = std::min(0.0333f, clock.restart().asSeconds()); // time interval between frames
        if (currentSim) currentSim->update(dt);

        window.clear(sf::Color::White);
        if (currentSim) currentSim->render(window);
        window.display();
    }

    if (currentSim) { delete currentSim; currentSim = nullptr; }
    return 0;
}
