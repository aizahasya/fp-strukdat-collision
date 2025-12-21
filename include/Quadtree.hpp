#pragma once
#include <SFML/Graphics.hpp>        //di pakai untuk sf::Floatreact nyimpen left, top, width, height
#include <vector>

class Particle;

class Quadtree {
public:
    Quadtree(sf::FloatRect boundary, int capacity = 4);     //buat 1 node quadtree boundry cakupan area nya, capacity 4 karena paling standar lah
    ~Quadtree();        //buat delete child

    void insert(Particle* p);       //buat masukin satu particel nyisipin ke quadtree (pointer)
    void query(sf::FloatRect range, std::vector<Particle*>& found);     //buat cari particle di srea dalam range

private:
    sf::FloatRect boundary;     //area yg di cakup node
    int capacity;       
    bool divided = false;       //mastiin node di pecah jadi 4 child sesuai capacity

    std::vector<Particle*> points;      //menyimpan pointer ke particle

    Quadtree* northeast;
    Quadtree* northwest;
    Quadtree* southeast;
    Quadtree* southwest;

    void subdivide();       //mbagi node
};
