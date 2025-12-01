#include "Particle.hpp"
#include <cmath>

Particle::Particle(AtomType t, sf::Vector2f startPos) {
    type = t;
    pos = startPos;

    // Karakteristik atom nyata (disederhanakan)
    if (t == AtomType::Hydrogen) {
        radius = 5;
        color = sf::Color::Cyan;
        vel = {80, 60};
    }
    else if (t == AtomType::Helium) {
        radius = 8;
        color = sf::Color(255, 200, 0);
        vel = {40, 30};
    }
    else if (t == AtomType::Oxygen) {
        radius = 10;
        color = sf::Color::Red;
        vel = {20, 50};
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
