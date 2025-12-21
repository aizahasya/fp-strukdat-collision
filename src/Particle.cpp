#include "Particle.hpp"
#include <SFML/Graphics.hpp>

const float GLOBAL_SPEED = 2.0f;

Particle::Particle(AtomType t, sf::Vector2f startPos) {
    type = t;
    pos  = startPos;

    switch (t) {        //buat definisi perilaku tiap atom
        case AtomType::Hydrogen:
            radius = 5;
            color  = sf::Color::Cyan;
            vel    = {80.f, 60.f};
            break;

        case AtomType::Helium:
            radius = 8;
            color  = sf::Color(255,200,0);
            vel    = {40.f, 30.f};
            break;

        case AtomType::Oxygen:
            radius = 10;
            color  = sf::Color::Red;
            vel    = {20.f, 50.f};
            break;

        case AtomType::Carbon:
            radius = 12;
            color  = sf::Color::White;
            vel    = {30.f, 40.f};
            break;

        case AtomType::Nitrogen:
            radius = 11;
            color  = sf::Color::Blue;
            vel    = {25.f, 35.f};
            break;

        case AtomType::Ferrum:
            radius = 15;
            color  = sf::Color(128,128,128);
            vel    = {100.f, 100.f};
            break;
    }

    
    vel *= GLOBAL_SPEED;        //kali kecepatan global
}

void Particle::update(float dt) {
    pos += vel * dt;

    if (pos.x < radius || pos.x > 800 - radius)     //kalau nabrak frame balik
        vel.x *= -1;

    if (pos.y < radius || pos.y > 600 - radius)
        vel.y *= -1;
}

void Particle::draw(sf::RenderWindow& window) {     //buatgambar nya
    sf::CircleShape c(radius);
    c.setOrigin(radius, radius);
    c.setPosition(pos);
    c.setFillColor(color);
    window.draw(c);
}
