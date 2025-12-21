#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include "Quadtree.hpp"

// ===============================
// MODE COLLISION
// ===============================
enum class CollisionMode {
    BruteForce,
    Quadtree
};

// ===============================
// PARTICLE SYSTEM
// ===============================
class ParticleSystem {
public:
    // tambah particle ke sistem
    void addParticle(AtomType type, sf::Vector2f pos);

    // update logika tiap frame
    void update(float dt);

    // gambar semua particle
    void draw(sf::RenderWindow& window);

    // ganti mode collision
    void setCollisionMode(CollisionMode m);

private:
    // semua particle disimpan di sini
    std::vector<Particle> particles;

    // mode collision aktif
    CollisionMode mode = CollisionMode::Quadtree;

    // metode collision
    void bruteForceCollision();   // O(n²)
    void quadtreeCollision();     // ~O(n log n)
};
