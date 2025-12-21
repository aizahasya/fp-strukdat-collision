#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"
#include <cstdlib>      //library standar nanti di pakai buat std::rand()std::srand()
#include <ctime>        

static AtomType randomAtom() {      //fungsi buat random atom
    return static_cast<AtomType>(std::rand() % 6); // 6 jenis atom
}

static sf::Vector2f randomPos() {       //fungsi random posisi
    return {
        float(std::rand() % 800),
        float(std::rand() % 600)
    };
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));      //buat atur seed random nya berdasarkan waktu

    sf::RenderWindow window(        //buat window nya
        sf::VideoMode(800, 600),
        "Particle Collision - Random Init + Keyboard Spawn"
    );

    ParticleSystem ps;      //objek nyimpen particle update collison dan nggambar 

    int initialTotal = 50;      //total particle awal

    for (int i = 0; i < initialTotal; i++) {        //loop sesuai input random jenis plus posisi
        ps.addParticle(
            randomAtom(),
            randomPos()
        );
    }

    sf::Clock clock;        //buat ngitung dt waktu antar frame

    while (window.isOpen()) {       //loop jalan selama window blm di tutup
        sf::Event e;        //buat ambil semua event
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            //ganti algoritma
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Num1)
                    ps.setCollisionMode(CollisionMode::BruteForce);

                if (e.key.code == sf::Keyboard::Num2)
                    ps.setCollisionMode(CollisionMode::Quadtree);
            }

           //nambah particle di tengah jalan
            if (e.type == sf::Event::KeyPressed) {      
                if (e.key.code == sf::Keyboard::Space) {
                    // Tambah 10 partikel random kalau tekan spasi :)
                    for (int i = 0; i < 10; i++) {
                        ps.addParticle(
                            randomAtom(),
                            randomPos()
                        );
                    }
                }

                // Tambah 1 partikel sesuai tombol nama depan atom nya
                if (e.key.code == sf::Keyboard::H)
                    ps.addParticle(AtomType::Hydrogen, randomPos());

                if (e.key.code == sf::Keyboard::E) // Helium
                    ps.addParticle(AtomType::Helium, randomPos());

                if (e.key.code == sf::Keyboard::O)
                    ps.addParticle(AtomType::Oxygen, randomPos());

                if (e.key.code == sf::Keyboard::C)
                    ps.addParticle(AtomType::Carbon, randomPos());

                if (e.key.code == sf::Keyboard::N)
                    ps.addParticle(AtomType::Nitrogen, randomPos());

                if (e.key.code == sf::Keyboard::F)
                    ps.addParticle(AtomType::Ferrum, randomPos());
            }
        }

        float dt = clock.restart().asSeconds();     //buat ngitung waktu nya dari frame terakhir aja
        ps.update(dt);      

        window.clear(sf::Color::Black);     //layar bersih
        ps.draw(window);        //gambar particle
        window.display();       //tampilin frame ke layar
    }

    return 0;
}
