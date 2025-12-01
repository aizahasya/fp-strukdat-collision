#pragma once
#include "Particle.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class ParticleSystem {
public:
    void addParticle(AtomType type, sf::Vector2f pos);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    std::vector<Particle> particles; // simpan partikel di sini
};
