#include <iostream>
#include <string>

using namespace std;

struct Node {
    int id;
    string namaTugas;
    Node* next;
};

struct StackMahasiswa {
    Node* top = NULL;

    void push(int id, string nama) {
        Node* tugasBaru = new Node;
        tugasBaru->id = id;
        tugasBaru->namaTugas = nama;
        tugasBaru->next = top;
        top = tugasBaru;
        cout << "\n[BERHASIL] Tugas '" << nama << "' telah ditambahkan.\n";
    }

    void pop() {
        if (top == NULL) {
            cout << "\n[ERROR] Daftar kosong! Tidak ada yang bisa dibatalkan.\n";
            return;
        }
        Node* temp = top;
        cout << "\n[UNDO] Membatalkan tugas: " << top->namaTugas << " (ID: " << top->id << ")\n";
        top = top->next;
        delete temp;
    }

    void display() {
        cout << "\n=======================================";
        cout << "\n       DAFTAR TUGAS MAHASISWA";
        cout << "\n=======================================";
        
        if (top == NULL) {
            cout << "\n          (Belum ada tugas)";
        } else {
            Node* current = top;
            int nomor = 1;
            while (current != NULL) {
                cout << "\n " << nomor << ". [ID: " << current->id << "] " << current->namaTugas;
                current = current->next;
                nomor++;
            }
        }
        cout << "\n=======================================\n";
    }
};

int main() {
    StackMahasiswa stackMhs;
    int pilihan, idIn;
    string namaIn;

    do {
        stackMhs.display();
        cout << " PILIHAN MENU :\n";
        cout << " 1. Tambah Tugas Baru\n";
        cout << " 2. Undo (Batalkan Tugas Terakhir)\n";
        cout << " 3. Keluar Program\n";
        cout << " Masukkan Pilihan (1-3): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << " > Masukkan ID Tugas   : "; cin >> idIn;
                cin.ignore();
                cout << " > Masukkan Nama Tugas : "; getline(cin, namaIn);
                stackMhs.push(idIn, namaIn);
                break;
            case 2:
                stackMhs.pop();
                break;
            case 3:
                cout << "\nKeluar dari program. Terima kasih!\n";
                break;
            default:
                cout << "\n[!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);

    return 0;
}
