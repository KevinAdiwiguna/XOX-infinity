#include <iostream>
#include <iomanip>
#include <conio.h>


using namespace std;

const int DEPTH_LIMIT = 3;

struct gameConfig
{
    int mode = 0;
    int ukuran = 3;
    int winCondition = 3;
} gameConfig;

int board[3][3];

void clearScreen()
{
    system("cls");
}
void banner()
{
    cout << "\033[6m";
    cout << "\033[1m";
    cout << "\033[3m";
    cout << "\033[37m";
    // cout<<"\033[33m";
    cout << "\033[36m";
    cout << " /$$   /$$  /$$$$$$  /$$   /$$       /$$$$$$ /$$   /$$ /$$$$$$$$ /$$$$$$ /$$   /$$ /$$$$$$ /$$$$$$$$ /$$     /$$\n";
    cout << "| $$  / $$ /$$__  $$| $$  / $$      |_  $$_/| $$$ | $$| $$_____/|_  $$_/| $$$ | $$|_  $$_/|__  $$__/|  $$   /$$/\n";
    cout << "\033[36m";
    cout << "|  $$/ $$/| $$  \\ $$|  $$/ $$/        | $$  | $$$$| $$| $$        | $$  | $$$$| $$  | $$     | $$    \\  $$ /$$/ \n";
    cout << "\033[34m";
    cout << " \\  $$$$/ | $$  | $$ \\  $$$$/         | $$  | $$ $$ $$| $$$$$     | $$  | $$ $$ $$  | $$     | $$     \\  $$$$/  \n";
    cout << "\033[35m";
    cout << "  >$$  $$ | $$  | $$  >$$  $$         | $$  | $$  $$$$| $$__/     | $$  | $$  $$$$  | $$     | $$      \\  $$/   \n";
    cout << " /$$/\\  $$| $$  | $$ /$$/\\  $$        | $$  | $$\\  $$$| $$        | $$  | $$\\  $$$  | $$     | $$       | $$    \n";
    cout << "| $$  \\ $$|  $$$$$$/| $$  \\ $$       /$$$$$$| $$ \\  $$| $$       /$$$$$$| $$ \\  $$ /$$$$$$   | $$       | $$    \n";
    cout << "|__/  |__/ \\______/ |__/  |__/      |______/|__/  \\__/|__/      |______/|__/  \\__/|______/   |__/       |__/    \n";

    cout << "\033[0m";
}

