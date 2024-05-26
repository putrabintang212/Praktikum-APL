#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <iomanip>
#include <cstdio>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <limits> 
#include <algorithm> 
#include <vector> 
#include <map>
#include <cctype>
#include <unordered_set>

using namespace std;
int main_exit;
string logged_in_acc_no;

void fordelay(int);
void close(void);
int main();
void menu_admin();
void employee();
void customer();
void menu_c();
void menu_baru();
void create_account();
void login();

class Bank
{
public:
    string acc_no;
	string name;
    string dob;
    string age;
    string date;
    string address;
    string phone;
    string doc;
    string depo;
    string acc_type;
    string password;
    int test;
public:
    void read_data();
    void acc_write();
	void modify_account(const string& acc_no);
	void search_admin();
    void search_c(const string& acc_no);
	void deposit_withdraw(const string& acc_no);
	void display_all();
	void transfer(const string& acc_no);
    void close_account();
    void permintaan_admin();
    void menu_permintaan_nasabah();

private:
    string generateAccountNumber(unordered_set<string>& existing_accounts);
    void loadExistingAccounts(const string& filename, unordered_set<string>& accounts);
};
bool is_number(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
bool is_valid_account_number(const string& acc_no) {
    for (char c : acc_no) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
bool is_valid_date(const string& date) {
    if (date.size() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;

    string mm = date.substr(0, 2);
    string dd = date.substr(3, 2);
    string yyyy = date.substr(6, 4);

    if (!is_number(mm) || !is_number(dd) || !is_number(yyyy)) return false;

    int month = stoi(mm);
    int day = stoi(dd);
    int year = stoi(yyyy);

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false; 
    return true;
}
void waitForEnter() {
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string Bank::generateAccountNumber(unordered_set<string>& existing_accounts) {
    srand(time(0)); 
    string acc_no;
    do {
        acc_no = to_string(rand() % 10000); 
        acc_no = string(6 - acc_no.length(), '0') + acc_no;
    } while (existing_accounts.find(acc_no) != existing_accounts.end());
    existing_accounts.insert(acc_no);
    return acc_no;
}

void Bank::loadExistingAccounts(const string& filename, unordered_set<string>& accounts) {
    ifstream file("Account_info.csv");
    string line, acc_no;
    while (getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            acc_no = line.substr(0, pos);
            accounts.insert(acc_no);
        }
    }
    file.close();
}
void Bank::read_data() {
    string acc_no, password; // Variabel untuk menyimpan nomor akun dan password baru
    int x; // Variabel untuk input umur (tidak digunakan langsung dalam fungsi ini)
    unordered_set<string> existing_accounts; // Set untuk menyimpan nomor akun yang sudah ada

    // Memuat nomor akun yang sudah ada dari file "Account_info.csv" ke dalam set existing_accounts
    loadExistingAccounts("Account_info.csv", existing_accounts);

    // Menghasilkan nomor akun baru yang belum ada di existing_accounts
    acc_no = generateAccountNumber(existing_accounts); 
    cout << "Nomor akun yang dihasilkan: " << acc_no << endl; // Menampilkan nomor akun yang dihasilkan

    ofstream os("Bank_Record.csv", ios::app); // Membuka file "Bank_Record.csv" untuk ditambahkan data baru
    cout << acc_no << endl;

    // Mengambil data dari pengguna
    cout << "\nMasukkan nama: ";
    cin.ignore(); // Mengabaikan karakter newline yang tersisa di buffer input
    getline(cin, name); // Mengambil input nama dari pengguna

    cout << "\nMasukkan tanggal lahir (DD/MM/YYYY): ";
    cin >> dob; // Mengambil input tanggal lahir dari pengguna

    cout << "\nMasukkan umur: ";
    cin >> age; // Mengambil input umur dari pengguna

    cout << "\nMasukkan alamat: ";
    cin.ignore(); // Mengabaikan karakter newline yang tersisa di buffer input
    getline(cin, address); // Mengambil input alamat dari pengguna

    cout << "\nMasukkan nomor telepon: ";
    cin >> phone; // Mengambil input nomor telepon dari pengguna

    cout << "\nMasukkan jumlah setoran awal: ";
    cin >> depo; // Mengambil input jumlah setoran awal dari pengguna

    cout << "\nMasukkan tipe akun (Tabungan/Giro): ";
    cin >> acc_type; // Mengambil input tipe akun dari pengguna

    // Mendapatkan waktu saat ini dan mengonversinya menjadi string
    time_t now = time(0);
    date = ctime(&now);
    date = date.substr(0, date.size() - 1); // Menghilangkan karakter newline di akhir string tanggal

    // Membuka file "Bank_Record.csv" dan "Account_info.csv" untuk ditambahkan data baru
    ofstream MyFile("Bank_Record.csv", ios::app);
    ofstream MyFile2("Account_info.csv", ios::app);

    // Memeriksa apakah kedua file berhasil dibuka
    if (MyFile.is_open() && MyFile2.is_open()) {
        // Menulis data akun baru ke file "Bank_Record.csv"
        MyFile << acc_no << "," << name << "," << dob << "," << age << "," << address << "," << phone << ","
               << depo << "," << acc_type << "," << date << "\n";
        MyFile.close(); // Menutup file setelah selesai menulis

        cout << "Buat password untuk akun baru: ";
        cin.ignore(); // Mengabaikan karakter newline yang tersisa di buffer input
        getline(cin, password); // Mengambil input password dari pengguna
        
        // Menulis nomor akun dan password ke file "Account_info.csv"
        MyFile2 << acc_no << "," << password << "\n";
        MyFile2.close(); // Menutup file setelah selesai menulis

        cout << "Data telah berhasil disimpan ke dalam database bank\n";
    } else {
        cout << "Data gagal disimpan ke dalam database bank.\n";
    }

    waitForEnter(); // Menunggu pengguna menekan tombol Enter sebelum melanjutkan
    customer(); // Kembali ke menu atau fungsi customer
}

void Bank::acc_write()
{
	read_data();
}

void Bank::modify_account(const string& acc_no) {
    // Mengecek apakah akun yang ingin dimodifikasi adalah akun yang sedang login
    if (acc_no != logged_in_acc_no) {
        cout << "Akun ini telah ditutup/tersedia" << endl;
        waitForEnter(); // Menunggu pengguna menekan Enter
        menu_c(); // Kembali ke menu utama
        return;
    }

    int test = 0; // Variabel untuk menandai apakah akun ditemukan
    ifstream is("Bank_Record.csv"); // Membuka file "Bank_Record.csv" untuk dibaca
    if (!is.is_open()) {
        cout << "Gagal membuka file" << endl;
        return; // Keluar jika file gagal dibuka
    }
    ofstream temp("temp.csv"); // Membuka file sementara untuk menulis data yang dimodifikasi
    if (!temp.is_open()) {
        cout << "Gagal membuka file sementara" << endl;
        is.close();
        return; // Keluar jika file sementara gagal dibuka
    }

    string line;
    // Membaca file baris per baris
    while (getline(is, line)) {
        stringstream ss(line); // Menggunakan stringstream untuk memisahkan data berdasarkan koma
        string acc_no, name, dob, age, address, phone, depo, acc_type, date, doc, bunga;
        // Membaca setiap field dalam satu baris
        getline(ss, acc_no, ',');
        getline(ss, name, ',');
        getline(ss, dob, ',');
        getline(ss, age, ',');
        getline(ss, address, ',');
        getline(ss, phone, ',');
        getline(ss, depo, ',');
        getline(ss, acc_type, ',');
        getline(ss, date, ',');
        getline(ss, doc, ',');
        getline(ss, bunga, '\n');

        // Mengecek apakah nomor akun sesuai dengan akun yang sedang login
        if (acc_no == logged_in_acc_no) {
            test = 1; // Menandai bahwa akun ditemukan
            // Menampilkan informasi akun
            cout << "\nAccount NO.:" << acc_no << endl;
            cout << "\nNama:" << name << endl;
            cout << "\nTanggal Lahir:" << dob << endl;
            cout << "\nUmur:" << age << endl;
            cout << "\nAlamat: " << address << endl;
            cout << "\nNomor Telepon:" << phone << endl;
            cout << "\nTipe Akun:" << acc_type << endl;
            cout << "\nTanggal Akun Dibuat:" << date << endl;
            cout << "\nJumlah yang telah disetor:" << depo << endl;

            int choice;
            // Menampilkan menu pilihan untuk memperbarui informasi akun
            do {
                cout << "\n\n\n\t\t1. Perbarui Nama\n";
                cout << "\t\t2. Perbarui Tanggal Lahir\n";
                cout << "\t\t3. Perbarui Umur\n";
                cout << "\t\t4. Perbarui Alamat\n";
                cout << "\t\t5. Perbarui Nomor Telepon\n";
                cout << "\t\t6. Selesai\n";
                cout << "Pilih opsi: ";
                cin >> choice;
                if (cin.fail()) {
                    cout << "Input tidak valid! Masukkan angka sesuai pilihan yang ada.\n";
                    cin.clear(); // Membersihkan flag error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter tidak valid
                    continue; // Kembali ke awal loop
                }
                switch (choice) {
                    case 1:
                        // Memperbarui nama
                        cout << "Masukkan Nama Baru: ";
                        cin.ignore();
                        getline(cin, name);
                        break;
                    case 2:
                        // Memperbarui tanggal lahir dengan validasi
                        do {
                            cout << "Masukkan Tanggal Lahir Baru (dd/mm/yyyy): ";
                            cin >> dob;
                            if (!is_valid_date(dob)) {
                                cout << "Input tidak valid! Masukkan tanggal lahir dengan format dd/mm/yyyy yang benar.\n";
                            }
                        } while (!is_valid_date(dob));
                        cout << "Tanggal lahir berhasil diperbarui.\n";
                        break;
                    case 3:
                        // Memperbarui umur
                        cout << "Masukkan Umur Baru: ";
                        cin >> age;
                        break;
                    case 4:
                        // Memperbarui alamat
                        cout << "Masukkan Alamat Baru: ";
                        cin.ignore();
                        getline(cin, address);
                        break;
                    case 5:
                        // Memperbarui nomor telepon dengan validasi
                        do {
                            cout << "Masukkan Nomor Telepon Baru: ";
                            cin >> phone;
                            if (!is_number(phone)) {
                                cout << "Input tidak valid! Masukkan hanya angka.\n";
                            }
                        } while (!is_number(phone));
                        cout << "Nomor telepon berhasil diperbarui.\n";
                        break;
                    case 6:
                        // Selesai memperbarui informasi
                        break;
                    default:
                        cout << "Input tidak valid" << endl;
                        break;
                }
            } while (choice != 6);
            // Menulis data yang sudah diperbarui ke file sementara
            temp << acc_no << ',' << name << ',' << dob << ',' << age << ',' << address << ',' << phone << ',' << depo << ',' << acc_type << ',' << date << ',' << doc << ',' << '\n';
        } else {
            // Menulis data yang tidak diubah ke file sementara
            temp << acc_no << ',' << name << ',' << dob << ',' << age << ',' << address << ',' << phone << ',' << depo << ',' << acc_type << ',' << date << ',' << doc << ',' << '\n';
        }
    }

    is.close(); // Menutup file input
    temp.close(); // Menutup file sementara
    if (test == 1) {
        // Jika akun ditemukan, menggantikan file asli dengan file sementara
        ifstream temp_in("temp.csv");
        ofstream bank_out("Bank_Record.csv");
        if (temp_in.is_open() && bank_out.is_open()) {
            string line;
            while (getline(temp_in, line)) {
                bank_out << line << endl;
            }
            temp_in.close();
            bank_out.close();
        } else {
            cout << "Gagal membuka file sementara atau file utama untuk menulis" << endl;
        }
        cout << "\nData berhasil diperbarui.\n";
        remove("temp.csv"); // Menghapus file sementara
    } else {
        // Jika akun tidak ditemukan, menghapus file sementara
        cout << "\nAkun Tidak Ditemukan\n";
        remove("temp.csv");
    }
    waitForEnter(); // Menunggu pengguna menekan Enter
}


void Bank::close_account() {
    string acc_no, line;
    bool account_found = false; // Variabel untuk menandai apakah akun ditemukan

    do {
        cout << "\nMasukkan nomor akun yang ingin ditutup: ";
        cin >> acc_no;
        // Validasi input untuk memastikan hanya angka yang dimasukkan
        if (cin.fail()) {
            cout << "Input tidak valid! Masukkan hanya angka.\n";
            cin.clear(); // Membersihkan flag error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter tidak valid
            continue; // Kembali ke awal loop
        }

        account_found = false; // Reset penanda akun ditemukan
        ifstream is("Account_info.csv"); // Membuka file "Account_info.csv" untuk membaca
        if (!is.is_open()) {
            cout << "Gagal membuka file Account_info.csv!\n";
            waitForEnter(); // Menunggu pengguna menekan Enter
            menu_admin(); // Kembali ke menu admin
            return; // Keluar dari fungsi jika file gagal dibuka
        }
        ofstream temp_is("temp_Account_info.csv", ios::app); // Membuka file sementara untuk menulis
        if (!temp_is.is_open()) {
            cout << "Gagal membuat sementara file temp_Account_info.csv!\n";
            is.close(); // Menutup file input
            waitForEnter(); // Menunggu pengguna menekan Enter
            menu_admin(); // Kembali ke menu admin
            return; // Keluar dari fungsi jika file sementara gagal dibuka
        }

        // Membaca file baris per baris
        while (getline(is, line)) {
            size_t pos = line.find(',');
            // Mengecek apakah nomor akun sesuai dengan akun yang ingin ditutup
            if (pos != string::npos && line.substr(0, pos) == acc_no) {
                account_found = true; // Menandai bahwa akun ditemukan
            } else {
                temp_is << line << "\n"; // Menulis baris ke file sementara jika bukan akun yang ingin ditutup
            }
        }
        is.close(); // Menutup file input
        temp_is.close(); // Menutup file sementara

        if (account_found) {
            // Mengganti file asli dengan file sementara
            remove("Account_info.csv");
            rename("temp_Account_info.csv", "Account_info.csv");

            ifstream br("Bank_Record.csv"); // Membuka file "Bank_Record.csv" untuk membaca
            if (!br.is_open()) {
                cout << "Gagal membuka file Bank_Record.csv!\n";
                waitForEnter(); // Menunggu pengguna menekan Enter
                menu_admin(); // Kembali ke menu admin
                return; // Keluar dari fungsi jika file gagal dibuka
            }

            ofstream temp_br("temp_Bank_Record.csv", ios::app); // Membuka file sementara untuk menulis
            if (!temp_br.is_open()) {
                cout << "Gagal membuat sementara file temp_Bank_Record.csv!\n";
                br.close(); // Menutup file input
                waitForEnter(); // Menunggu pengguna menekan Enter
                menu_admin(); // Kembali ke menu admin
                return; // Keluar dari fungsi jika file sementara gagal dibuka
            }

            // Membaca file baris per baris
            while (getline(br, line)) {
                size_t pos = line.find(',');
                // Mengecek apakah nomor akun sesuai dengan akun yang ingin ditutup
                if (pos != string::npos && line.substr(0, pos) == acc_no) {
                    continue; // Lewati baris ini jika sesuai
                } else {
                    temp_br << line << "\n"; // Menulis baris ke file sementara jika bukan akun yang ingin ditutup
                }
            }
            br.close(); // Menutup file input
            temp_br.close(); // Menutup file sementara
            remove("Bank_Record.csv"); // Menghapus file asli
            rename("temp_Bank_Record.csv", "Bank_Record.csv"); // Mengganti file asli dengan file sementara

            system("cls"); // Membersihkan layar
            cout << "Akun berhasil ditutup dan data telah dihapus dari database bank.\n";
        } else {
            cout << "Nomor akun tidak ditemukan. Silakan coba lagi.\n";
            remove("temp_Account_info.csv"); // Menghapus file sementara jika akun tidak ditemukan
        }

    } while (!account_found); // Mengulang jika akun tidak ditemukan

    waitForEnter(); // Menunggu pengguna menekan Enter
    menu_admin(); // Kembali ke menu admin
}

void Bank::search_admin() {
    int test = 0, main_exit; // Variabel untuk menandai apakah akun ditemukan dan opsi keluar
    int choice; // Variabel untuk menyimpan pilihan pengguna
    string acc_no, name_s; // Variabel untuk nomor akun dan nama pemegang akun

    do {
        ifstream is("Bank_Record.csv"); // Membuka file "Bank_Record.csv" untuk membaca

        if (!is.is_open()) {
            // Jika file tidak dapat dibuka, tampilkan pesan kesalahan
            cout << "File Bank_Record.csv tidak dapat dibuka! Pastikan file tersedia.\n";
            return;
        }

        // Menampilkan pilihan pencarian kepada pengguna
        cout << "Apakah Anda ingin cek berdasarkan\n"
                "1. Account\n"
                "2. Nama\n"
                "Masukkan Pilihan Anda : ";

        // Memastikan input pengguna valid (1 atau 2)
        while (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Input tidak valid! Masukkan pilihan 1 atau 2.\n";
        }

        if (choice == 1) {
            cout << "Masukkan nomor account:";
            cin >> acc_no;

            string acc, name, dob, age, address, phone, depo, acc_type, date, doc, bunga;
            while (getline(is, acc, ',')) {
                // Membaca data akun dari file
                getline(is, name, ',');
                getline(is, dob, ',');
                getline(is, age, ',');
                getline(is, address, ',');
                getline(is, phone, ',');
                getline(is, depo, ',');
                getline(is, acc_type, ',');
                getline(is, date, ',');
                getline(is, doc, ',');
                getline(is, bunga, '\n');
                
                int amount = atoi(depo.c_str());
                // Jika nomor akun ditemukan, tampilkan data
                if (acc == acc_no) {
                    test = 1;
                    system("cls");
                    cout << "\nAccount NO.:" << acc << endl;
                    cout << "\nNama:" << name << endl;
                    cout << "\nTanggal Lahir:" << dob << endl;
                    cout << "\nUmur:" << age << endl;
                    cout << "\nAlamat: " << address << endl;
                    cout << "\nNomor Telepon:" << phone << endl;
                    cout << "\nTipe Akun:" << acc_type << endl;
                    cout << "\nTanggal Akun Dibuat:" << date << endl;
                    cout << "\nJumlah yang telah disetor:" << depo << endl;
                }
            }
        } else if (choice == 2) {
            cout << "Masukkan nama Pemegang akun:";
            cin >> name_s;

            string acc, name, dob, age, address, phone, depo, acc_type, date, doc, bunga;
            while (getline(is, acc, ',')) {
                // Membaca data akun dari file
                getline(is, name, ',');
                getline(is, dob, ',');
                getline(is, age, ',');
                getline(is, address, ',');
                getline(is, phone, ',');
                getline(is, depo, ',');
                getline(is, acc_type, ',');
                getline(is, date, ',');
                getline(is, doc, ',');
                getline(is, bunga, '\n');
                
                int amount = atoi(depo.c_str());
                // Jika nama pemegang akun ditemukan, tampilkan data
                if (name == name_s) {
                    test = 1;
                    system("cls");
                    cout << "\nAccount NO.:" << acc << endl;
                    cout << "\nNama:" << name << endl;
                    cout << "\nTanggal Lahir:" << dob << endl;
                    cout << "\nUmur:" << age << endl;
                    cout << "\nAlamat: " << address << endl;
                    cout << "\nNomor Telepon:" << phone << endl;
                    cout << "\nTipe Akun:" << acc_type << endl;
                    cout << "\nTanggal Akun Dibuat:" << date << endl;
                    cout << "\nJumlah yang telah disetor:" << depo << endl;
                }
            }
        }

        // Jika akun tidak ditemukan, tampilkan pesan
        if (test == 0) {
            cout << "\n\n\t\tAkun Tidak Ditemukan!";
        }

        is.close(); // Menutup file

        do {
            // Meminta pengguna untuk memasukkan 1 untuk kembali ke menu utama
            cout << "\nKetik 1 untuk kembali ke menu utama: ";
            cin >> main_exit;
            if (cin.fail() || main_exit != 1) {
                cout << "Input tidak valid! Silakan masukkan angka 1." << endl;
                cin.clear();                
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                continue;                    
            } else {
                system("cls"); // Membersihkan layar
                menu_admin(); // Kembali ke menu admin
            }
        } while (true);

    } while (true);
}

void Bank::search_c(const string& acc_no) {
    ifstream is("Bank_Record.csv"); // Membuka file "Bank_Record.csv" untuk membaca
    bool found = false; // Penanda apakah akun ditemukan
    if (!is.is_open()) { // Memeriksa apakah file berhasil dibuka
        cout << "Error membuka file!" << endl; // Menampilkan pesan kesalahan jika file tidak dapat dibuka
        return; // Keluar dari fungsi jika file gagal dibuka
    }

    string line;
    // Membaca file baris per baris
    while (getline(is, line)) {
        stringstream ss(line); // Membuat stringstream dari baris yang dibaca
        string current_acc_no;
        Bank *currentAccount = new Bank(); // Membuat objek Bank baru untuk menyimpan data akun
        getline(ss, currentAccount->acc_no, ','); // Membaca nomor akun dari stream
        // Jika nomor akun cocok, tampilkan data akun
        if (currentAccount->acc_no == acc_no) {
            getline(ss, currentAccount->name, ','); // Membaca nama dari stream
            getline(ss, currentAccount->dob, ','); // Membaca tanggal lahir dari stream
            getline(ss, currentAccount->age, ','); // Membaca umur dari stream
            getline(ss, currentAccount->address, ','); // Membaca alamat dari stream
            getline(ss, currentAccount->phone, ','); // Membaca nomor telepon dari stream
            getline(ss, currentAccount->depo, ','); // Membaca jumlah deposit dari stream
            getline(ss, currentAccount->acc_type, ','); // Membaca tipe akun dari stream
            getline(ss, currentAccount->date, ','); // Membaca tanggal pembuatan akun dari stream
            getline(ss, currentAccount->doc, ','); // Membaca dokumen dari stream
            system("cls"); // Membersihkan layar
            // Menampilkan data akun yang ditemukan
            cout << "\nAccount NO.:" << acc_no << endl;
            cout << "\nNama:" << currentAccount->name << endl;
            cout << "\nTanggal Lahir:" << currentAccount->dob << endl;
            cout << "\nUmur:" << currentAccount->age << endl;
            cout << "\nAlamat: " << currentAccount->address << endl;
            cout << "\nNomor Telepon:" << currentAccount->phone << endl;
            cout << "\nTipe Akun:" << currentAccount->acc_type << endl;
            cout << "\nTanggal Akun Dibuat:" << currentAccount->date << endl;
            cout << "\nJumlah yang telah disetor:" << currentAccount->depo << endl;
            waitForEnter(); // Menunggu pengguna menekan Enter
            found = true; // Menandai bahwa akun ditemukan

            delete currentAccount; // Menghapus objek akun saat ini untuk menghindari kebocoran memori
            break; // Keluar dari loop setelah menemukan akun
        }

        delete currentAccount; // Menghapus objek akun saat ini untuk menghindari kebocoran memori
    }

    is.close(); // Menutup file

    if (!found) { // Jika akun tidak ditemukan, tampilkan pesan
        cout << "Akun tidak tersedia." << endl;
        waitForEnter(); // Menunggu pengguna menekan Enter
    }

    waitForEnter(); // Menunggu pengguna menekan Enter
    menu_c(); // Kembali ke menu pelanggan
}

void Bank::deposit_withdraw(const string& acc_no) {
    if (acc_no != logged_in_acc_no) { // Memeriksa apakah nomor akun yang diberikan cocok dengan akun yang sedang login
        cout << "Anda hanya dapat melakukan transaksi pada akun Anda sendiri." << endl;
        waitForEnter(); // Menunggu pengguna menekan Enter
        menu_c(); // Kembali ke menu pelanggan
        return; // Keluar dari fungsi jika akun tidak cocok
    }

    int choice, amt, amount;
    string name, dob, age, address, phone, depo, acc_type, date, doc, bunga;

    ifstream file("bank_record.csv"); // Membuka file "bank_record.csv" untuk membaca
    ofstream ofile("temp.csv"); // Membuka atau membuat file sementara "temp.csv" untuk menulis

    if (!file.is_open() || !ofile.is_open()) { // Memeriksa apakah kedua file berhasil dibuka
        cout << "Error membuka file!" << endl;
        return; // Keluar dari fungsi jika salah satu file gagal dibuka
    }

    bool found_account = false; // Penanda apakah akun ditemukan

    // Membaca file baris per baris
    while (getline(file, this->acc_no, ',')) {
        getline(file, name, ',');
        getline(file, dob, ',');
        getline(file, age, ',');
        getline(file, address, ',');
        getline(file, phone, ',');
        getline(file, depo, ',');
        getline(file, acc_type, ',');
        getline(file, date, ',');
        getline(file, doc, ',');
        getline(file, bunga, '\n');

        if (this->acc_no == logged_in_acc_no) { // Memeriksa apakah nomor akun cocok dengan akun yang sedang login
            found_account = true; // Menandai bahwa akun ditemukan
            amount = stoi(depo); // Mengonversi jumlah deposit dari string ke integer

            // Menampilkan informasi akun
            cout << "\nAccount No.: " << logged_in_acc_no << endl;
            cout << "Nama: " << name << endl;
            cout << "Saldo: " << depo << endl;

            // Loop untuk memilih antara deposit atau withdraw
            while (true) {
                cout << "\n\nApakah Anda ingin: \n1. Deposit\n2. Withdraw (tarik uang)?\n\n"
                     << "Masukkan Pilihan Anda: ";
                cin >> choice;

                if (cin.fail()) { // Memeriksa apakah input valid
                    cout << "Input tidak valid!" << endl;
                    cin.clear(); // Membersihkan status fail
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang tidak valid
                    system("cls"); // Membersihkan layar
                    continue; // Kembali ke awal loop
                }

                if (choice == 1) { // Jika pilihan adalah deposit
                    cout << "Masukkan jumlah yang ingin Anda setor: ";
                    cin >> amt;
                    if (cin.fail() || amt <= 0) { // Memeriksa apakah jumlah valid
                        cout << "Jumlah tidak valid!" << endl;
                        cin.clear(); // Membersihkan status fail
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang tidak valid
                        system("cls"); // Membersihkan layar
                        continue; // Kembali ke awal loop
                    } else {
                        amount += amt; // Menambahkan jumlah ke saldo
                        depo = to_string(amount); // Mengonversi saldo baru ke string
                        cout << "\n\tSaldo baru: " << depo << endl;
                    }
                    break; // Keluar dari loop setelah deposit
                } else if (choice == 2) { // Jika pilihan adalah withdraw
                    cout << "Masukkan jumlah yang ingin Anda tarik: ";
                    cin >> amt;
                    if (cin.fail() || amt <= 0) { // Memeriksa apakah jumlah valid
                        cout << "Jumlah tidak valid!" << endl;
                        cin.clear(); // Membersihkan status fail
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang tidak valid
                        system("cls"); // Membersihkan layar
                        continue; // Kembali ke awal loop
                    }
                    if (amt > amount) { // Memeriksa apakah saldo mencukupi untuk withdraw
                        cout << "Saldo Tidak Cukup\n" << endl;
                    } else {
                        amount -= amt; // Mengurangi jumlah dari saldo
                        depo = to_string(amount); // Mengonversi saldo baru ke string
                        cout << "\n\tSaldo baru: " << depo << endl;
                    }
                    break; // Keluar dari loop setelah withdraw
                } else {
                    cout << "Pilihan tidak valid! Silakan coba lagi.\n";
                    system("cls"); // Membersihkan layar
                }
            }

            // Menulis data akun yang diperbarui ke file sementara
            ofile << logged_in_acc_no << ',' << name << ',' << dob << ',' << age << ','
                  << address << ',' << phone << ',' << depo << ',' << acc_type << ','
                  << date << ',' << doc << ',' << bunga << '\n';

        } else {
            // Menulis data akun lainnya ke file sementara tanpa perubahan
            ofile << this->acc_no << ',' << name << ',' << dob << ',' << age << ','
                  << address << ',' << phone << ',' << depo << ',' << acc_type << ','
                  << date << ',' << doc << ',' << bunga << '\n';
        }
    }

    file.close(); // Menutup file asli
    ofile.close(); // Menutup file sementara
    remove("bank_record.csv"); // Menghapus file asli
    rename("temp.csv", "bank_record.csv"); // Mengganti nama file sementara menjadi file asli

    if (!found_account) { // Jika akun tidak ditemukan, tampilkan pesan
        cout << "\n\nAkun Tidak Ditemukan!!" << endl;
    }

    // Loop untuk menunggu input dari pengguna untuk kembali ke menu utama
    while (true) {
        cout << "\nKetik 1 untuk kembali ke menu utama: ";
        cin >> choice;
        if (cin.fail() || choice != 1) { // Memeriksa apakah input valid
            cout << "Input tidak valid! Silakan masukkan angka 1." << endl;
            cin.clear(); // Membersihkan status fail
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang tidak valid
            system("cls"); // Membersihkan layar
            continue; // Kembali ke awal loop
        }
        system("cls"); // Membersihkan layar
        menu_c(); // Kembali ke menu pelanggan
        break; // Keluar dari loop setelah input valid
    }
}

void Bank::display_all() {
    ifstream is("Bank_Record.csv"); // Membuka file "Bank_Record.csv" untuk membaca
    if (!is) { // Memeriksa apakah file berhasil dibuka
        cerr << "Error opening file!" << endl;
        return; // Keluar dari fungsi jika file gagal dibuka
    }

    // Struktur data untuk menyimpan semua data akun nasabah
    vector<vector<string>> all_accounts;

    string line;
    while (getline(is, line)) { // Membaca file baris per baris
        istringstream ss(line);

        vector<string> account_data;
        string token;
        while (getline(ss, token, ',')) { // Membaca setiap token (kolom) yang dipisahkan oleh koma
            account_data.push_back(token); // Menambahkan token ke vector account_data
        }

        all_accounts.push_back(account_data); // Menambahkan account_data ke all_accounts
    }

    // Pilihan sorting berdasarkan huruf nama nasabah
    int sort_choice = 0;
    while (true) { // Loop untuk pilihan sorting
        cout << "\n\n====================================\n";
        cout << "             Pilihan Sorting         \n";
        cout << "====================================\n";
        cout << "1. Ascending (A-Z)\n";
        cout << "2. Descending (Z-A)\n";
        cout << "====================================\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> sort_choice;

        // Cek apakah input valid
        if (cin.fail()) { // Memeriksa apakah input valid
            cin.clear(); // Membersihkan kesalahan
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan sisa input yang salah
            cout << "Input tidak valid. Silakan masukkan angka 1 atau 2.\n";
            continue; // Kembali ke awal loop
        }

        if (sort_choice == 1 || sort_choice == 2) { // Memeriksa apakah pilihan valid
            break; // Keluar dari loop jika pilihan valid
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }

    // Fungsi untuk membandingkan nama nasabah
    auto compare_names = [](const vector<string>& a, const vector<string>& b) {
        return a[1] < b[1]; // Mengurutkan berdasarkan nama nasabah (indeks ke-1 dari vector account_data)
    };

    // Melakukan pengurutan berdasarkan nama nasabah
    if (sort_choice == 1) {
        // Ascending (A-Z)
        sort(all_accounts.begin(), all_accounts.end(), compare_names);
    } else if (sort_choice == 2) {
        // Descending (Z-A)
        sort(all_accounts.begin(), all_accounts.end(), compare_names);
        reverse(all_accounts.begin(), all_accounts.end()); // Membalik urutan untuk descending
    }

    // Menampilkan header tabel
    cout << "\n\n\t\tDAFTAR AKUN NASABAH\n\n";
    cout << "=================================================================================================="
         << "============================================\n";
    cout << left << setw(15) << "Account No." << setw(20) << "Nama" << setw(10) << "Tipe" << setw(15)
         << "Saldo" << setw(30) << "Alamat" << setw(20) << "Nomor Telepon" << "Tanggal Dibuat\n";
    cout << "=================================================================================================="
         << "============================================\n";

    // Menampilkan data akun nasabah setelah pengurutan
    for (const auto& account_data : all_accounts) {
        long long amount = 0;
        try {
            if (!account_data[6].empty()) { // Memeriksa apakah data saldo tidak kosong
                amount = stoll(account_data[6]); // Mengonversi saldo dari string ke long long
            }
        } catch (const invalid_argument& e) { // Menangani kesalahan konversi jika data tidak valid
            cerr << "Invalid argument: " << account_data[6] << " cannot be converted to integer." << endl;
            continue; // Melewati akun ini dan melanjutkan ke akun berikutnya
        } catch (const out_of_range& e) { // Menangani kesalahan jika nilai diluar jangkauan long long
            cerr << "Out of range error: " << account_data[6] << " is out of range for a long long integer." << endl;
            continue; // Melewati akun ini dan melanjutkan ke akun berikutnya
        }

        // Menampilkan data akun
        cout << left << setw(15) << account_data[0] << setw(20) << account_data[1] << setw(10) << account_data[7]
             << setw(15) << amount << setw(30) << account_data[4] << setw(20) << account_data[5] << account_data[8] << endl;
    }

    is.close(); // Menutup file
    waitForEnter(); // Menunggu pengguna menekan Enter
}

void Bank::transfer(const string& acc_no) {
    int amt, test = 0; // Variabel untuk menyimpan jumlah transfer dan penanda akun ditemukan
    string acc_no_sender, acc_no_receiver, y; // Variabel untuk nomor akun pengirim dan penerima serta saldo sementara
    ifstream file("Bank_Record.csv"); // Membuka file "Bank_Record.csv" untuk membaca
    ofstream ofile("temp.csv"); // Membuka file sementara "temp.csv" untuk menulis

    if (!file.is_open() || !ofile.is_open()) { // Memeriksa apakah file berhasil dibuka
        cout << "Error membuka file!" << endl;
        return; // Keluar dari fungsi jika file gagal dibuka
    }

    while (true) { // Loop untuk mendapatkan nomor akun pengirim
        cout << "Masukkan nomor akun Anda: ";
        cin >> acc_no_sender;
        if (!is_valid_account_number(acc_no_sender)) { // Memeriksa validitas nomor akun
            cout << "Input tidak valid! Masukkan nomor akun yang benar.\n";
            cin.clear(); // Membersihkan kesalahan input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
        } else {
            break; // Keluar dari loop jika input valid
        }
    }

    while (getline(file, this->acc_no, ',')) { // Membaca file baris per baris
        if (this->acc_no.empty()) break; // Memeriksa jika nomor akun kosong
        getline(file, name, ','); // Membaca nama
        getline(file, dob, ','); // Membaca tanggal lahir
        getline(file, age, ','); // Membaca umur
        getline(file, address, ','); // Membaca alamat
        getline(file, phone, ','); // Membaca nomor telepon
        getline(file, depo, ','); // Membaca saldo
        getline(file, acc_type, ','); // Membaca tipe akun
        getline(file, date, ','); // Membaca tanggal pembuatan akun
        getline(file, doc, ','); // Membaca dokumen lainnya

        if (this->acc_no == acc_no_sender) { // Memeriksa jika nomor akun cocok dengan pengirim
            test = 1; // Menandai bahwa akun pengirim ditemukan
            cout << "Account No. Pengirim: " << this->acc_no << endl;
            cout << "Nama: " << name << endl;
            cout << "Saldo: " << depo << endl;
            cout << "\nMasukkan jumlah yang ingin ditransfer: ";
            cin >> amt;

            if (amt > stoi(depo)) { // Memeriksa jika saldo cukup untuk transfer
                cout << "Saldo tidak cukup untuk transfer.\n";
                // Menulis data akun ke file sementara
                ofile << this->acc_no << ',' << name << ',' << dob << ',' << age << ','
                      << address << ',' << phone << ',' << depo << ',' << acc_type << ','
                      << date << ',' << doc << ',' << '\n';
                continue; // Melewatkan iterasi loop ini
            }
            int amount = stoi(depo) - amt; // Mengurangi saldo pengirim dengan jumlah transfer
            y = to_string(amount); // Mengonversi saldo baru ke string
            cout << "\n\tSisa saldo Anda: " << y << endl;
            // Menulis data akun dengan saldo baru ke file sementara
            ofile << this->acc_no << ',' << name << ',' << dob << ',' << age << ','
                  << address << ',' << phone << ',' << y << ',' << acc_type << ','
                  << date << ',' << doc << ',' << '\n';

        } else {
            // Menulis data akun lain ke file sementara
            ofile << this->acc_no << ',' << name << ',' << dob << ',' << age << ','
                  << address << ',' << phone << ',' << depo << ',' << acc_type << ','
                  << date << ',' << doc << ',' << '\n';
        }
    }

    file.close(); // Menutup file setelah selesai membaca
    ofile.close(); // Menutup file sementara setelah selesai menulis
    remove("Bank_Record.csv"); // Menghapus file asli
    rename("temp.csv", "Bank_Record.csv"); // Mengganti nama file sementara menjadi file asli

    if (test == 0) { // Memeriksa jika akun pengirim tidak ditemukan
        cout << "\n\nAkun pengirim tidak ditemukan!" << endl;
        return; // Keluar dari fungsi
    }

    while (true) { // Loop untuk mendapatkan nomor akun penerima
        cout << "Masukkan nomor akun penerima: ";
        cin >> acc_no_receiver;
        if (!is_valid_account_number(acc_no_receiver)) { // Memeriksa validitas nomor akun
            cout << "Input tidak valid! Masukkan nomor akun yang benar.\n";
            cin.clear(); // Membersihkan kesalahan input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
        } else {
            break; // Keluar dari loop jika input valid
        }
    }

    test = 0; // Mengatur ulang penanda akun ditemukan
    file.open("Bank_Record.csv"); // Membuka kembali file asli untuk membaca
    ofile.open("temp.csv"); // Membuka kembali file sementara untuk menulis

    if (!file.is_open() || !ofile.is_open()) { // Memeriksa apakah file berhasil dibuka
        cout << "Error membuka file!" << endl;
        return; // Keluar dari fungsi jika file gagal dibuka
    }

    while (getline(file, this->acc_no, ',')) { // Membaca file baris per baris
        if (this->acc_no.empty()) break; // Memeriksa jika nomor akun kosong
        getline(file, name, ','); // Membaca nama
        getline(file, dob, ','); // Membaca tanggal lahir
        getline(file, age, ','); // Membaca umur
        getline(file, address, ','); // Membaca alamat
        getline(file, phone, ','); // Membaca nomor telepon
        getline(file, depo, ','); // Membaca saldo
        getline(file, acc_type, ','); // Membaca tipe akun
        getline(file, date, ','); // Membaca tanggal pembuatan akun
        getline(file, doc, ','); // Membaca dokumen lainnya

        if (this->acc_no == acc_no_receiver) { // Memeriksa jika nomor akun cocok dengan penerima
            test = 1; // Menandai bahwa akun penerima ditemukan
            cout << "Account No. Penerima: " << this->acc_no << endl;
            int amount = stoi(depo) + amt; // Menambah saldo penerima dengan jumlah transfer
            y = to_string(amount); // Mengonversi saldo baru ke string
            cout << "\n\tSaldo baru Penerima: " << y << endl;
            // Menulis data akun dengan saldo baru ke file sementara
            ofile << this->acc_no << ',' << name << ',' << dob << ',' << age << ','
                  << address << ',' << phone << ',' << y << ',' << acc_type << ','
                  << date << ',' << doc << ',' << '\n';
            cout << "Transfer berhasil dikirim!"<< endl;
            waitForEnter(); // Menunggu pengguna menekan Enter
            menu_c(); // Kembali ke menu pelanggan

        } else {
            // Menulis data akun lain ke file sementara
            ofile << this->acc_no << ',' << name << ',' << dob << ',' << age << ','
                  << address << ',' << phone << ',' << depo << ',' << acc_type << ','
                  << date << ',' << doc << ',' << '\n';
        }
    }

    file.close(); // Menutup file setelah selesai membaca
    ofile.close(); // Menutup file sementara setelah selesai menulis
    remove("Bank_Record.csv"); // Menghapus file asli
    rename("temp.csv", "Bank_Record.csv"); // Mengganti nama file sementara menjadi file asli

    if (test == 0) { // Memeriksa jika akun penerima tidak ditemukan
        cout << "\n\nAkun penerima tidak ditemukan!" << endl;
    }
}

void fordelay(int j)
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}

void close(void)
{
    printf("\n\n\n\nProgram Ini Telah Berhenti... Thank You");
}

void employee() {
    char pass[10]; // Variabel tidak digunakan, bisa dihapus
    char c; // Variabel untuk menyimpan karakter yang dimasukkan pengguna
    string s, name; // `s` untuk menyimpan password, `name` untuk menyimpan ID staff
    int i = 0; // Variabel penghitung untuk loop animasi
    cout << "\n\n\t\tKeamanan:";
    cout << "\n\n\t\tMasukkan Staff Id:";
    cin >> name; // Membaca ID staff
    cout << "\n\n\t\tMasukkan Password:";

    // Loop untuk membaca password karakter demi karakter
    while (true) {
        c = getch(); // Membaca karakter tanpa menunggu Enter (fungsi ini biasanya ada di <conio.h>)
        if (c != '\r' && c != '\b') { // Jika karakter bukan Enter atau Backspace
            printf("*"); // Menampilkan bintang sebagai pengganti karakter yang dimasukkan
            s += c; // Menambahkan karakter ke string password
        }
        if (c == '\r') { // Jika karakter adalah Enter
            break; // Keluar dari loop
        }
        if (c == '\b' && !s.empty()) { // Jika karakter adalah Backspace dan string password tidak kosong
            printf("\b \b"); // Menghapus bintang terakhir dari layar
            s = s.substr(0, s.size() - 1); // Menghapus karakter terakhir dari string password
        }
    }

    // Memeriksa jika password dan ID staff cocok dengan kredensial yang diizinkan
    if (s == "1234" && (name == "admin" || name == "bintang")) {
        printf("\n\nAkses Diberikan!\nLOADING");
        for (i = 0; i <= 6; i++) {
            fordelay(100000000); // Fungsi untuk menunda waktu (fungsi ini biasanya didefinisikan sendiri)
            printf("."); // Menampilkan titik sebagai animasi loading
        }
        system("cls"); // Membersihkan layar (fungsi ini tergantung pada sistem operasi)
        menu_admin(); // Memanggil fungsi untuk menampilkan menu admin
    } else {
        printf("\n\nID atau Password Salah!!");
    login_try: // Label untuk ulangi login jika gagal
        while (true) {
            cout << "\n1. Coba Lagi\n"
                 << "0. Keluar\n"
                 << "Masukkan Pilihan Anda : ";

            if (!(cin >> main_exit)) { // Membaca pilihan pengguna dan memeriksa jika input valid
                cout << "Input tidak valid! Masukkan angka (0 atau 1).\n";
                cin.clear(); // Membersihkan kesalahan input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
            } else {
                if (main_exit == 1) { // Jika pilihan adalah 1
                    system("cls"); // Membersihkan layar
                    employee(); // Memanggil ulang fungsi employee untuk mencoba lagi
                    break;
                } else if (main_exit == 0) { // Jika pilihan adalah 0
                    system("cls"); // Membersihkan layar
                    main(); // Kembali ke fungsi utama
                    break;
                } else {
                    cout << "\nTidak Valid!\n";
                    fordelay(10000000); // Menunda waktu sejenak
                    system("cls"); // Membersihkan layar
                }
            }
        }
    }
}


void cek_saran() {
    cout << "===============SARAN===============" << endl; // Menampilkan judul
    ifstream is("saran.txt"); // Membuka file "saran.txt" untuk dibaca
    if (!is.is_open()) { // Memeriksa apakah file terbuka dengan sukses
        cerr << "Error opening file!" << endl; // Menampilkan pesan kesalahan jika gagal membuka file
        return; // Keluar dari fungsi jika gagal membuka file
    }
    string line;
    while (getline(is, line)) { // Membaca file baris per baris dan menampilkannya
        cout << line << endl; // Menampilkan setiap baris dari file
    }
    is.close(); // Menutup file setelah selesai membacanya
}

void permintaan_admin() {
    ifstream file("nasabah.csv"); // Membuka file "nasabah.csv" untuk dibaca

    if (!file.is_open()) { // Memeriksa apakah file terbuka dengan sukses
        cout << "Gagal membuka file nasabah.csv" << endl; // Menampilkan pesan kesalahan jika gagal membuka file
        return; // Keluar dari fungsi jika gagal membuka file
    }
    string line;
    bool hasData = false;
    while (getline(file, line)) { // Membaca file baris per baris
        hasData = true; // Mengubah status hasData menjadi true jika ada data dalam file
        break; // Keluar dari loop setelah membaca baris pertama
    }
    if (!hasData) { // Jika tidak ada data dalam file
        cout << "Tidak ada data!" << endl; // Menampilkan pesan bahwa tidak ada data
        file.close(); // Menutup file
        waitForEnter(); // Menunggu pengguna menekan Enter
        menu_admin(); // Memanggil menu_admin untuk kembali ke menu admin
    }

    // Menampilkan header tabel
    cout << left << setw(10) << "ID" << left << setw(20) << "Nama" << left << setw(15) << "Password"
         << left << setw(20) << "Permintaan" << left << setw(10) << "Opsi" << left << setw(20) << "Data Baru" << endl;
    cout << string(95, '=') << endl; // Menampilkan garis pemisah

    while (getline(file, line)) { // Membaca file baris per baris
        size_t pos = 0;
        string token;
        int column = 0;

        while ((pos = line.find(',')) != string::npos) { // Membagi baris menjadi token berdasarkan koma (,)
            token = line.substr(0, pos); // Mendapatkan token dari posisi awal hingga koma
            line.erase(0, pos + 1); // Menghapus token yang sudah dibaca beserta koma
            switch (column) { // Switch untuk menentukan kolom data yang akan ditampilkan
                case 0: cout << left << setw(10) << token; break; // ID
                case 1: cout << left << setw(20) << token; break; // Nama
                case 2: cout << left << setw(15) << token; break; // Password
                case 3: cout << left << setw(20) << token; break; // Permintaan
                case 4: cout << left << setw(10) << token; break; // Opsi
            }
            column++; // Pindah ke kolom data berikutnya
        }
        cout << left << setw(20) << line << endl; // Menampilkan data baru setelah koma terakhir
    }

    file.close(); // Menutup file setelah selesai membacanya
    waitForEnter(); // Menunggu pengguna menekan Enter
    menu_admin(); // Memanggil menu_admin untuk kembali ke menu admin
}

void menu_admin() {
    int choice; // Variabel untuk menyimpan pilihan user
    Bank B; // Objek Bank untuk mengakses fungsi-fungsi terkait Bank
    while (true) { // Loop utama untuk menampilkan menu admin dan menghandle pilihan user
        system("cls"); // Menghapus layar konsol sebelum menampilkan menu
        system("color 2"); // Mengubah warna teks pada konsol menjadi hijau muda
        cout << "\n\n\t\t\tSISTEM MANAJEMEN BANK"; // Menampilkan judul program
        cout << "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SELAMAT DATANG "
                  << "DI MENU ADMIN \xB2\xB2\xB2\xB2\xB2\xB2\xB2"; // Menampilkan judul menu admin
        cout << "\n\n\t\t\tMenu Staff"; // Menampilkan subjudul menu
        cout << "\n\t\t1. Cek Detail Akun\n"; // Pilihan untuk melihat detail akun
        cout << "\t\t2. Tampilkan Semua Pemegang Akun\n"; // Pilihan untuk menampilkan semua pemegang akun
        cout << "\t\t3. Perbarui Akun Nasabah\n"; // Pilihan untuk memperbarui akun nasabah
        cout << "\t\t4. Cek Permintaan Nasabah\n"; // Pilihan untuk mengecek permintaan nasabah
        cout << "\t\t5. Tutup Akun\n"; // Pilihan untuk menutup akun
        cout << "\t\t6. Cek Saran\n"; // Pilihan untuk mengecek saran
        cout << "\t\t0. Exit\n\n\n\n\n\t\t Masukkan Pilihan Anda: "; // Instruksi untuk memasukkan pilihan
        
        // Memastikan input user merupakan angka dan berada dalam rentang yang valid
        while (!(cin >> choice) || choice < 0 || choice > 6) {
            cin.clear(); // Menghapus status error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
            cout << "Input tidak valid! Masukkan pilihan angka antara 0 dan 5.\n"; // Pesan kesalahan
            cout << "Masukkan Pilihan Anda: "; // Meminta user untuk memasukkan pilihan lagi
        }
        cin.ignore(); // Menghapus karakter newline dari buffer input

        system("cls"); // Menghapus layar konsol setelah user memilih pilihan
        switch (choice) { // Memilih aksi berdasarkan pilihan user
            case 1:
                B.search_admin(); // Memanggil fungsi untuk mencari detail akun sebagai admin
                waitForEnter(); // Menunggu user menekan Enter sebelum melanjutkan
                break;
            case 2:
                B.display_all(); // Memanggil fungsi untuk menampilkan semua pemegang akun
                waitForEnter(); // Menunggu user menekan Enter sebelum melanjutkan
                break;
            case 3:
                B.modify_account(logged_in_acc_no); // Memanggil fungsi untuk memperbarui akun nasabah
                waitForEnter(); // Menunggu user menekan Enter sebelum melanjutkan
                break;
            case 4:
                permintaan_admin(); // Memanggil fungsi untuk mengecek permintaan nasabah
                waitForEnter(); // Menunggu user menekan Enter sebelum melanjutkan
                break;
            case 5:
                B.close_account(); // Memanggil fungsi untuk menutup akun
                break;
            case 6:
                cek_saran(); // Memanggil fungsi untuk mengecek saran
                waitForEnter(); // Menunggu user menekan Enter sebelum melanjutkan
                break;
            case 0:
                main(); // Kembali ke menu utama
                break;
            default:
                cout << "Input Tidak Valid!\n"; // Pesan kesalahan jika pilihan tidak valid
                waitForEnter(); // Menunggu user menekan Enter sebelum melanjutkan
                break;
        }
    }
}

void customer() {
    int x; // Variabel untuk menyimpan pilihan menu dari user
    while (true) { // Loop utama untuk menampilkan dan memproses menu customer
        system("cls"); // Menghapus layar konsol sebelum menampilkan menu
        cout << "\n\n\t\t\tMENU"; // Menampilkan judul menu
        cout << "\n\t\t1. Nasabah Baru"; // Pilihan menu untuk nasabah baru
        cout << "\n\t\t2. Login"; // Pilihan menu untuk login
        cout << "\n\t\t3. Keluar"; // Pilihan menu untuk keluar dari program
        cout << "\n\t\tMasukkan Pilihan Anda (1/2/3) : "; // Instruksi untuk memasukkan pilihan menu

        cin >> x; // Mengambil pilihan menu dari input

        if (cin.fail()) { // Memeriksa apakah input merupakan angka
            cout << "Input Tidak Valid! Masukkan angka 1 atau 2.\n"; // Pesan kesalahan jika input tidak valid
            cin.clear(); // Menghapus status error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
            continue; // Melanjutkan loop untuk meminta input yang benar
        }

        if (x == 1) { // Jika user memilih 1, panggil fungsi menu_baru() dan keluar dari loop
            menu_baru();
            break;
        } else if (x == 2) { // Jika user memilih 2, panggil fungsi login() dan keluar dari loop
            login();
            break;
        } else if (x == 3) { // Jika user memilih 3, kembali ke menu utama dengan memanggil fungsi main()
            main();
            break;
        } else { // Jika input tidak sesuai pilihan yang tersedia, tampilkan pesan kesalahan
            cout << "Input Tidak Valid! Masukkan angka 1 atau 2.\n";
        }
    }
}


void login(){
    string name, s, acc_no; // Variabel untuk menyimpan ID, password yang diinput, dan nomor akun dari file
    char c; // Variabel untuk menerima input karakter

    cout << "\n\n\t\tKeamanan: "; // Menampilkan judul keamanan
    cout << "\n\n\t\tMasukkan ID: "; // Meminta input ID dari user
    cin >> name; // Mengambil input ID

    cout << "\n\n\t\tMasukkan Password: "; // Meminta input password dari user

    while (true) { // Loop untuk menerima karakter password secara tersembunyi
        c = getch(); // Menerima karakter tanpa menampilkan ke layar
        if (c == '\r') break; // Jika Enter (newline) ditekan, keluar dari loop
        if (c == '\b' && !s.empty()) { // Jika tombol backspace ditekan dan string password tidak kosong
            cout << "\b \b"; // Menghapus satu karakter dari layar
            s.pop_back(); // Menghapus satu karakter dari string password
        } else if (c != '\r' && c != '\b') { // Jika karakter bukan Enter atau backspace
            cout << '*'; // Tampilkan karakter '*' sebagai pengganti karakter password
            s.push_back(c); // Tambahkan karakter ke string password
        }
    }

    ifstream is("Account_info.csv"); // Membuka file Account_info.csv untuk verifikasi login
    string password; // Variabel untuk menyimpan password dari file
    bool access_granted = false; // Flag untuk menandakan akses diberikan atau tidak

    while (getline(is, acc_no, ',')) { // Loop untuk membaca setiap baris file dan membandingkan ID dan password
        getline(is, password, '\n'); // Mengambil password dari file
        if (acc_no == name && password == s) { // Jika ID dan password cocok dengan yang diinput
            logged_in_acc_no = acc_no; // Set nomor akun yang login
            access_granted = true; // Set flag akses diberikan menjadi true
            break; // Keluar dari loop
        }
    }

    if (access_granted) { // Jika akses diberikan
        cout << "\n\nAkses Diberikan!\nLOADING"; // Tampilkan pesan akses diberikan dan loading
        for (int i = 0; i <= 6; i++) { // Loop untuk simulasi loading
            fordelay(10000000); // Fungsi penundaan
            cout << "."; // Tampilkan titik-titik loading
        }
        system("cls"); // Bersihkan layar
        menu_c(); // Panggil menu untuk customer setelah login berhasil
    } else { // Jika akses tidak diberikan
        cout << "\n\nPassword atau Customer ID salah!!"; // Tampilkan pesan kesalahan login
        int main_exit; // Variabel untuk pilihan menu
        while (true) { // Loop untuk menampilkan menu pilihan setelah gagal login
            cout << "\n1. Coba lagi\n2. Menu Utama\n0. Exit\n"
                    << "Masukan Pilihan Anda : "; // Menampilkan pilihan menu
            cin >> main_exit; // Menerima input pilihan menu
            if (cin.fail()) { // Jika input tidak valid
                cout << "\nInput Tidak Valid!\nHarus sesuai dengan pilihan!"; // Tampilkan pesan kesalahan
                fordelay(100000000); // Penundaan
                system("cls"); // Bersihkan layar
                cin.clear(); // Hapus status error dari cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Hapus karakter yang tidak valid dari input
                continue; // Lanjutkan loop untuk meminta input yang benar
            }
            if (main_exit == 1) { // Jika memilih coba lagi
                system("cls"); // Bersihkan layar
                customer(); // Panggil menu customer kembali
                break; // Keluar dari loop
            } else if (main_exit == 2) { // Jika memilih menu utama
                system("cls"); // Bersihkan layar
                main(); // Panggil menu utama
                break; // Keluar dari loop
            } else if (main_exit == 0) { // Jika memilih exit
                system("cls"); // Bersihkan layar
                close(); // Keluar dari program
                break; // Keluar dari loop
            } else { // Jika input tidak valid
                cout << "\nTidak Valid!\nHarus sesuai dengan pilihan!"; // Tampilkan pesan kesalahan
                fordelay(1000000000); // Penundaan
                system("cls"); // Bersihkan layar
            }
        }
    }
}
    
void create_account() {
    string new_id, new_password, s; // Variabel untuk menyimpan ID baru, password baru, dan karakter yang diinput
    char c; // Variabel untuk menerima input karakter

    cout << "\n\n\t\tBuat Akun Baru"; // Menampilkan judul pembuatan akun baru
    cout << "\n\n\t\tMasukkan ID Baru: "; // Meminta input ID baru dari user
    cin >> new_id; // Mengambil input ID baru

    cout << "\n\n\t\tMasukkan Password Baru: "; // Meminta input password baru dari user

    while (true) { // Loop untuk menerima karakter password baru secara tersembunyi
        c = getch(); // Menerima karakter tanpa menampilkan ke layar
        if (c == '\r') break; // Jika Enter (newline) ditekan, keluar dari loop
        if (c == '\b' && !s.empty()) { // Jika tombol backspace ditekan dan string password tidak kosong
            cout << "\b \b"; // Menghapus satu karakter dari layar
            s.pop_back(); // Menghapus satu karakter dari string password
        } else if (c != '\r' && c != '\b') { // Jika karakter bukan Enter atau backspace
            cout << '*'; // Tampilkan karakter '*' sebagai pengganti karakter password
            s.push_back(c); // Tambahkan karakter ke string password
        }
    }
    new_password = s; // Set password baru dengan nilai dari string password

    ofstream os("Account_info.csv", ios::app); // Membuka file Account_info.csv untuk menambahkan data
    os << new_id << ',' << new_password << '\n'; // Menulis ID baru dan password baru ke file
    os.close(); // Menutup file setelah selesai menulis

    cout << "\n\nAkun berhasil dibuat! Silakan login.\n"; // Menampilkan pesan akun berhasil dibuat
    customer(); // Memanggil fungsi menu customer setelah membuat akun baru
}

void saran(){
    string saran; // Variabel untuk menyimpan saran yang dimasukkan oleh pengguna
    cout << "Masukkan saran Anda: "; // Menampilkan pesan memasukkan saran kepada pengguna
    cin.ignore(); // Mengabaikan karakter newline yang tersisa di buffer
    getline(cin, saran); // Mengambil input saran dari pengguna

    ofstream file("saran.txt", ios::app); // Membuka file "saran.txt" untuk menambahkan data
    if (file.is_open()) { // Memeriksa apakah file berhasil dibuka
        file << saran << endl; // Menulis saran ke dalam file
        file.close(); // Menutup file setelah selesai menulis
        cout << "Saran berhasil disimpan.\n"; // Menampilkan pesan bahwa saran berhasil disimpan
    } else { // Jika file tidak berhasil dibuka
        cout << "Gagal membuka file.\n"; // Menampilkan pesan bahwa gagal membuka file
    }
    waitForEnter(); // Menunggu pengguna menekan tombol enter sebelum melanjutkan
    menu_c(); // Memanggil fungsi menu customer setelah selesai menyimpan saran
}

void menu_permintaan_nasabah() {
    int pilih; // Variabel untuk menyimpan pilihan pengguna
    string id, user, pw; // Variabel untuk menyimpan ID, nama, dan password pengguna
    
    do {
        system("cls"); // Membersihkan layar
        system("color 2"); // Mengatur warna tampilan

        // Menampilkan opsi menu
        cout << "1. Minta Hapus Akun Nasabah\n";
        cout << "2. Minta Perbarui Data Nasabah\n";
        cout << "3. Kembali ke menu nasabah\n";
        cout << "Masukkan Pilihan Anda: ";
        cin >> pilih; // Menerima input pilihan dari pengguna
        
        // Memeriksa apakah input valid
        if (cin.fail()) {
            cin.clear(); // Membersihkan status kesalahan input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan sisa input yang salah
            cout << "Input tidak valid! Masukkan hanya angka 1, 2, atau 3.\n";
            system("pause"); // Menunggu pengguna menekan tombol sebelum melanjutkan
            continue; // Melanjutkan loop untuk input ulang
        }

        // Memeriksa apakah pilihan berada dalam rentang yang valid
        if (pilih < 1 || pilih > 3) {
            cout << "Input tidak valid! Masukkan hanya angka 1, 2, atau 3.\n";
            system("pause");
            continue;
        }
        
        switch (pilih) {
            case 1:
                // Meminta informasi untuk menghapus akun
                cout << "Masukkan ID Anda: ";
                cin >> id;
                cout << "Masukkan Nama Anda: ";
                cin >> user;
                cout << "Masukkan Password Anda: ";
                cin >> pw;
                {
                    // Membuka file "nasabah.csv" untuk menambahkan data penghapusan akun
                    ofstream file("nasabah.csv", ios::app);
                    if (file.is_open()) {
                        file << id << "," << user << "," << pw << ",hapus akun\n";
                        file.close();
                        cout << "Data berhasil disimpan ke file.\n";
                    } else {
                        cout << "Gagal membuka file.\n";
                    }
                }
                break;

            case 2:
                // Meminta informasi untuk memperbarui data nasabah
                cout << "Masukkan ID Anda: ";
                cin >> id;
                cout << "Masukkan Nama Anda: ";
                cin >> user;
                cout << "Masukkan Password Anda: ";
                cin >> pw;
                
                int choice; // Variabel untuk menyimpan pilihan perbaruan data
                do {
                    system("cls");
                    // Menampilkan opsi perbaruan data
                    cout << "\n\n\n\t\t1. Perbarui Nama\n";
                    cout << "\t\t2. Perbarui Tanggal Lahir\n";
                    cout << "\t\t3. Perbarui Umur\n";
                    cout << "\t\t4. Perbarui Alamat\n";
                    cout << "\t\t5. Perbarui Nomor Telepon\n";
                    cout << "\t\t6. Selesai\n";
                    cout << "Pilih opsi: ";
                    cin >> choice;

                    // Memeriksa apakah input opsi valid
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Input tidak valid! Masukkan hanya angka antara 1 dan 6.\n";
                        system("pause");
                        continue;
                    }

                    // Memeriksa apakah opsi berada dalam rentang yang valid
                    if (choice < 1 || choice > 6) {
                        cout << "Input tidak valid! Masukkan hanya angka antara 1 dan 6.\n";
                        system("pause");
                        continue;
                    }

                    string new_data; // Variabel untuk menyimpan data baru yang dimasukkan pengguna
                    switch (choice) {
                        case 1:
                            cout << "Masukkan Nama Baru: ";
                            cin >> new_data;
                            break;
                        case 2:
                            cout << "Masukkan Tanggal Lahir Baru (dd-mm-yyyy): ";
                            cin >> new_data;
                            break;
                        case 3:
                            cout << "Masukkan Umur Baru: ";
                            cin >> new_data;
                            break;
                        case 4:
                            cout << "Masukkan Alamat Baru: ";
                            cin >> new_data;
                            break;
                        case 5:
                            cout << "Masukkan Nomor Telepon Baru: ";
                            cin >> new_data;
                            break;
                        case 6:
                            cout << "Selesai\n";
                            break;
                    }

                    if (choice != 6) {
                        // Membuka file "nasabah.csv" untuk menambahkan data perbaruan
                        ofstream file("nasabah.csv", ios::app);
                        if (file.is_open()) {
                            file << id << "," << user << "," << pw << ",perbarui," << choice << "," << new_data << "\n";
                            file.close();
                            cout << "Permintaan berhasil dikirim.\n";
                        } else {
                            cout << "Permintaan gagal.\n";
                        }
                        system("pause");
                    }
                } while (choice != 6);
                break;

            case 3:
                cout << "Kembali ke menu nasabah\n";
                break;
        }

        if (pilih != 3) {
            system("pause");
        }
    } while (pilih != 3);
}

void menu_baru() {
    int choice; // Variabel untuk menyimpan pilihan pengguna
    Bank B; // Objek Bank untuk mengelola data nasabah
    do {
        system("cls"); // Membersihkan layar
        system("color 2"); // Mengatur warna tampilan
        cout << "\n\n\t\t\tSISTEM MANAJEMEN BANK"; // Menampilkan judul program
        cout << "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SELAMAT DATANG"
             << " DI MENU PENDAFTARAN \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n"; // Menampilkan pesan selamat datang
        cout << "\n\t\t1. Daftar Menjadi Nasabah Baru\n"; // Menampilkan opsi daftar nasabah baru
        cout << "\t\t0. Exit\n\n\n\n\n\t\t Masukkan Pilihan Anda:"; // Menampilkan instruksi untuk memilih opsi
        cin >> choice; // Menerima input pilihan dari pengguna

        // Memeriksa apakah input valid
        if (cin.fail()) {
            cin.clear(); // Membersihkan status kesalahan input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan sisa input yang salah
            cout << "Input tidak valid! Masukkan hanya angka 0 atau 1.\n"; // Menampilkan pesan kesalahan input
            system("pause"); // Menunggu pengguna menekan tombol sebelum melanjutkan
            continue; // Melanjutkan loop untuk input ulang
        }

        // Memeriksa apakah pilihan berada dalam rentang yang valid
        if (choice != 0 && choice != 1) {
            cout << "Input tidak valid! Masukkan hanya angka 0 atau 1.\n"; // Menampilkan pesan kesalahan input
            system("pause"); // Menunggu pengguna menekan tombol sebelum melanjutkan
            continue;
        }

        system("cls"); // Membersihkan layar
        switch (choice) {
            case 1:
                B.read_data(); // Memanggil metode read_data dari objek Bank untuk mendaftar nasabah baru
                break;
            case 0:
                main(); // Kembali ke fungsi main untuk keluar dari program
                break;
        }

    } while (choice != 0 && choice != 1); // Melanjutkan loop selama pilihan tidak 0 atau 1
}

void menu_c(void)
{
    int choice; // Variabel untuk menyimpan pilihan pengguna
    Bank B; // Objek Bank untuk mengelola data nasabah
    while (true) { // Loop tak terbatas untuk menampilkan menu terus-menerus
        system("cls"); // Membersihkan layar
        system("color 2"); // Mengatur warna tampilan
	    cout << "\n\n\t\t\tSISTEM MANAJEMEN BANK"; // Menampilkan judul program
        cout << "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SELAMAT DATANG"
		     << " DI MENU NASABAH \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n"; // Menampilkan pesan selamat datang
        cout << "\n\t\t1.Kirim Permintaan pada Staff\n"; // Menampilkan opsi untuk mengirim permintaan pada staf
        cout << "\t\t2.Transaksi\n"; // Menampilkan opsi untuk melakukan transaksi
        cout << "\t\t3.Cek detail akun\n"; // Menampilkan opsi untuk mengecek detail akun
        cout << "\t\t4.Transfer\n"; // Menampilkan opsi untuk melakukan transfer
        cout << "\t\t5.Saran\n"; // Menampilkan opsi untuk memberikan saran
        cout << "\t\t0.Exit\n\n\n\n\n\t\t Masukkan Pilihan Anda:"; // Menampilkan instruksi untuk memilih opsi
        cin >> choice; // Menerima input pilihan dari pengguna

        if (cin.fail()) { // Memeriksa apakah input valid
            cout << "Input Tidak Valid! Coba Lagi...\n"; // Menampilkan pesan kesalahan input
            cin.clear(); // Membersihkan status kesalahan input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan sisa input yang salah
            fordelay(1000000000); // Menghentikan eksekusi untuk beberapa waktu
            continue; // Melanjutkan loop untuk input ulang
        }
        system("cls"); // Membersihkan layar
        switch (choice)
        {
            case 1:
                menu_permintaan_nasabah(); // Memanggil menu untuk mengirim permintaan nasabah
                break;
            case 2:
                B.deposit_withdraw(logged_in_acc_no); // Memanggil metode deposit_withdraw dari objek Bank
                break;
            case 3:
                B.search_c(logged_in_acc_no); // Memanggil metode search_c dari objek Bank
                break;
            case 4:
                B.transfer(logged_in_acc_no); // Memanggil metode transfer dari objek Bank
                break;
            case 5: 
                saran(); // Memanggil fungsi untuk memberikan saran
                break;
            case 0:
                main(); // Kembali ke fungsi main untuk keluar dari program
                break;
            default:
                cout << "Input tidak Valid!\nSesuaikan dengan pilihan yang ada!" << endl; // Menampilkan pesan kesalahan input
                fordelay(1000000000); // Menghentikan eksekusi untuk beberapa waktu
                break;
        }
    }
}

int main() {
    int ch; // Variabel untuk menyimpan pilihan pengguna
    cout << "\n\n\n\n\n\t\t\t\tSelamat datang di sistem bank kami"; // Menampilkan pesan selamat datang
    for (int i = 0; i < 6; i++) { // Loop untuk menampilkan titik-titik sebagai efek tunggu
        fordelay(100000000); // Menghentikan eksekusi untuk beberapa waktu
        cout << "."; // Menampilkan titik
    }

    while (true) { // Loop tak terbatas untuk menampilkan menu terus-menerus
        system("cls"); // Membersihkan layar
        system("color 4"); // Mengatur warna tampilan
        cout << "\t\t\t ---------------------" << endl; // Menampilkan garis pembatas
        cout << "\t\t\t| SISTEM MANAJEMEN BANK |" << endl; // Menampilkan judul program
        cout << "\t\t\t ---------------------" << endl; // Menampilkan garis pembatas
        system("color 3"); // Mengatur warna tampilan
        cout << "\n\n\t\t\t\t MENU\n"; // Menampilkan menu
        cout << "\n\t\t1. Staff "; // Menampilkan opsi untuk menu staff
        cout << "\n\t\t2. Nasabah "; // Menampilkan opsi untuk menu nasabah
        cout << "\n\t\t3. Exit "; // Menampilkan opsi untuk keluar dari program
        cout << "\n\t\tMasukkan Pilihan Anda: "; // Menampilkan instruksi untuk memilih opsi

        cin >> ch; // Menerima input pilihan dari pengguna

        if (cin.fail()) { // Memeriksa apakah input valid
            cout << "Input Tidak Valid! Coba Lagi...\n"; // Menampilkan pesan kesalahan input
            cin.clear(); // Membersihkan status kesalahan input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan sisa input yang salah
            continue; // Melanjutkan loop untuk input ulang
        }

        switch (ch) { // Memeriksa pilihan pengguna
            case 1:
                employee(); // Memanggil fungsi untuk menu staff
                break;
            case 2:
                customer(); // Memanggil fungsi untuk menu nasabah
                break;
            case 3:
                close(); // Memanggil fungsi untuk keluar dari program
                return 0; // Mengakhiri program dengan nilai 0
            default:
                cout << "Input Tidak Valid! Coba Lagi...\n"; // Menampilkan pesan kesalahan input
                fordelay(1000000000); // Menghentikan eksekusi untuk beberapa waktu
                break;
        }
    }
    return 0; // Mengakhiri program dengan nilai 0
}
