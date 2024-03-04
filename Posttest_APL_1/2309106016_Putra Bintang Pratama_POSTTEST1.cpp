#include <iostream>
#include <iomanip>
using namespace std;



int main(){
    int i;
    string usename,password;
    int nomor;    
    float rupiah,dollar,yen,euro; 
    cout << endl << "Selamat datang di program konversi mata uang" << endl;
 
    for (i = 1; i < 4; i++) {
    cout << "Masukan username : ";
    cin >> usename;
    cout << "Masukan password : ";
    cin >> password;
  
        if(usename == "Bintang" && password == "2309106016"){
            cout << "Anda berhasil login"<< endl;
                do{
                    cout << "|Program Konversi Mata Uang C++|POSTTEST 1|" << endl;
                    cout << "-------------------------------------------" << endl;
                    cout << "1. Rupiah" << endl;
                    cout << "2. Dollar" << endl;
                    cout << "3. Yen" << endl;
                    cout << "4. Euro" << endl;
                    cout << "5. Keluar" << endl;
                    cout << "Masukkan Nomor Menu Yang Anda Inginkan: " << endl;
                    cin >> nomor;
                    switch (nomor){
                        
                    case 1:
                        cout << "Rupiah" << endl;
                        cout << "Silahkan masukkan nilai rupiah: " << endl;
                        cin >> rupiah;
                        dollar = rupiah/15600;
                        yen = rupiah/104;
                        euro = rupiah/17000; 
                        cout << "Dollar: "<< dollar <<" Yen: "<<yen<<" Euro: "<<euro<< endl;
                    break;
                    case 2:
                        cout << "Dollar" << endl;
                        cout << "Silahkan masukkan nilai dollar: " << endl;
                        cin >> dollar;
                        rupiah = dollar*15600;
                        yen = dollar*150;
                        euro = dollar*0.92; 
                        cout << "Rupiah: "<< rupiah <<" Yen: "<<yen<<" Euro: "<<euro<< endl;
                    break;
                    case 3:
                        cout << "Yen" << endl;
                        cout << "Silahkan masukkan nilai yen: " << endl;
                        cin >> yen;
                        dollar = yen*0.0067;
                        rupiah = yen*104.61;
                        euro = yen*0.0061; 
                        cout << "Dollar: "<< dollar <<" Rupiah: "<< rupiah <<" Euro: "<< euro << endl;        
                    break;
                    case 4:
                        cout << "Euro" << endl;
                        cout << "Silahkan masukkan nilai euro: " << endl;
                        cin >> euro;
                        dollar = euro*1.09;
                        rupiah = euro*17000;
                        yen = euro*162.93; 
                        cout << "Dollar :"<< dollar <<" Rupiah: "<<rupiah<<" Yen: "<<yen<< endl;
                    case 5:
                        cout << "Terima kasih telah menggunakan program kami!" << endl;
                        break;
                    
                    }
                    }while(nomor!=5);
                        return 0;  
                
        }
        else {
            cout << "Username atau password anda salah! " << i << "(x)" << endl;
        }
    }
    if (usename != "Bintang" && password != "2309106016")
    cout << "Anda telah salah password sebanyak 3 kali! \n"
         << "Harap memulai ulang program kembali!";
    return 0;

}
