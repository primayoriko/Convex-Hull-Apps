# Convex Hull Program

---

Program untuk mencari convex hull dari N buah titik dan menampilkan ilustrasi/grafiknya menggunakan matplotlib.

## Instruction

---

Untuk menjalankan program,
run program ch yang ada di folder bin

Fitur grafik hanya tersediadi file ELF untuk linux

## Explanation

---

1. Library matplotlibcpp yang saya gunakan sejatinya adalah library matplotlib python sehingga diperlukan linking ke library python saat kompilasi, yang mana command untuk compile (di Kubuntu 18.04, kemungkinan sama untuk system operasi linux turunan Debian lainnya)

> g++ ch.cpp -o ch -I/usr/include/python2.7 -lpython2.7

Source code untuk versi yang harus di Linux ini saya beri nama ch.cpp

2. Matplotlibcpp karena terhubung dengan library di python maka untuk dijalankan memerlukan beberapa library python lainnya, beberapa yang saya tahu dibutuhkan : numpy, matplotlib, libpython2.7-dev . Namun tidak menutup kemungkinan membutuhkan library tambahan lain.

3. Untuk linking pada sistem operasi selain ubuntu/linux, misal windows mengalami beberapa kendala,sehingga tidak bisa dikompilasi, maka saya membuat file src khusus di windows ch_nolinux.cpp yang mana bisa dikompilasi dengan biasa (tanpa perlu linking), namun karena tidak ada library matplotlibcpp maka berarti di versi ini tidak ada penampilan gambar.

4. Untuk file ch.exe berasal dari kompilasi ch_nolinux.cpp dan file ELF ch berasal dari kompilasi ch.cpp

## Source

---

1. Matplotlib-cpp : https://github.com/lava/matplotlib-cpp
