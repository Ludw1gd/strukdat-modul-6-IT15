#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
    
    int amount;
    cout << "Masukkan Kode Barang: ";
    cin >> code;
    cout << "Masukkan Nama Barang: ";
    cin.ignore();
    getline(cin, name);
    cout << "Masukkan Jumlah Stok: ";
    cin >> amount;
    cout << "Masukkan Deskripsi Barang: ";
    cin.ignore();
    getline(cin, description);

    goods new_goods(code, name, amount, description);
    list_goods.push_back(new_goods);
    cout << "Barang berhasil ditambahkan!" << endl;
}

void show_all_goods()
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
}

void find_goods()
{
    string code;
    cout << "Masukkan Kode Barang yang Dicari: ";
    cin >> code;

    for (const auto &goods : list_goods) 
    {
        if (goods .get_goods_code() == code) 
        {
            goods .show_goods();
            
            return;
        }
    }
    cout << "Barang tidak ditemukan." << endl;
}

void change_goods()
{
    string code;
    cout << "Masukkan Kode Barang yang Akan Diubah: ";
    cin >> code;

    for (auto &goods : list_goods) {
        if (goods.get_goods_code() == code) 
        {
            string name, description;
            
            int amount;
            cout << "Masukkan Nama Barang Baru: ";
            cin.ignore();
            
            getline(cin, name);
            cout << "Masukkan Jumlah Stok Baru: ";
            cin >> amount;
            cout << "Masukkan Deskripsi Baru: ";
            cin.ignore();
            
            getline(cin, description);
            goods.set_goods_name(name);
            goods.set_amount_stock(amount);
            goods.set_description(description);

            cout << "Barang berhasil diubah!" << endl;
            
            return;
        }
    }
    cout << "Barang tidak ditemukan." << endl;
}

void delete_goods()
{
    string code;
    cout << "Masukkan Kode Barang yang Akan Dihapus: ";
    cin >> code;

    for (auto it = list_goods .begin(); it != list_goods .end(); ++it) 
    {
        if (it ->get_goods_code() == code) 
        {
            list_goods.erase(it);
            cout << "Barang berhasil dihapus!" << endl;
            
            return;
        }
    }
    cout << "Barang tidak ditemukan." << endl;
}

void goods_management_menu() 
{
    int choices;
    do {
        cout << "\n--- Menu Manajemen Barang ---" << endl;
        cout << "1. Tambah Barang Baru" << endl;
        cout << "2. Tampilkan Semua Barang" << endl;
        cout << "3. Cari Barang" << endl;
        cout << "4. Ubah Data Barang" << endl;
        cout << "5. Hapus Barang" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> choices;

        switch (choices) 
        {
            case 1:
                add_goods();
                break;
            case 2:
                show_all_goods();
                break;
            case 3:
                find_goods();
                break;
            case 4:
                change_goods();
                break;
            case 5:
                delete_goods();
                break;
            case 6:
                cout << "Keluar dari Menu Utama." << endl;
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
        cout << "5. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> choices;

        switch (choices) 
        {
            case 1:
                goods_management_menu();
                break;
            case 2:
                incoming_goods_management_menu();
                break;
            case 3:
                outgoing_goods_management_menu();
                break;
            case 4:
                report();
                break;
            case 5:
                cout << "Keluar dari program." << endl;
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