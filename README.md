### Particle Simulation – Struktur Data (Final Project)
## Deskripsi Singkat
project kali ini adalah memodelkan simulasi tumbukan (collision )dengan objek particle. Pendekatan yang di lakukan adalah menggunakan dua algoritma yaitu burte force dan quadtree. Konsep algoritma burte force adalah mengecek tabrakan yang terjadi antar semua particle sementara quadtree versi lebih sederhana dengan hanya melakukan pengecekan di area tertentu.

## Tools
- C++
- SFML (2.6)
- Brute Force Collision
- Quadtree Spatial Partitioning

## Fitur
- Banyak jenis partikel (atom)
- Setiap atom punya warna, massa, radius, dan kecepatan berbeda
- Simulasi berjalan real-time
- Penambahan particle melalui tombol keyboard

## Cara menjalankan
make
./particle-sim

## Analisis percobaan 

### BURTE FORCE
### Metodologi dan Implementasi
Sistem ini menerapkan metode brute force untuk mendeteksi tabrakan, di mana setiap partikel akan dibandingkan dengan seluruh partikel lainnya satu per satu. Dengan jumlah  partikel, sistem perlu mengecek sebanyak  pasangan, yang membuat kompleksitas waktunya berada pada skala . Meski sangat mudah diimplementasikan, metode ini memiliki tantangan pada efisiensi karena beban komputasi akan melonjak tajam seiring bertambahnya jumlah objek.
Dalam simulasi ini, partikel direpresentasikan sebagai lingkaran 2D yang memiliki data posisi , kecepatan , dan radius . Pembaruan posisi dilakukan secara berkala menggunakan prinsip gerak dasar: **posisi baru = posisi lama + (kecepatan )**. Penggunaan  di sini sangat krusial agar pergerakan partikel tetap konsisten dan tidak terpengaruh oleh fluktuasi *frame rate*.

### Logika Tabrakan dan Respon
Deteksi tabrakan dilakukan dengan menghitung jarak Euclidean antar pusat partikel. Jika jarak tersebut lebih kecil dari gabungan jari-jari kedua partikel (), maka sistem mencatat telah terjadi tabrakan. Saat kondisi ini terpenuhi, simulasi akan merespons dengan menukar vektor kecepatan antar kedua partikel. Walaupun model ini merupakan penyederhanaan dari hukum fisika asli (seperti hukum kekekalan momentum), hasilnya cukup efektif untuk kebutuhan visualisasi edukatif yang mengutamakan stabilitas.

### Analisis Performa
Keunggulan utama teknik brute force adalah presisinya; tidak ada satu pun interaksi yang terlewatkan. Namun, kelemahannya muncul saat menangani partikel dalam jumlah besar atau partikel dengan kecepatan sangat tinggi yang bisa memicu efek *tunneling* (partikel menembus satu sama lain). Untuk pengembangan lebih lanjut pada skala masif, penggunaan struktur data seperti **Quadtree** sangat disarankan sebagai langkah optimasi.

### QUADTREE

### Optimasi Menggunakan Metode Quadtree

Sebagai solusi atas keterbatasan efisiensi pada metode *brute force*, simulasi ini menerapkan metode **Quadtree** untuk mengurangi jumlah pengecekan tabrakan. Berbeda dengan pendekatan brute force yang membandingkan setiap pasangan partikel, Quadtree bekerja dengan membagi ruang simulasi dua dimensi secara rekursif menjadi empat kuadran. Proses pembagian ini terus berlanjut hingga setiap node hanya menampung sejumlah kecil partikel. Dengan cara tersebut, sistem hanya perlu memeriksa tabrakan antar partikel yang berada dalam area ruang yang berdekatan, sehingga kompleksitas waktu dapat ditekan dari orde kuadratik menjadi mendekati (O(n \log n)).

Implementasi Quadtree dalam simulasi ini dijalankan melalui dua tahap utama, yaitu *broad phase* dan *narrow phase*. Pada tahap *broad phase*, sistem membentuk area pencarian di sekitar setiap partikel menggunakan struktur `sf::FloatRect`. Area ini berfungsi sebagai filter awal untuk menjaring kandidat partikel yang berpotensi bertabrakan, sementara partikel yang berada di luar area tersebut diabaikan tanpa dilakukan perhitungan lanjutan. Tahap ini bertujuan untuk memangkas jumlah perhitungan jarak yang tidak perlu. Selanjutnya, pada tahap *narrow phase*, kandidat partikel yang telah lolos penyaringan akan diperiksa lebih lanjut menggunakan perhitungan jarak Euclidean guna memastikan apakah benar terjadi tabrakan sebelum sistem memberikan respon fisik.

### Error simulasi
Meskipun memberikan peningkatan performa yang signifikan, penggunaan Quadtree menimbulkan beberapa kendala yang memengaruhi akurasi simulasi secara visual. Salah satu masalah yang sering muncul adalah gejala partikel yang terlihat saling menempel sebelum akhirnya bereaksi. Kondisi ini umumnya terjadi ketika ukuran area pencarian pada tahap *broad phase* terlalu kecil, sehingga partikel yang seharusnya menjadi kandidat tabrakan tidak terdeteksi oleh Quadtree pada frame tertentu. Akibatnya, proses pemeriksaan jarak pada tahap *narrow phase* menjadi terlambat dan respon tabrakan tidak langsung terjadi.

Kendala lain yang ditemukan adalah fenomena *tunneling*, khususnya pada partikel dengan kecepatan tinggi. Dalam simulasi berbasis *frame* diskrit, posisi partikel diperbarui berdasarkan selang waktu tertentu. Jika dalam satu langkah waktu partikel bergerak sejauh jarak yang melebihi diameter partikel lain, maka kondisi tumpang tindih tidak pernah terdeteksi. Fenomena ini dapat terjadi baik pada metode brute force maupun Quadtree, namun pada Quadtree risikonya lebih besar karena adanya tahap penyaringan awal yang dapat melewatkan partikel yang bergerak terlalu cepat.

Selain itu, efek partikel yang tampak lengket atau *overlap* juga dipengaruhi oleh tidak adanya koreksi posisi setelah tabrakan. Pada simulasi ini, respon tabrakan hanya dilakukan dengan menukar vektor kecepatan antar partikel tanpa memisahkan posisi partikel yang saling bertumpuk. Akibatnya, meskipun arah gerak partikel telah berubah, posisi yang masih saling tumpang tindih dapat menyebabkan partikel terlihat menempel selama beberapa frame berikutnya.

## Kesimpulan
Secara keseluruhan, metode Quadtree sangat efektif untuk meningkatkan performa simulasi pada jumlah partikel yang besar, namun bersifat aproksimatif dan sensitif terhadap parameter tertentu seperti ukuran area pencarian, kecepatan partikel, dan langkah waktu simulasi. Untuk memperoleh hasil yang lebih stabil dan presisi, metode ini dapat dikembangkan lebih lanjut dengan memperlebar jangkauan deteksi pada area padat atau menerapkan teknik *sub-stepping* waktu. Dengan pendekatan tersebut, Quadtree tetap menjadi solusi optimasi yang efisien dengan kompromi tertentu pada tingkat akurasi fisika.

