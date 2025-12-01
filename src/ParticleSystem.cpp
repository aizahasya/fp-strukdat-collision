#include "ParticleSystem.hpp"
#include <cstdlib>
#include <cmath>


void ParticleSystem::update(float dt) {
    // Update posisi semua partikel normal
    for (auto& p : particles) {
        if (!p.linked) {
            p.pos += p.vel * dt;

            // Bounce sederhana
            if (p.pos.x < p.radius || p.pos.x > 800 - p.radius)
                p.vel.x *= -1;
            if (p.pos.y < p.radius || p.pos.y > 600 - p.radius)
                p.vel.y *= -1;
        }
    }

    // Cek H + H + O untuk membentuk H2O
    for (size_t i = 0; i < particles.size(); i++) {
        Particle& p1 = particles[i];
        if (p1.linked || p1.type != AtomType::Hydrogen) continue;

        for (size_t j = i+1; j < particles.size(); j++) {
            Particle& p2 = particles[j];
            if (p2.linked || p2.type != AtomType::Hydrogen) continue;

            for (size_t k = 0; k < particles.size(); k++) {
                Particle& p3 = particles[k];
                if (p3.linked || p3.type != AtomType::Oxygen) continue;

                // Hitung jarak H-H-O
                float d1 = std::hypot(p1.pos.x - p3.pos.x, p1.pos.y - p3.pos.y);
                float d2 = std::hypot(p2.pos.x - p3.pos.x, p2.pos.y - p3.pos.y);

                if (d1 < 30 && d2 < 30) { // threshold jarak molekul
                    // Tandai sudah linked
                    p1.linked = p2.linked = p3.linked = true;

                    // Simpan partner agar bisa bergerak bareng
                    p1.partners = {&p2, &p3};
                    p2.partners = {&p1, &p3};
                    p3.partners = {&p1, &p2};

                    // Set velocity sama supaya bergerak bersama
                    sf::Vector2f avgVel = (p1.vel + p2.vel + p3.vel) / 3.0f;
                    p1.vel = p2.vel = p3.vel = avgVel;

                    goto nextMolecule; // sudah menemukan 1 molekul, lanjut cek yang lain
                }
            }
        }
    nextMolecule:;
    }

    // Update posisi partikel yang linked (bergerak bersama molekul)
    for (auto& p : particles) {
        if (p.linked) {
            p.pos += p.vel * dt; // bergerak bareng velocity rata-rata
        }
    }
}

void ParticleSystem::draw(sf::RenderWindow& window) {
    for (auto& p : particles)
        p.draw(window);
}

void ParticleSystem::addParticle(AtomType type, sf::Vector2f pos) {
    particles.push_back(Particle(type, pos));
}