void tampilkanBoard()
{
    clearScreen();
    banner();
    cout << "\n=== TIC TAC TOE (" << gameConfig.ukuran << "x" << gameConfig.ukuran << ") ===\n\n";

    for (int i = 0; i < gameConfig.ukuran; ++i)
    {
       for (int j = 0; j < gameConfig.ukuran; ++j)
        {
            if (board[i][j] == -1)
                cout << " X ";
            else if (board[i][j] == -2)
                cout << " O ";
            else
                cout << " " << board[i][j] << " ";
            
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "-----------\n";
    }
    cout << "\n";
}

void inisialisasiBoard()
{
    int angka = 1;
    for (int i = 0; i < gameConfig.ukuran; ++i)
    {
        for (int j = 0; j < gameConfig.ukuran; ++j)
        {
            board[i][j] = angka++;
        }
    }
}

bool cekArah(int x, int y, int dx, int dy, int simbol)
{
    int count = 1;
    int i = x + dx, j = y + dy;
    while (i >= 0 && i < gameConfig.ukuran && j >= 0 && j < gameConfig.ukuran && board[i][j] == simbol)
    {
        count++;
        i += dx;
        j += dy;
    }
    i = x - dx;
    j = y - dy;
    while (i >= 0 && i < gameConfig.ukuran && j >= 0 && j < gameConfig.ukuran && board[i][j] == simbol)
    {
        count++;
        i -= dx;
        j -= dy;
    }
    return count >= gameConfig.winCondition;
}

bool cekMenang(int x, int y, int simbol)
{
    return cekArah(x, y, 1, 0, simbol) || cekArah(x, y, 0, 1, simbol) ||
           cekArah(x, y, 1, 1, simbol) || cekArah(x, y, 1, -1, simbol);
}

bool papanPenuh()
{
    for (int i = 0; i < gameConfig.ukuran; i++)
    {
        for (int j = 0; j < gameConfig.ukuran; j++)
        {
            if (board[i][j] > 0)
                return false;
        }
    }
    return true;
}

int evaluateBoard()
{
    for (int i = 0; i < gameConfig.ukuran; i++)
    {
        for (int j = 0; j < gameConfig.ukuran; j++)
        {
            if (board[i][j] == -1 && cekMenang(i, j, -1))
                return +10;
            if (board[i][j] == -2 && cekMenang(i, j, -2))
                return -10;
        }
    }
    return 0;
}

int minimax(int depth, bool isMax)
{
    int score = evaluateBoard();

    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth;
    if (papanPenuh() || depth >= DEPTH_LIMIT)
        return 0;

    if (isMax)
    {
        int best = -1000;
        for (int i = 0; i < gameConfig.ukuran; i++)
        {
            for (int j = 0; j < gameConfig.ukuran; j++)
            {
                if (board[i][j] > 0)
                {
                    board[i][j] = -1;
                    int val = minimax(depth + 1, false);
                    board[i][j] = (i * gameConfig.ukuran + j) + 1;
                    best = max(best, val);
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i < gameConfig.ukuran; i++)
        {
            for (int j = 0; j < gameConfig.ukuran; j++)
            {
                if (board[i][j] > 0)
                {
                    board[i][j] = -2;
                    int val = minimax(depth + 1, true);
                    board[i][j] = (i * gameConfig.ukuran + j) + 1;
                    best = min(best, val);
                }
            }
        }
        return best;
    }
}

void botMove()
{
    int bestVal = 1000;
    int bestMoveRow = -1, bestMoveCol = -1;

    for (int i = 0; i < gameConfig.ukuran; i++)
    {
        for (int j = 0; j < gameConfig.ukuran; j++)
        {
            if (board[i][j] > 0)
            {
                board[i][j] = -2;
                int moveVal = minimax(0, true);
                board[i][j] = (i * gameConfig.ukuran + j) + 1;
                if (moveVal < bestVal)
                {
                    bestVal = moveVal;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    if (bestMoveRow != -1 && bestMoveCol != -1)
    {
        board[bestMoveRow][bestMoveCol] = -2;
    }
}

void mainGamePvP()
{
    int giliran = -1;
    int posisi;

    while (true)
    {
        banner();
        tampilkanBoard();
        cout << "Giliran Player " << (giliran == -1 ? "X" : "O") << " (masukkan nomor posisi): ";
        cin >> posisi;

        if (posisi < 1 || posisi > gameConfig.ukuran * gameConfig.ukuran)
        {
            cout << "Input nomor posisi tidak valid.\n";
            system("pause");
            continue;
        }

        int baris = (posisi - 1) / gameConfig.ukuran;
        int kolom = (posisi - 1) % gameConfig.ukuran;

        if (board[baris][kolom] == -1 || board[baris][kolom] == -2)
        {
            cout << "Posisi sudah terisi.\n";
            system("pause");
            continue;
        }

        board[baris][kolom] = giliran;

        if (cekMenang(baris, kolom, giliran))
        {
            tampilkanBoard();
            cout << "Player " << (giliran == -1 ? "X" : "O") << " MENANG!\n";
            break;
        }

        if (papanPenuh())
        {
            tampilkanBoard();
            cout << "Permainan SERI.\n";
            break;
        }

        giliran = (giliran == -1) ? -2 : -1;
    }

    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void mainGamePvBot()
{
    int giliran = -1; // Player selalu X
    int posisi;

    while (true)
    {
        banner();
        tampilkanBoard();

        if (giliran == -1)
        {
            cout << "Giliran Player X (masukkan nomor posisi): ";
            cin >> posisi;

            if (posisi < 1 || posisi > gameConfig.ukuran * gameConfig.ukuran)
            {
                cout << "Input nomor posisi tidak valid.\n";
                system("pause");
                continue;
            }

            int baris = (posisi - 1) / gameConfig.ukuran;
            int kolom = (posisi - 1) % gameConfig.ukuran;

            if (board[baris][kolom] == -1 || board[baris][kolom] == -2)
            {
                cout << "Posisi sudah terisi.\n";
                system("pause");
                continue;
            }

            board[baris][kolom] = giliran;

            if (cekMenang(baris, kolom, giliran))
            {
                tampilkanBoard();
                cout << "Player X MENANG!\n";
                break;
            }
        }
        else
        {
            cout << "Giliran Bot O...\n";
            botMove();

            // Cari posisi terakhir bot pasang
            bool botMenang = false;
            for (int i = 0; i < gameConfig.ukuran && !botMenang; i++)
            {
                for (int j = 0; j < gameConfig.ukuran && !botMenang; j++)
                {
                    if (board[i][j] == -2 && cekMenang(i, j, -2))
                    {
                        botMenang = true;
                    }
                }
            }

            if (botMenang)
            {
                tampilkanBoard();
                cout << "Bot O MENANG!\n";
                break;
            }
        }

        if (papanPenuh())
        {
            tampilkanBoard();
            cout << "Permainan SERI.\n";
            break;
        }

        giliran = (giliran == -1) ? -2 : -1;
    }

    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void tampilkanMenuUtama()
{
    clearScreen();
    banner();
    cout << "=================================================================================================================\n";
    cout << "||                                             TIC TAC TOE GAME                                                ||\n";
    cout << "=================================================================================================================\n";
    cout << "||                                            1. Pilih Mode Permainan                                          ||\n";
    cout << "||                                            2. Mulai Permainan                                               ||\n";
    cout << "||                                            3. Keluar                                                        ||\n";
    cout << "=================================================================================================================\n";
    cout << "                                             Pilih menu (1-3): ";
}

void pilihModePermainan()
{
    clearScreen();
    banner();
    cout << "================================================================================================================\n";
    cout << "||                                              Pilih Mode Permainan                                          ||\n";
    cout << "================================================================================================================\n";
    cout << "||                                             1. Player vs Player                                            ||\n";
    cout << "||                                             2. Player vs Bot                                               ||\n";
    cout << "================================================================================================================\n";
    cout << "                                              Masukkan pilihan (1/2): ";
    int pilihan;
    cin >> pilihan;
    while (pilihan != 1 && pilihan != 2)
    {
        cout << "Input tidak valid. Masukkan 1 atau 2: ";
        cin >> pilihan;
    }
    gameConfig.mode = pilihan;
    cout << "Mode permainan berhasil diset.\n";
    cout << "Tekan enter untuk kembali ke menu utama...";
    cin.ignore();
    cin.get();
}

bool konfirmasiKeluar()
{
    cout << "                                       Apakah Anda yakin ingin keluar? (Y/N): ";
    char jawaban;
    cin >> jawaban;
    jawaban = toupper(jawaban);
    return (jawaban == 'Y');
}

void menuUtama()
{
    bool running = true;

    while (running)
    {

        tampilkanMenuUtama();

        int pilihan;
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            pilihModePermainan();
            break;
        case 2:

            if (gameConfig.mode == 0)
            {
                cout << "Mode permainan belum diset. Silakan pilih mode permainan terlebih dahulu.\n";
                system("pause");
            }
            else
            {
                inisialisasiBoard();
                if (gameConfig.mode == 1)
                {
                    mainGamePvP();
                }
                else
                {
                    mainGamePvBot();
                }
            }
            break;
        case 3:
            if (konfirmasiKeluar())
            {
                running = false;
                cout << "Terima kasih telah bermain. Sampai jumpa!\n";
            }
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            system("pause");
        }
    }
}

int main()
{
    banner();
    inisialisasiBoard();
    menuUtama();
    return 0;
}
