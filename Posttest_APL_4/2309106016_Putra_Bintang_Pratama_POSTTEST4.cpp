#include <iostream>
#include <cstdlib> 
#include <string>
#include <unistd.h>

using namespace std;

struct spesifikasi
{
    string model;
    string harga;
};

struct Laptop {
    string brand;
    spesifikasi spec;
};

const int maks_data = 100;
Laptop dataLaptop[maks_data];
int nomorlaptop = 0;

void tampilkanPesan(const string& pesan) {
    cout << pesan << endl;
    sleep(1);
}

void login(){
    int i;
    string usename,password;
    bool berhasilLogin = false;
    system("cls");
    cout << "===========================================" << endl;
    cout << "Silahkan login untuk masuk ke program utama" << endl;
    cout << "===========================================" << endl;

   for (i = 1; i < 4; i++) {
        cout << "Masukan username : ";
        cin >> usename;
        cout << "Masukan password : ";
        cin >> password;
    
        if(usename == "Bintang" && password == "2309106016"){
            cout << "===========================================" << endl;
            cout << "Anda berhasil login"<< endl;
            cout << "===========================================" << endl;
            berhasilLogin = true;
            break;
        } else {
            cout << "===========================================" << endl;
            cout << "Username atau password anda salah! " << i << "(x)" << endl;
            cout << "===========================================" << endl;
        }
    }
    if (!berhasilLogin) {
        cout << "===========================================" << endl;
        cout << "Anda telah salah username atau password sebanyak 3 kali!" << endl;
        cout << "Harap memulai ulang program kembali!" << endl;
        cout << "===========================================" << endl;    
        exit(0); 
    }
}

bool tambahData() {
    system("cls");
    if (nomorlaptop < maks_data) {
        cout << "Masukkan Brand: ";
        getline(cin, dataLaptop[nomorlaptop].brand);
        cout << "Masukkan Model: ";
        getline(cin, dataLaptop[nomorlaptop].spec.model);
        cout << "Masukkan Harga: ";
        getline(cin, dataLaptop[nomorlaptop].spec.harga);
        nomorlaptop++;
        cout << "===========================================" << endl;
        cout << "Data laptop berhasil ditambahkan." << endl;
        cout << "===========================================" << endl;
        return true;
    } else {
        cout << "===========================================" << endl;
        cout << "Batas maksimum data laptop telah tercapai." << endl;
        cout << "===========================================" << endl;
        return false;
    }
}


void tampilkanData() {
    system("cls");
    if (nomorlaptop == 0) {
        cout << "===========================================" << endl;
        cout << "Tidak ada data laptop yang tersimpan." << endl;
        cout << "===========================================" << endl;
    } else {
        cout << "===========================================" << endl;
        cout << "Data laptop yang tersimpan:" << endl;
        cout << "===========================================" << endl;
        for (int i = 0; i < nomorlaptop; ++i) {
            cout << "Brand: " << dataLaptop[i].brand << endl;
            cout << "Model: " << dataLaptop[i].spec.model << endl;
            cout << "Harga: " << dataLaptop[i].spec.harga << endl;
            cout << "===========================================" << endl;
        }
    }
}


    void updaterekursif(const string &brandToUpdate, const Laptop &newData, int index = 0) {
        tampilkanData();
        if (index >= nomorlaptop) {
            cout << "===========================================" << endl;
            cout << "Brand laptop tidak ditemukan." << endl;
            cout << "===========================================" << endl;
            return;
        }

        if (dataLaptop[index].brand == brandToUpdate) {
            dataLaptop[index] = newData;
            cout << "===========================================" << endl;
            cout << "Data laptop dengan brand " << brandToUpdate << " berhasil diupdate." << endl;
            cout << "===========================================" << endl;
            return;
        }

        updaterekursif(brandToUpdate, newData, index + 1); 
    }

bool hapusData() {
    tampilkanData();
    system("cls");
    string brandToFind;
    cout << "Masukkan brand laptop yang ingin dihapus: ";
    getline(cin, brandToFind);

    bool laptopDitemukan = false;
    for (int i = 0; i < nomorlaptop; ++i) {
        if (dataLaptop[i].brand == brandToFind) {
            for (int j = i; j < nomorlaptop - 1; ++j) {
                dataLaptop[j] = dataLaptop[j + 1];
            }
            nomorlaptop--;
            laptopDitemukan = true;
            cout << "===========================================" << endl;
            cout << "Data laptop berhasil dihapus." << endl;
            cout << "===========================================" << endl;
            break;
        }
    }

    if (!laptopDitemukan) {
    cout << "===========================================" << endl;
    cout << "Brand laptop tidak ditemukan." << endl;
    cout << "===========================================" << endl;
        return false;
    }

    return true;
}

int main() {
    login();
    system("cls");
    string pilihan;
    do {
        // system("cls");
        cout << "Sistem Manajemen Data Laptop" <<endl;
        cout << "Menu Utama:" << endl;
        cout << "1. Tambah data laptop" << endl;
        cout << "2. Tampilkan data laptop" << endl;
        cout << "3. Update data laptop" << endl;
        cout << "4. Hapus data laptop" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        getline(cin >> ws, pilihan);

        if (pilihan == "1") {
            tambahData();
        } else if (pilihan == "2") {
            tampilkanData();
        } else if (pilihan == "3") {
            string brandToUpdate;
            Laptop newData;
            tampilkanData();
            cout << "===========================================" << endl;
            cout << "Masukkan brand laptop yang ingin diupdate: ";
            getline(cin >> ws, brandToUpdate);
            cout << "Masukkan data baru" << endl;
            cout << "Brand: ";
            getline(cin >> ws, newData.brand);
            cout << "Model: ";
            getline(cin >> ws, newData.spec.model);
            cout << "Harga: ";
            getline(cin >> ws, newData.spec.harga);

            updaterekursif(brandToUpdate, newData);
        } else if (pilihan == "4") {
            hapusData();
        } else if (pilihan == "5") {
            cout << "===========================================" << endl;
            cout << "Terima kasih telah menggunakan program kami." << endl;
            cout << "===========================================" << endl;
        } else {
            tampilkanPesan("Pilihan tidak valid");
        }
    } while (pilihan != "5");

    return 0;
}


