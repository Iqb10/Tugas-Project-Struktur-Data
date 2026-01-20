#include <iostream>
#include <string>
using namespace std;

/* ================== STACK ================== */
struct NodeStack {
    int id;
    string namaTugas;
    NodeStack* next;
};

struct StackMahasiswa {
    NodeStack* top = NULL;

    void push(int id, string nama) {
        NodeStack* tugasBaru = new NodeStack;
        tugasBaru->id = id;
        tugasBaru->namaTugas = nama;
        tugasBaru->next = top;
        top = tugasBaru;
        cout << "\n[BERHASIL] Tugas '" << nama << "' telah ditambahkan.\n";
    }

    void pop() {
        if (top == NULL) {
            cout << "\n[ERROR] Daftar kosong!\n";
            return;
        }
        NodeStack* temp = top;
        cout << "\n[UNDO] Membatalkan tugas: " << top->namaTugas << endl;
        top = top->next;
        delete temp;
    }

    void display() {
        if (top == NULL) {
            cout << "\n(Belum ada tugas)\n";
            return;
        }
        NodeStack* current = top;
        while (current != NULL) {
            cout << "[ID: " << current->id << "] " << current->namaTugas << endl;
            current = current->next;
        }
    }
};

/* ================== TREE ================== */
struct Node {
    string nama;
    Node* firstchild;
    Node* turunan;

    StackMahasiswa tugas;
};

class Pohon {
public:
    Node* root;

    Pohon(string value) {
        root = Buatnode(value);
    }

    Node* Buatnode(string nama) {
        Node* node = new Node;
        node->nama = nama;
        node->firstchild = nullptr;
        node->turunan = nullptr;
        return node;
    }

    Node* Carinode(Node* node, string nama) {
        if (node == nullptr)
            return nullptr;
        else if (node->nama == nama)
            return node;
        else {
            Node* found = Carinode(node->firstchild, nama);
            if (found != nullptr)
                return found;
            else
                return Carinode(node->turunan, nama);
        }
    }

    void Tambahkategori(string namaparent, string namakategori) {
        Node* parent = Carinode(root, namaparent);
        if (parent == nullptr) {
            cout << "Kategori induk tidak ditemukan.\n";
            return;
        }

        Node* child = Buatnode(namakategori);
        if (parent->firstchild == nullptr) {
            parent->firstchild = child;
        } else {
            Node* temp = parent->firstchild;
            while (temp->turunan != nullptr)
                temp = temp->turunan;
            temp->turunan = child;
        }
        cout << "Kategori berhasil ditambahkan.\n";
    }

    void Tampil(Node* node, int level) {
        if (node == nullptr) return;

        for (int i = 0; i < level; i++)
            cout << "|   ";
        cout << "|-- " << node->nama << endl;

        TampilStack(node->tugas.top, level + 1);
        Tampil(node->firstchild, level + 1);
        Tampil(node->turunan, level);
    }

    void TampilStack(NodeStack* top, int level) {
        NodeStack* cur = top;
        while (cur != nullptr) {
            for (int i = 0; i < level; i++)
                cout << "|   ";
            cout << "|-- [TUGAS] " << cur->namaTugas << endl;
            cur = cur->next;
        }
    }
    
    void TambahTugas(string namaKategori, int id, string tugasBaru) {
        Node* kategori = Carinode(root, namaKategori);
        if (kategori == nullptr) {
            cout << "Kategori tidak ditemukan.\n";
            return;
        }
        kategori->tugas.push(id, tugasBaru);
        cout << "Tugas berhasil ditambahkan ke kategori " << namaKategori << endl;
    }

    void UndoTugas(string namaKategori) {
        Node* kategori = Carinode(root, namaKategori);
        if (kategori == nullptr) {
            cout << "Kategori tidak ditemukan.\n";
            return;
        }
        kategori->tugas.pop();
    }
};

/* ================== MAIN ================== */
int main() {
    int pilihan, idIn;
    string namaIn, repo, parent, kategori;

    cout << "Masukkan Nama Repository: ";
    getline(cin, repo);

    Pohon pohon(repo);

    do {
        cout << "\n=======================================\n";
        cout << "\t      TODO MANAGER\n";
        cout << "=======================================\n";
        cout << " 1. Tambah Kategori\n";
        cout << " 2. Tambah Tugas Baru\n";
        cout << " 3. Undo (Batalkan Tugas Terakhir)\n";
        cout << " 4. Tampilkan\n";
        cout << " 5. Keluar Program\n";
        cout << " Masukkan Pilihan (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cin.ignore();
                cout << "Kategori Induk : ";
                getline(cin, parent);

                cout << "Kategori Baru  : ";
                getline(cin, kategori);

                pohon.Tambahkategori(parent, kategori);
                break;
            case 2:
                cin.ignore();
                cout << " > Masukkan Nama Kategori : "; 
                getline(cin, kategori);
                cout << " > Masukkan ID Tugas   : "; cin >> idIn;
                cin.ignore();
                cout << " > Masukkan Nama Tugas : "; getline(cin, namaIn);

                pohon.TambahTugas(kategori, idIn, namaIn);
                break;
            case 3:
                cin.ignore();
                cout << "Masukkan Nama Kategori : ";
                getline(cin, kategori);
                pohon.UndoTugas(kategori);
                break;
            case 4:
                cout << "\n=======================================";
                cout << "\n       DAFTAR TUGAS MAHASISWA";
                cout << "\n=======================================\n";
                pohon.Tampil(pohon.root, 0);
                cout << endl;
                break;
            case 5:
                cout << "\nKeluar dari program. Terima kasih!\n";
                break;
            default:
                cout << "\n[!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}
