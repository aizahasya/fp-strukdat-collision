#pragma once
#include "Particle.hpp"
#include <vector>

class ParticleSystem {
public:
    std::vector<Particle> particles;

    void addRandomParticles(int count);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};
