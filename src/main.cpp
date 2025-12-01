#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Simulation");

    ParticleSystem ps;

    // Jumlah awal tiap jenis partikel (manual)
    int numHydrogen = 200;
    int numHelium = 5;
    int numOxygen = 40;
    int numCarbon = 300;
    int numNitrogen = 4;
    int numFerrum = 2;

    // Tambahkan partikel sesuai jumlah
    for(int i = 0; i < numHydrogen; i++)
        ps.addParticle(AtomType::Hydrogen, sf::Vector2f(rand()%800, rand()%600));

    for(int i = 0; i < numHelium; i++)
        ps.addParticle(AtomType::Helium, sf::Vector2f(rand()%800, rand()%600));

    for(int i = 0; i < numOxygen; i++)
        ps.addParticle(AtomType::Oxygen, sf::Vector2f(rand()%800, rand()%600));

    for(int i = 0; i < numCarbon; i++)
        ps.addParticle(AtomType::Carbon, sf::Vector2f(rand()%800, rand()%600));

    for(int i = 0; i < numNitrogen; i++)
        ps.addParticle(AtomType::Nitrogen, sf::Vector2f(rand()%800, rand()%600));

    int numIron = 2;  // jumlah manual

    for(int i = 0; i < numFerrum; i++)
        ps.addParticle(AtomType::Ferrum, sf::Vector2f(rand()%800, rand()%600));

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
