#include "Quadtree.hpp"
#include "Particle.hpp"

Quadtree::Quadtree(sf::FloatRect b, int cap)
    : boundary(b),
      capacity(cap),
      divided(false),
      northeast(nullptr),
      northwest(nullptr),
      southeast(nullptr),
      southwest(nullptr) {}

Quadtree::~Quadtree() {
    delete northeast;
    delete northwest;
    delete southeast;
    delete southwest;
}

void Quadtree::subdivide() {
    float x = boundary.left;
    float y = boundary.top;
    float w = boundary.width / 2.f;
    float h = boundary.height / 2.f;

    northeast = new Quadtree({x + w, y, w, h}, capacity);
    northwest = new Quadtree({x, y, w, h}, capacity);
    southeast = new Quadtree({x + w, y + h, w, h}, capacity);
    southwest = new Quadtree({x, y + h, w, h}, capacity);

    divided = true;
}

void Quadtree::insert(Particle* p) {
    if (!boundary.contains(p->pos)) return;

    if (points.size() < capacity) {
        points.push_back(p);
        return;
    }

    if (!divided)
        subdivide();

    northeast->insert(p);
    northwest->insert(p);
    southeast->insert(p);
    southwest->insert(p);
}

void Quadtree::query(sf::FloatRect range, std::vector<Particle*>& found) {
    if (!boundary.intersects(range)) return;

    for (auto* p : points) {
        if (range.contains(p->pos))
            found.push_back(p);
    }

    if (!divided) return;

    northeast->query(range, found);
    northwest->query(range, found);
    southeast->query(range, found);
    southwest->query(range, found);
}
