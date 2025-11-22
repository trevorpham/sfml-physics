#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace sim {

class Simulation {
public:
	virtual ~Simulation() = default;
	virtual std::string const name() = 0;
	virtual void init(sf::RenderWindow& window) = 0;
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};

}