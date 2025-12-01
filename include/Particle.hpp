#pragma once
#include <SFML/Graphics.hpp>

enum class AtomType {
    Hydrogen,
    Helium,
    Oxygen,
    Carbon,    
    Nitrogen,  
    Ferrum,  
};

class Particle {
public:
    sf::Vector2f pos;
    sf::Vector2f vel;
    float radius;
    sf::Color color;
    AtomType type;

    bool linked = false;
    std::vector<Particle*> partners;

    Particle(AtomType t, sf::Vector2f startPos);

    void update(float dt);
    void draw(sf::RenderWindow& window);
};
