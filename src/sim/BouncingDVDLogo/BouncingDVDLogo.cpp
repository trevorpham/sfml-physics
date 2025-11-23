#include "sim/Simulation.h"
#include "sim/SimulationRegistry.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <iostream>

namespace {

	class BouncingDVDLogo : public sim::Simulation {
	private:
		sf::RectangleShape shape_;
		float const width_{ 220.f };
		float const height_{ 150.f };
		sf::Vector2f const shapeSize_{ width_, height_ };
		float const speed_{ 230.f };
		sf::Vector2f velocity_;
		sf::Vector2u windowSize_{ 800, 600 };
		std::mt19937 rng_;
		std::uniform_real_distribution<float> angleDist_{ 0.f, 2.f * 3.14159265358979323846f };
	public:
		BouncingDVDLogo() : rng_(std::random_device{}()) {
			float const initAngle{ angleDist_(rng_) };
			velocity_ = sf::Vector2f(
				std::cos(initAngle) * speed_,
				std::sin(initAngle) * speed_
			);
		}

		std::string name() const override { return "Bouncing DVD Logo"; }

		void init(sf::RenderWindow& window) override {
			windowSize_ = window.getSize();
			shape_.setSize(shapeSize_);
			shape_.setOrigin(sf::Vector2f(width_ / 2.f, height_ / 2.f));
			shape_.setFillColor(sf::Color::Blue);
			shape_.setPosition(sf::Vector2(
				static_cast<float>(windowSize_.x) / 2.f,
				static_cast<float>(windowSize_.y) / 2.f
			));
		}

		void update(float dt) override {
			sf::Vector2f pos = shape_.getPosition();
			pos += velocity_ * dt;
			float leftEdge = pos.x - width_ / 2.f;
			float rightEdge = pos.x + width_ / 2.f;
			float topEdge = pos.y - height_ / 2.f;
			float bottomEdge = pos.y + height_ / 2.f;

			if (leftEdge < 0) {
				pos.x = 0.f + width_ / 2.f;
				velocity_.x = std::abs(velocity_.x);
			}
			if (topEdge < 0) {
				pos.y = 0.f + height_ / 2.f;
				velocity_.y = std::abs(velocity_.y);
			}
			if (rightEdge > windowSize_.x) {
				pos.x = windowSize_.x - width_ / 2.f;
				velocity_.x = -std::abs(velocity_.x);
			}
			if (bottomEdge > windowSize_.y) {
				pos.y = windowSize_.y - height_ / 2.f;
				velocity_.y = -std::abs(velocity_.y);
			}

			shape_.setPosition(pos);
		}

		void render(sf::RenderWindow& window) override { window.draw(shape_); }
	};

	struct Registrar {
		Registrar() {
			bool registered = sim::SimulationRegistry::instance()
				.registerSimulation("bouncing_dvd_logo", []() -> sim::Simulation* {
				return new BouncingDVDLogo();
					});
			std::cout << (registered ? "Success" : "Failed") << ": Register bouncing_dvd_logo\n";
		}
	};

	static Registrar registrar;

} // anonymous namespace