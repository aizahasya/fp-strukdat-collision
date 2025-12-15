#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Particle;

class Quadtree {
public:
    Quadtree(sf::FloatRect boundary, int capacity = 4);
    ~Quadtree();

    void insert(Particle* p);
    void query(sf::FloatRect range, std::vector<Particle*>& found);

private:
    sf::FloatRect boundary;
    int capacity;
    bool divided = false;

    std::vector<Particle*> points;

    Quadtree* northeast;
    Quadtree* northwest;
    Quadtree* southeast;
    Quadtree* southwest;

    void subdivide();
};
