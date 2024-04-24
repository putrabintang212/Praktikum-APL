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

void login(string& username, string& password, bool& berhasilLogin) {
    int i;
    system("cls");
    cout << "===========================================" << endl;
    cout << "Silahkan login untuk masuk ke program utama" << endl;
    cout << "===========================================" << endl;

    for (i = 1; i < 4; i++) {
        cout << "Masukan username : ";
        cin >> username;
        cout << "Masukan password : ";
        cin >> password;

        if (username == "Bintang" && password == "2309106016") {
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

bool hapusData(Laptop* laptopPtr, int* nomorlaptopPtr) {
    tampilkanData();

    string brandToFind;
    cout << "Masukkan brand laptop yang ingin dihapus: ";
    getline(cin, brandToFind);

    bool laptopDitemukan = false;
    for (int i = 0; i < *nomorlaptopPtr; ++i) {
        if (laptopPtr[i].brand == brandToFind) {
            for (int j = i; j < *nomorlaptopPtr - 1; ++j) {
                laptopPtr[j] = laptopPtr[j + 1];
            }
            (*nomorlaptopPtr)--;
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

void bubble_huruf_descending() {
    for (int i = 0; i < nomorlaptop - 1; ++i) {
        for (int j = 0; j < nomorlaptop - i - 1; ++j) {
            if (dataLaptop[j].brand < dataLaptop[j + 1].brand) {
                swap(dataLaptop[j], dataLaptop[j + 1]);
            }
        }
    }
}

void selection_angka_descending() {
    for (int i = 0; i < nomorlaptop - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < nomorlaptop; ++j) {
            if (stoi(dataLaptop[j].spec.harga) < stoi(dataLaptop[minIdx].spec.harga)) {
                minIdx = j;
            }
        }
        swap(dataLaptop[i], dataLaptop[minIdx]);
    }
}

int partitionHurufDescending(int low, int high) {
    string pivot = dataLaptop[high].brand;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (dataLaptop[j].brand >= pivot) {
            i++;
            swap(dataLaptop[i], dataLaptop[j]);
        }
    }
    swap(dataLaptop[i + 1], dataLaptop[high]);
    return (i + 1);
}

void quick_angka_ascending(int low, int high) {
    if (low < high) {
        int pi = partitionHurufDescending(low, high);
        quick_angka_ascending(low, pi - 1);
        quick_angka_ascending(pi + 1, high);
    }
}

int sequentialSearchAscending(const string& brand) {
    for (int i = 0; i < nomorlaptop; ++i) {
        if (dataLaptop[i].brand == brand) {
            return i; 
        }
    }
    return -1; 
}

int binarySearchDescending(const string& brand) {
    int low = 0, high = nomorlaptop - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (dataLaptop[mid].brand == brand) {
            return mid; 
        } else if (dataLaptop[mid].brand < brand) {
            high = mid - 1; 
        } else {
            low = mid + 1; 
        }
    }
    return -1; 
}

void menu_sort() {
    string pilihan;
    do {
        cout << "Silahkan untuk memilih menu sorting yang diinginkan" << endl;
        cout <<"1. Bubble sort (huruf-descending)" << endl;
        cout <<"2. Selection sort (harga-ascending)" << endl;
        cout <<"3. Quick sort (huruf-descending)" << endl;
        cout <<"4. Keluar" << endl;
        cout << "Pilihan: ";
        getline(cin >> ws, pilihan);
        if (pilihan == "1"){
            bubble_huruf_descending();
            cout << "Data berhasil diurutkan" << endl; 
            tampilkanData();
        }else if (pilihan == "2"){
            selection_angka_descending();
            cout << "Data berhasil diurutkan" << endl; 
            tampilkanData();
        }else if (pilihan == "3"){
            quick_angka_ascending(0, nomorlaptop - 1);
            cout << "Data berhasil diurutkan" << endl; 
            tampilkanData();
        }else if (pilihan == "4"){
            break;
        }else{
            cout << "Pilihan tidak valid" << endl;
        }
    } while (true); 
}

void menu_search() {
    string pilihan;
    do {
        cout << "Silahkan untuk memilih menu search yang diinginkan" << endl;
        cout << "1. Sequential Search (ascending)" << endl;
        cout << "2. Binary Search (descending)" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";
        getline(cin >> ws, pilihan);

        if (pilihan == "1") {
            string brandToSearch;
            cout << "Masukkan brand laptop yang ingin dicari secara ascending: ";
            getline(cin >> ws, brandToSearch);

            int index = sequentialSearchAscending(brandToSearch);
            if (index != -1) {
                cout << "===========================================" << endl;
                cout << "Data laptop dengan brand " << brandToSearch << " ditemukan pada indeks " << index << "." << endl;
                cout << "===========================================" << endl;
            } else {
                cout << "===========================================" << endl;
                cout << "Brand laptop tidak ditemukan." << endl;
                cout << "===========================================" << endl;
            }
        } else if (pilihan == "2") {
            string brandToSearch;
            cout << "Masukkan brand laptop yang ingin dicari secara descending: ";
            getline(cin >> ws, brandToSearch);

            int index = binarySearchDescending(brandToSearch);
            if (index != -1) {
                cout << "===========================================" << endl;
                cout << "Data laptop dengan brand " << brandToSearch << " ditemukan pada indeks " << index << "." << endl;
                cout << "===========================================" << endl;
            } else {
                cout << "===========================================" << endl;
                cout << "Brand laptop tidak ditemukan." << endl;
                cout << "===========================================" << endl;
            }
        } else if  (pilihan == "3"){
            break;
            
        } else{
            cout << "Pilihan tidak valid." << endl;
        }
    } while (true); 
}

int main() {
    string username, password;
    bool berhasilLogin = false;
    login(username, password, berhasilLogin);
    system("cls");
    string pilihan;
    do {
        cout << "Sistem Manajemen Data Laptop" <<endl;
        cout << "Menu Utama:" << endl;
        cout << "1. Tambah data laptop" << endl;
        cout << "2. Tampilkan data laptop" << endl;
        cout << "3. Update data laptop" << endl;
        cout << "4. Hapus data laptop" << endl;
        cout << "5. Sorting data laptop" << endl;
        cout << "6. Searching data laptop" <<endl;
        cout << "7. Keluar" << endl;
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
            hapusData(dataLaptop, &nomorlaptop);
        } else if (pilihan == "5"){
            menu_sort(); 
        } else if (pilihan == "6"){
            menu_search();    
        } else if (pilihan == "7") {
            cout << "===========================================" << endl;
            cout << "Terima kasih telah menggunakan program kami." << endl;
            cout << "===========================================" << endl;
        } else {
            tampilkanPesan("Pilihan tidak valid");
        }
    } while (pilihan != "7");

    return 0;
}


