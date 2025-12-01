#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Simulation");

    ParticleSystem ps;
    ps.addRandomParticles(50);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        ps.update(dt);

        window.clear(sf::Color::Black);
        ps.draw(window);
        window.display();
    }

    return 0;
}
