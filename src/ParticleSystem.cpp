#include "ParticleSystem.hpp"
#include <cstdlib>

void ParticleSystem::addRandomParticles(int count) {
    for (int i = 0; i < count; i++) {
        int r = rand() % 3;
        AtomType t = (r == 0 ? AtomType::Hydrogen :
                      r == 1 ? AtomType::Helium : AtomType::Oxygen);

        float x = rand() % 780 + 10;
        float y = rand() % 580 + 10;

        particles.emplace_back(t, sf::Vector2f(x, y));
    }
}

void ParticleSystem::update(float dt) {
    for (auto& p : particles)
        p.update(dt);
}

void ParticleSystem::draw(sf::RenderWindow& window) {
    for (auto& p : particles)
        p.draw(window);
}
