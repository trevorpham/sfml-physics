#include "sim/Simulation.h"
#include "sim/SimulationRegistry.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

namespace {

class BallWithinBoxCollision : public sim::Simulation {
private:
	sf::CircleShape shape_;
	sf::Vector2f velocity_;
	sf::Vector2u boxSize_{ 800, 600 };
public:
	BallWithinBoxCollision() {
		velocity_ = sf::Vector2f(140.f, 100.f);
	}

	std::string name() const override { return "Ball Within Box Collision"; }

	void init(sf::RenderWindow& window) override {
		boxSize_ = window.getSize();
		shape_.setRadius(12.f);
		shape_.setFillColor(sf::Color::Blue);
		shape_.setPosition(sf::Vector2(
			static_cast<float>(boxSize_.x) / 2.f,
			static_cast<float>(boxSize_.y) / 2.f
		));
	}

	void update(float dt) override {
		sf::Vector2f pos = shape_.getPosition();
		// calculate preliminary new position then check for collision
		pos += velocity_ * dt;

		// collision with a wall causes the velocity component that caused the impact to be inverted
		// collision with left-hand boundary
		if (pos.x < 0.f) { pos.x = 0.f; velocity_.x = std::abs(velocity_.x); }
		// collision with top boundary
		if (pos.y < 0.f) { pos.y = 0.f; velocity_.y = std::abs(velocity_.y); }
		// collision with right-hand boundary
		if (pos.x > static_cast<float>(boxSize_.x)) { pos.x = static_cast<float>(boxSize_.x); velocity_.x = -std::abs(velocity_.x); }
		// collision with bottom boundary
		if (pos.y > static_cast<float>(boxSize_.y)) { pos.y = static_cast<float>(boxSize_.y); velocity_.y = -std::abs(velocity_.y); }

		shape_.setPosition(pos);
	}

	void render(sf::RenderWindow& window) override { window.draw(shape_); }
};

struct Registrar {
	Registrar() {
		bool registered = sim::SimulationRegistry::instance()
			.registerSimulation("ball_within_box_collision", []() -> sim::Simulation* {
				return new BallWithinBoxCollision();
			});
		std::cout << (registered ? "Success" : "Failed") << ": Register ball_within_box_collision\n";
	}
};

static Registrar registrar;

} // anonymous namespace