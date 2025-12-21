#include "ParticleSystem.hpp"
#include <cmath>

static float dist(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

void ParticleSystem::addParticle(AtomType type, sf::Vector2f pos) {
    particles.emplace_back(type, pos);      //mbuat particle langsung di vector
}

void ParticleSystem::update(float dt) {
    for (auto& p : particles)
        p.update(dt);

    if (mode == CollisionMode::BruteForce)
        bruteForceCollision();
    else
        quadtreeCollision();
}

void ParticleSystem::bruteForceCollision() {
    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = i + 1; j < particles.size(); j++) {
            Particle& a = particles[i];
            Particle& b = particles[j];

            float d = dist(a.pos, b.pos);
            float minDist = a.radius + b.radius;

            if (d < minDist && d > 0) {
                std::swap(a.vel, b.vel);
            }
        }
    }
}

void ParticleSystem::quadtreeCollision() {
    Quadtree qt({0,0,800,600}, 4);

    for (auto& p : particles)
        qt.insert(&p);      //masukin semua particle

    for (auto& p : particles) {
        sf::FloatRect range(
            p.pos.x - 30, p.pos.y - 30, 60, 60
        );

        std::vector<Particle*> found;
        qt.query(range, found);

        for (auto* other : found) {
            if (&p == other) continue;

            float d = dist(p.pos, other->pos);
            if (d < p.radius + other->radius && d > 0) {
                std::swap(p.vel, other->vel);
            }
        }
    }
}

void ParticleSystem::draw(sf::RenderWindow& window) {
    for (auto& p : particles)
        p.draw(window);
}

void ParticleSystem::setCollisionMode(CollisionMode m) {
    mode = m;
}
