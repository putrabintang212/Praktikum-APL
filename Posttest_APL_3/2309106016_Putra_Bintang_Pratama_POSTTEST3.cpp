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

bool tambahData() {
    system("cls");
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
            cout << "Model: " << dataLaptop[i].model << endl;
            cout << "Harga: " << dataLaptop[i].harga << endl;
            cout << "===========================================" << endl;
        }
    }
}


    void updaterekursif(const string &brandToUpdate, const laptop &newData, int index = 0) {
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
    system("cls");
    tampilkanData();
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
                 {
                    string brandToUpdate;
                    laptop newData;
                    cout << "===========================================" << endl;
                    cout << "Masukkan brand laptop yang ingin diupdate: ";
                    getline(cin, brandToUpdate);
                    cout << "Masukkan data baru" << endl;
                    cout << "Brand: ";
                    getline(cin, newData.brand);
                    cout << "Model: ";
                    getline(cin, newData.model);
                    cout << "Harga: ";
                    getline(cin, newData.harga);

                    updaterekursif(brandToUpdate, newData);
                }
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