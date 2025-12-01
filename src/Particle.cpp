#include "Particle.hpp"
#include <cmath>

Particle::Particle(AtomType t, sf::Vector2f startPos) {
    type = t;
    pos = startPos;

    switch(t) {
        case AtomType::Hydrogen:
            radius = 5;
            color = sf::Color::Cyan;
            vel = {80, 60};
            break;

        case AtomType::Helium:
            radius = 8;
            color = sf::Color(255, 200, 0);
            vel = {40, 30};
            break;

        case AtomType::Oxygen:
            radius = 10;
            color = sf::Color::Red;
            vel = {20, 50};
            break;

        case AtomType::Carbon:
            radius = 12;
            color = sf::Color::White;
            vel = {30, 40};
            break;

        case AtomType::Nitrogen:
            radius = 11;
            color = sf::Color::Blue;
            vel = {25, 35};
            break;

        case AtomType::Ferrum:   // Ferrum
            radius = 15;                     // lebih besar
            color = sf::Color(128,128,128);  // abu-abu
            vel = {100, 100};                // cepat, supaya mantul terasa
            break;
    }
}


void Particle::update(float dt) {
    pos += vel * dt;

    // Bounce simple
    if (pos.x < radius || pos.x > 800 - radius)
        vel.x *= -1;

    if (pos.y < radius || pos.y > 600 - radius)
        vel.y *= -1;
}

void Particle::draw(sf::RenderWindow& window) {
    sf::CircleShape c(radius);
    c.setPosition(pos - sf::Vector2f(radius, radius));
    c.setFillColor(color);
    window.draw(c);
}
