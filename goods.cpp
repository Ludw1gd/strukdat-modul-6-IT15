#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

void clearScreen() 
{        // Fungsi untuk membersihkan layar tiap pemanggilan fungsi
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

class goods 
{
    string goods_code;
    string goods_name;
    
    int stock_amount;
    string description;

public:
    goods(string code, string name, int jumlah, string desc)
        : goods_code(code), goods_name(name), stock_amount(jumlah), description(desc) {}

    string get_goods_code() const 
    { 
        return goods_code; 
    }
    string get_goods_name() const 
    { 
        return goods_name; 
    }
    
    int get_stock_amount() const 
    { 
        return stock_amount; 
    }
    string get_description() const 
    { 
        return description; 
    }

    void set_goods_name(const string &name) 
    { 
        goods_name = name; 
    }

    void set_amount_stock(int jumlah) 
    { 
        stock_amount = jumlah; 
    }
    
    void set_description(const string &desc) 
    { 
        description = desc; 
    }

    void show_goods() const 
    {
        cout << "Kode: " << goods_code << ", Nama: " << goods_name
             << ", Jumlah: " << stock_amount << ", Deskripsi: " << description << endl;
    }
};

vector<goods> list_goods;

void add_goods() 
{
    string code, name, description;
    char next;
    int amount;
    do
    {
        clearScreen();
        bool is_duplicate;
        // Looping sampai pengguna memasukkan kode barang yang tidak duplikat
        do
        {
            is_duplicate = false;
            cout << "Masukkan Kode Barang: ";
            cin >> code;

            // Memeriksa apakah kode barang sudah ada
            for (const auto &goods : list_goods) 
            {
                if (goods.get_goods_code() == code) 
                {
                    is_duplicate = true;
                    cout << "Kode barang sudah ada. Silakan masukkan kode barang yang berbeda." << endl;
                    break;
                }
            }
        } 
        while (is_duplicate); // ulangi jika duplikat

        cout << "Masukkan Nama Barang: ";
        cin.ignore();
        getline(cin, name);
        
        while (true) 
        {
            cout << "Masukkan Jumlah Stok: ";
            cin >> amount;

            if (cin.fail()) 
            {
                cin.clear(); // Menghapus flag kesalahan
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
                cout << "Input tidak valid. Silakan masukkan angka." << endl;
            } 
            
            else 
            {
                break; // Input valid, keluar dari loop
            }
        }
        cout << "Masukkan Deskripsi Barang: ";
        cin.ignore();
        
        getline(cin, description);
        goods new_goods(code, name, amount, description);
        list_goods.push_back(new_goods);
        cout << "Barang berhasil ditambahkan!" << endl;
        cout << "\nTekan 1 untuk menambahkan barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Barang: ";
        cin >> next;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    }
    
    while (next == '1');
}

void show_all_goods()
{
    char next;
    do
    {
        if (list_goods .empty()) 
        {
            cout << "Tidak ada barang dalam daftar." << endl;
        } 
        
        else 
        {
            cout << "Daftar Barang:" << endl;
            
            for (const auto &goods : list_goods) 
            {
                goods .show_goods();
            }
        }
        cout << "\nKetik bebas untuk balik ke Menu Manajemen Barang.";
        cin >> next;

        while (getchar() != '\n');
    } 
    
    while (next == '1');
}

void find_goods()
{
    string code;
    char next;

    do
    {
        clearScreen();
        cout << "Masukkan Kode Barang yang Dicari: ";
        cin >> code;

        bool found = false;
        for (const auto &goods : list_goods) 
        {
            if (goods .get_goods_code() == code) 
            {
                goods .show_goods();
                found = true;
                
                break;
            }
        }

        if (!found)
        {
            cout << "Barang tidak ditemukan." << endl;    
        }
        cout << "\nTekan 1 untuk mencari barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Barang: ";
        cin >> next;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    }

    while (next == '1');
}

void change_goods()
{
    string code;
    char next;

    do
    {
        clearScreen();
        cout << "Masukkan Kode Barang yang Akan Diubah: ";
        cin >> code;

        bool found = false;
        for (auto &goods : list_goods) 
        {
            if (goods.get_goods_code() == code) 
            {
                string name, description;
                
                int amount;
                cout << "\nMasukkan Nama Barang Baru: ";
                cin.ignore();
                
                getline(cin, name);

                while (true)
                {
                    cout << "Masukkan Jumlah Stok: ";
                    cin >> amount;

                    if (cin.fail()) 
                    {
                        cin.clear(); // Menghapus flag kesalahan
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
                        cout << "Input tidak valid. Silakan masukkan angka." << endl;
                    } 
                    
                    else 
                    {
                        break; // Input valid, keluar dari loop
                    }
                }
                cout << "Masukkan Deskripsi Baru: ";
                cin.ignore();
                
                getline(cin, description);
                goods.set_goods_name(name);
                goods.set_amount_stock(amount);
                goods.set_description(description);

                cout << "Barang berhasil diubah!" << endl;
                found = true;
                
                break;
            }
        }

        if (!found)
        {
            cout << "Barang tidak ditemukan." << endl;
        }
        cout << "\nTekan 1 untuk mengubah barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Barang: ";
        cin >> next;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    }

    while (next == '1');
}

void delete_goods()
{
    string code;
    char next;

    do
    {
        clearScreen();
        cout << "Masukkan Kode Barang yang Akan Dihapus: ";
        cin >> code;
        
        bool found = false;
        for (auto it = list_goods .begin(); it != list_goods .end(); ++it) 
        {
            if (it ->get_goods_code() == code) 
            {
                list_goods.erase(it);
                cout << "Barang berhasil dihapus!" << endl;
                found = true;

                break;
            }
        }

        if (!found)
        {
            cout << "Barang tidak ditemukan." << endl;
        }
        cout << "\nTekan 1 untuk menghapus barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Barang: ";
        cin >> next;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    }

    while (next == '1');
}

void goods_management_menu() 
{
    clearScreen();
    int choices;
    do {
        cout << "\n--- Menu Manajemen Barang ---" << endl;
        cout << "1. Tambah Barang Baru" << endl;
        cout << "2. Tampilkan Semua Barang" << endl;
        cout << "3. Cari Barang" << endl;
        cout << "4. Ubah Data Barang" << endl;
        cout << "5. Hapus Barang" << endl;
        cout << "6. Keluar dari Menu utama" << endl;
        cout << "Pilih opsi: ";
        cin >> choices;

        switch (choices) 
        {
            case 1:
                clearScreen();
                add_goods();
                break;
            case 2:
                clearScreen();
                show_all_goods();
                break;
            case 3:
                clearScreen();
                find_goods();
                break;
            case 4:
                clearScreen();
                change_goods();
                break;
            case 5:
                clearScreen();
                delete_goods();
                break;
            case 6:
                clearScreen();
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } 
    
    while (choices != 6);
}

void incoming_goods_management_menu();
void outgoing_goods_management_menu();
void report();

void main_menu() 
{
    int choices;
    do {
        cout << "\n--- Menu Utama ---" << endl;
        cout << "1. Menu Manajemen Barang" << endl;
        cout << "2. Menu Manajemen Pemasukan Barang" << endl;
        cout << "3. Menu Manajemen Pengeluaran Barang" << endl;
        cout << "4. Laporan" << endl;
        cout << "5. Keluar dari Program" << endl;
        cout << "Pilih opsi: ";
        cin >> choices;

        switch (choices) 
        {
            case 1:
                goods_management_menu();
                break;
            case 2:
                clearScreen();
//                incoming_goods_management_menu();
                break;
            case 3:
                clearScreen();
//                outgoing_goods_management_menu();
                break;
            case 4:
                clearScreen();
//                report();
                break;
            case 5:
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } 
    
    while (choices != 5);
}

int main() {
    main_menu();

    return 0;
}