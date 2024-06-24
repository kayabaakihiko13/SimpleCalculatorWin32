# Simple Calculator

Simple Calculator adalah aplikasi kalkulator yang dibuat menggunakan Windows API 32-bit. Aplikasi ini dirancang untuk berjalan di lingkungan Windows dan memanfaatkan Windows API untuk menyediakan antarmuka pengguna grafis.

## Fitur

- Operasi aritmatika dasar: penjumlahan, pengurangan, perkalian, dan pembagian.
- Antarmuka pengguna yang intuitif dan mudah digunakan.
- Memanfaatkan Windows API untuk kinerja yang baik dan responsif.

## Prasyarat

- Windows OS
- CMake (versi 3.0 atau lebih baru)
- Compiler yang mendukung Windows API (misalnya, Visual Studio)

## Instalasi

1. Clone repositori ini ke mesin lokal Anda:

    ```sh
    git clone https://github.com/username/simple-calculator.git
    cd simple-calculator
    ```

2. Buat direktori build dan navigasikan ke dalamnya:

    ```sh
    mkdir build
    cd build
    ```

3. Jalankan CMake untuk menghasilkan file proyek:

    ```sh
    cmake ..
    ```

4. Bangun proyek menggunakan CMake:

    ```sh
    cmake --build .
    ```

5. Jalankan aplikasi:

    ```sh
    .\bin\app_calculator.exe
    ```

## Penggunaan

Setelah aplikasi dijalankan, Anda akan melihat antarmuka kalkulator dengan tombol-tombol untuk angka dan operasi aritmatika dasar. Klik tombol angka dan operasi sesuai kebutuhan Anda, kemudian tekan tombol sama dengan (=) untuk melihat hasilnya.

## Kontribusi

Jika Anda ingin berkontribusi pada proyek ini, silakan fork repositori ini dan buat pull request dengan perubahan Anda. Semua kontribusi dipersilakan!

1. Fork repositori ini.
2. Buat branch fitur baru (`git checkout -b fitur-baru`).
3. Commit perubahan Anda (`git commit -m 'Tambah fitur baru'`).
4. Push ke branch (`git push origin fitur-baru`).
5. Buat pull request.

## Lisensi

Proyek ini dilisensikan di bawah lisensi MIT - lihat file [MIT License](LICENSE) untuk detail lebih lanjut.

## Kredit

Dibuat oleh [Kayaba Akihiko](https://github.com/kayabaakihiko13).
