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
