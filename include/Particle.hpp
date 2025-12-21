#pragma once        // buat ngehindari multiple definition penyebab error
#include <SFML/Graphics.hpp>        //buat komponen2 grafis nya kayak vector posisi dan kecepatanwarna partikel dll
#include <vector>       //library STL

enum class AtomType {       //definisi jenis partikel nya apa aja pakai enum class biar lebih aman ga gampang ke campur
    Hydrogen,
    Helium,
    Oxygen,
    Carbon,
    Nitrogen,
    Ferrum
};

class Particle {        //definisi class particle
public:
    AtomType type;
    sf::Vector2f pos;       //buat posisi particle koordinat xy tipe float gerakan halebih halus
    sf::Vector2f vel;       //ini buat kecepatan nya
    float radius;       //radius particle
    sf::Color color;

    Particle(AtomType t, sf::Vector2f startPos);        //construktor nya t itu jenis atom nya dan posisi awal starpos

    void update(float dt);      //update logika particle tipa frame
    void draw(sf::RenderWindow& window);        //menggambar particle ke window
};
