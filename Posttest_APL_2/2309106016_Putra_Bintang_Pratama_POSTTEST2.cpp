#include <iostream>
#include <cstdlib> 
#include <string>

using namespace std;

struct laptop
{
    string brand;
    string model;
    string harga;
};

const int maks_data = 100;
laptop dataLaptop[maks_data];
int nomorlaptop = 0;

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

void tambahData() {
    system("cls");
    cout << "===========================================" << endl;
    if (nomorlaptop < maks_data) {
        cout << "Masukkan Brand: ";
        getline(cin, dataLaptop[nomorlaptop].brand);
        cout << "Masukkan Model: ";
        getline(cin, dataLaptop[nomorlaptop].model);
        cout << "Masukkan Harga: ";
        getline(cin, dataLaptop[nomorlaptop].harga);
        nomorlaptop++;
        cout << "===========================================" << endl;
        cout << "Data laptop berhasil ditambahkan." << endl;
        cout << "===========================================" << endl;
    } else {
        cout << "===========================================" << endl;
        cout << "Batas maksimum data laptop telah tercapai." << endl;
        cout << "===========================================" << endl;
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
            cout << "Model: " << dataLaptop[i].model << endl;
            cout << "Harga: " << dataLaptop[i].harga << endl;
            cout << "===========================================" << endl;
        }
    }
}


void updateData() {
    system("cls");
    tampilkanData();
    string brand;
    cout << "===========================================" << endl;
    cout << "Masukkan brand laptop yang ingin diupdate: " << endl;
    cout << "===========================================" << endl;
    cin >> brand;
    for (int i = 0; i < nomorlaptop; ++i) {
        if (dataLaptop[i].brand == brand) {
            cout << "===========================================" << endl;
            cout << "Masukkan Model baru: ";
            cin.ignore(); 
            getline(cin, dataLaptop[i].model);
            cout << "Masukkan Harga baru: ";
            getline(cin, dataLaptop[i].harga);
            cout << "===========================================" << endl;
            cout << "Data laptop berhasil diupdate." << endl;
            cout << "===========================================" << endl;
            return;
        }
    }
    cout << "===========================================" << endl;
    cout << "Brand laptop tidak ditemukan." << endl;
    cout << "===========================================" << endl;
}


void hapusData() {
    system("cls");
    tampilkanData();
    string brand;
    cout << "Masukkan brand laptop yang ingin dihapus: ";
    cin >> brand;
    for (int i = 0; i < nomorlaptop; ++i) {
        if (dataLaptop[i].brand == brand) {
            for (int j = i; j < nomorlaptop - 1; ++j) {
                dataLaptop[j] = dataLaptop[j + 1];
            }
            nomorlaptop--;
            cout << "===========================================" << endl;
            cout << "Data laptop berhasil dihapus." << endl;
            cout << "===========================================" << endl;
            return;
        }
    }
    cout << "===========================================" << endl;
    cout << "Brand laptop tidak ditemukan." << endl;
    cout << "===========================================" << endl;
}


int main() {
    system("cls");
    login();
    int pilihan;
    do {
        cout << "\nMenu Utama:" << endl;
        cout << "1. Tambah data laptop" << endl;
        cout << "2. Tampilkan data laptop" << endl;
        cout << "3. Update data laptop" << endl;
        cout << "4. Hapus data laptop" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tambahData();
                break;
            case 2:
                tampilkanData();
                break;
            case 3:
                updateData();
                break;
            case 4:
                hapusData();
                break;
            case 5:
                cout << "===========================================" << endl;
                cout << "Terima kasih telah menggunakan program kami." << endl;
                cout << "===========================================" << endl;
                break;
            default:
                cout << "===========================================" << endl;
                cout << "Pilihan tidak valid." << endl;
                cout << "===========================================" << endl;
                break;
        }
    } while (pilihan != 5);

    return 0;
}