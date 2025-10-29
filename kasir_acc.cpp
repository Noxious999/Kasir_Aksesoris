#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Di beberapa compiler modern, conio.h mungkin perlu diganti atau dihapus

// Fungsi untuk menghitung diskon
float diskon (float harga) {
    float awal, hasil;

    if (harga <= 50000) {
        hasil = harga; // Tidak ada diskon
    } else if (harga > 50000 && harga < 200000) {
        printf("Selamat Anda Mendapat Diskon 20 Persen!\n");
        awal = harga * 0.2;
        hasil = harga - awal;
    } else if (harga >= 200000 && harga < 500000) {
        printf("Selamat Anda Mendapat Diskon 40 Persen!\n");
        awal = harga * 0.4;
        hasil = harga - awal;
    } else if (harga >= 500000) {
        printf("Selamat Anda Mendapat Diskon 60 Persen!\n");
        awal = harga * 0.6;
        hasil = harga - awal;
    }
    return hasil;
}

int main() {
    float total = 0, potongan, hitung = 0; // Inisialisasi total dan hitung
    float bayar[12] = {0, 3000, 5000, 12000, 15000, 20000, 30000, 50000, 70000, 100000, 200000, 250000};
    int opsi, pilih, i;
    char barang[13][100] = { // Ubah ukuran array agar sesuai (13 item)
        "Checkout Pembelian",
        "Sticker",
        "Key Chain",
        "Anime Poster",
        "Case HP",
        "Special: Lil",
        "Case Laptop",
        "Figma Figure",
        "Special: Med",
        "Nendroid",
        "Action Figure",
        "Special: Big",
        "Keluar"
    };
    FILE *kasir;

    // Gunakan mode "w" untuk membuat file jika belum ada atau menimpanya
    if ((kasir = fopen("Kasir.txt", "w")) == NULL) {
        printf("Gagal membuat atau membuka file Kasir.txt!\n");
        return 1; // Keluar jika file tidak bisa dibuat/dibuka
    } else {
        // Tampilan Awal
        printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t---------------------------------\n");
        printf("\t\t\t\t\tPROGRAM KASIR\n");
        printf("\t\t\t\t---------------------------------\n");
        printf("\t\t\t\t\tNAMA : DEMSSI MULIA\n\t\t\t\t\tNIM : 210532516406\n\t\t\t\t\tPRODI: D3 TEKNIK ELEKTRONIKA\n");
        printf("\t\t\t\t---------------------------------\n");
        printf("\t\t\t\t TEKAN TOMBOL APA PUN UNTUK MELANJUTKAN");
        getch();
        system("cls"); // membersihkan layar konsol

        // Menulis header ke file struk
        fprintf(kasir, "---------------------------------\n");
        fprintf(kasir, "\t Checkout Pembelian\n");
        fprintf(kasir, "---------------------------------\n");
        fprintf(kasir, "Nama Barang\t\t Harga\n");
        fprintf(kasir, "---------------------------------\n");

        do { // Gunakan loop do-while agar menu tampil setidaknya sekali
            printf("SELAMAT DATANG DI ACCESSORY CARNIVAL!\n");
            printf("---------------------------------\n");
            for (i = 0; i < 13; i++) {
                // Tampilkan harga jika i > 0 dan i < 12
                if (i > 0 && i < 12) {
                    printf("%d - %s \t\t Rp.%.0f\n", i, barang[i], bayar[i]);
                } else {
                    printf("%d - %s\n", i, barang[i]);
                }
            }
            printf("---------------------------------\n");

            printf("\nPilihan Anda? (0-12): ");
            scanf("%d", &pilih);

            if (pilih == 0) { // Checkout
                printf("Total Belanja: Rp.%.0f\n", hitung);
                potongan = diskon(hitung); // Hitung diskon dari total belanja (hitung)
                printf("Total Akhir Setelah Diskon: Rp.%.0f\n", potongan);

                // Menulis total ke file struk
                fprintf(kasir, "---------------------------------\n");
                fprintf(kasir, "\nTotal \t\t\t Rp.%.0f", hitung);
                fprintf(kasir, "\nTotal Setelah Diskon \t Rp.%.0f", potongan);
                fprintf(kasir, "\n---------------------------------");
                break; // Keluar dari loop setelah checkout
            } else if (pilih >= 1 && pilih <= 11) { // Pilih barang
                printf("\nAmbil Barang? (1 = Ya / 2 = Tidak): ");
                scanf("%d", &opsi);
                if (opsi == 1) {
                    printf("%s Rp.%.0f ditambahkan.\n", barang[pilih], bayar[pilih]);
                    fprintf(kasir, "%s \t\t Rp.%.0f\n", barang[pilih], bayar[pilih]);
                    hitung = hitung + bayar[pilih]; // Tambahkan harga barang ke total belanja
                    total = hitung; // Simpan nilai hitung ke total (jika diperlukan nanti, meskipun pointer total tidak terpakai di source code asli)
                }
                // Jika opsi == 2 (Tidak), tidak melakukan apa-apa dan kembali ke menu
            } else if (pilih == 12) { // Keluar
                printf("Terima kasih telah berbelanja!\n");
                break; // Keluar dari loop
            } else { // Pilihan tidak valid
                printf("Pilihan tidak valid. Silakan pilih antara 0-12.\n");
                // Tidak perlu rewind(kasir) di sini
            }
            printf("\nTekan tombol apa saja untuk kembali ke menu...");
            getch();
            system("cls");

        } while (pilih != 0 && pilih != 12); // Loop terus selama belum checkout atau keluar

        fclose(kasir); // Tutup file setelah selesai
        printf("\nStruk pembelian telah disimpan di Kasir.txt\n");
        printf("Tekan tombol apa saja untuk keluar...");
        getch();
        return 0; // Program selesai dengan sukses
    }
}
