#include <iostream>
#include <conio.h>
using namespace std;

struct Player {
    string name;
    char symbol;
};

void logo (){
    cout << R"(
  ____       _                       _     ____        _                     
 / ___|  ___| | __ _ _ __ ___   __ _| |_  |  _ \  __ _| |_ __ _ _ __   __ _  
 \___ \ / _ \ |/ _` | '_ ` _ \ / _` | __| | | | |/ _` | __/ _` | '_ \ / _` | 
  ___) |  __/ | (_| | | | | | | (_| | |_  | |_| | (_| | || (_| | | | | (_| | 
 |____/ \___|_|\__,_|_| |_| |_|\__,_|\__| |____/ \__,_|\__\__,_|_| |_|\__, | 
                                                                      |___/  )"<< endl;
    cout << ' ';
	for (int i = 0; i < 77; i++) cout << "=";
    cout << endl;
}

void logo1 (){
    cout << R"(
 _  _  __  _  _    __  __ _  ____  __  __ _  __  ____  _  _ 
( \/ )/  \( \/ )  (  )(  ( \(  __)(  )(  ( \(  )(_  _)( \/ )
 )  ((  O ))  (    )( /    / ) _)  )( /    / )(   )(   )  / 
(_/\_)\__/(_/\_)  (__)\_)__)(__)  (__)\_)__)(__) (__) (__/  
)" << endl;
    for (int i = 0; i < 60; i++) cout << "=";
    cout << endl;
}

string mid(string teks, int lebar){
	int totalpadding = lebar - teks.length();
	int lebarkiri = totalpadding/2;
	int lebarkanan = totalpadding - lebarkiri;
	string hasil = "";
	for (int i = 0; i < lebarkiri; i++) hasil += " ";
	hasil += teks;
	for (int i = 0; i < lebarkanan; i++) hasil += " ";
	return hasil;
}

int pilihKesulitan() {
    logo();
    int level;
    cout << "=== PILIH TINGKAT KESULITAN ===\n";
    cout << "1. Mudah\n";
    cout << "2. Sedang\n";
    cout << "3. Sulit\n";
    cout << "Pilih: ";
    cout <<"asdasdas";
    cin >> level;
    while (cin.fail() || level < 1 || level > 3) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Pilihan tidak valid. Ulangi: ";
        cin >> level;
    }
    system("pause"); system("cls");
    return level;
}
void mulai(){
	logo();
	Player user;
    user.symbol = 'X';

    cout << "Masukkan nama pemain: ";
    getline(cin, user.name);
    system("pause"); system("cls");

    int level = pilihKesulitan();

    int size;
    logo ();
    cout << "Masukkan ukuran papan (3 - 10): ";
    cin >> size;
    while (cin.fail() || size < 3 || size > 10) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Ukuran tidak valid. Masukkan ukuran (3 - 10): ";
        cin >> size;
    }
    system("pause"); system("cls");
    getch();
}

void about() {
    logo1();
    cout << mid("TENTANG PERMAINAN", 60) << endl;
    cout << "============================================================\n";
    cout << "Selamat datang di permainan Tic Tac Toe versi terminal!\n\n";
    cout << "FITUR UNGGULAN:\n";
    cout << "- Tampilan visual ASCII art menarik.\n";
    cout << "- Navigasi menu menggunakan tombol keyboard (W/S dan Enter).\n";
    cout << "- Pilihan tingkat kesulitan AI:\n";
    cout << "   > Mudah    : AI memilih langkah secara acak.\n";
    cout << "   > Sedang   : AI mencoba menang jika bisa.\n";
    cout << "   > Sulit    : Menggunakan algoritma minimax.\n";
    cout << "- Ukuran papan bisa dipilih (3x3 hingga 10x10).\n";
    cout << "- Nama pemain dapat dimasukkan secara manual.\n\n";

    cout << "CARA BERMAIN:\n";
    cout << "1. Masukkan nama pemain saat diminta.\n";
    cout << "2. Pilih tingkat kesulitan untuk AI lawan.\n";
    cout << "3. Masukkan ukuran papan (misal 3 untuk 3x3).\n";
    cout << "4. Saat giliran Anda, pilih posisi kosong di papan.\n";
    cout << "5. Siapa yang berhasil membuat barisan simbol (X/O)\n";
    cout << "   dalam satu garis lurus, dialah pemenangnya!\n\n";

    cout << "KREDIT:\n";
    cout << "Dibuat oleh:\n";
    cout << "- Developer 1: Ida Bagus Kevin Adiwiguna\n";
    cout << "- Developer 2: I Gde Surya Laksana Diputra\n";
    cout << "- Developer 3: Andre Astamam\n\n";

    cout << "Terima kasih telah memainkan game ini!\n";
    cout << "Selamat Bermain\n";
    getch();
    system("cls");
}

void menu_awal() {
	int tampil = 0;
    char input;
    string menuawal[3] = {"Start", "About", "Exit"};

    while (true) {
    	logo();
        for (int i = 0; i < 3; i++) {
            cout << "|";
            if (i == tampil) cout << "\033[1;34m";
            else cout << "\033[0m";
			cout << mid(menuawal[i], 77) << "\033[0m|\n";
		}
		cout << ' ';
		for (int i = 0; i < 77; i++) cout << "=";
        input = getch();
        switch (input) {
            case 'w':
		    case 'W':
		        tampil = (tampil == 0) ? 2 : tampil - 1;
		        break;
		    case 's':
		    case 'S':
		        tampil = (tampil == 2) ? 0 : tampil + 1;
		        break;
            case 13: // enter
                if (tampil == 0) {
                	system("cls"); mulai();
                } else if (tampil == 1) {
                    system("cls"); about();
                } else if (tampil == 2){
                	return;
				}
                break;
        }
        system("cls");
    }
}

int main() {
    menu_awal();
}
