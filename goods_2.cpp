#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <regex>

using namespace std;

void clearScreen() 
{        // Fungsi untuk membersihkan layar tiap pemanggilan fungsi
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

class Goods 
{
protected:
    string goods_id;
    string goods_name;
    string goods_category;
    int stock_amount;
    string date;

public:
    Goods(string goods_id, string goods_name, string goods_category, int stock_amount, string date)
        : goods_id(goods_id), goods_name(goods_name), goods_category(goods_category), stock_amount(stock_amount), date(date) {}

    string get_goods_code() const 
    { 
        return goods_id; 
    }
    string get_goods_name() const 
    { 
        return goods_name; 
    }
    string get_goods_category() const 
    { 
        return goods_category; 
    }
    
    int get_stock_amount() const 
    {
        return stock_amount; 
    }
    string get_date() const 
    { 
        return date; 
    }

    void set_goods_name(const string &goods_name) 
    { 
        this ->goods_name = goods_name; 
    }
    
    void set_goods_category(const string &goods_category) 
    { 
        this ->goods_category = goods_category; 
    }
    
    void set_stock_amount(int stock_amount) 
    { 
        this ->stock_amount = stock_amount; 
    }
    
    void set_data(const string &date) 
    { 
        this->date = date; 
    }

    virtual void display_goods() const 
    {
        cout << "ID: " << goods_id << "\nNama: " << goods_name << "\nKategori: " << goods_category
             << "\nJumlah: " << stock_amount << "\nTanggal: " << date << endl;
    }
};

class incoming_goods : public Goods 
{
private:
    string supplier;

public:
    incoming_goods(string goods_id, string goods_name, string goods_category, int stock_amount, string date, string supplier)
        : Goods(goods_id, goods_name, goods_category, stock_amount, date), supplier(supplier) {}

    string get_supplier() const 
    { 
        return supplier; 
    }
    
    void set_supplier(const string &supplier) 
    { 
        this ->supplier = supplier; 
    }

    void display_goods() const override 
    {
        Goods::display_goods();
        cout << "Supplier: " << supplier << endl << endl;
    }
};

class inventory_management 
{
private:
    vector <incoming_goods>incoming_goods_list;

    incoming_goods *find_incoming_goods_list(const string &goods_id) 
    {
        for (auto& goods : incoming_goods_list) 
        {
            if (goods .get_goods_code() == goods_id) 
            {
                return &goods;
            }
        }
        
        return nullptr;
    }

    bool isValidDate(const string &date) 
    {
        // Check format YYYY-MM-DD
        regex datePattern(R"((\d{4})-(\d{2})-(\d{2}))");
        smatch match;
    
        if (!regex_match(date, match, datePattern)) 
        {
            return false;
        }

        int year = stoi(match[1] .str());
        int month = stoi(match[2] .str());
        int day = stoi(match[3] .str());

        if (month < 1 || month > 12) 
        {
            return false;
        }

        vector <int>daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
        {
            daysInMonth[1] = 29;
        }

        if (day < 1 || day > daysInMonth[month - 1]) 
        {
            return false;
        }

        return true;
    }

public:
    void add_incoming_goods();
    void view_incoming_goods();
    void find_incoming_goods();
    void update_incoming_goods();
    void delete_incoming_goods();
    void manage_incoming_goods();
};

void inventory_management::add_incoming_goods() 
{
    string goods_id, goods_name, goods_category, date, supplier;

    char next;
    int stock_amount;

    do
    {
        clearScreen();
        bool is_duplicate;

        // Looping sampai pengguna memasukkan kode barang yang tidak duplikat
        do
        {
            is_duplicate = false;
            cout << "Masukkan ID Barang: ";
            cin >> goods_id;

            // Memeriksa apakah kode barang sudah ada
            for (const auto &goods : incoming_goods_list) 
            {
                if (goods.get_goods_code() == goods_id) 
                {
                    is_duplicate = true;
                    cout << "\nKode barang sudah ada. Silakan masukkan kode barang yang berbeda." << endl;
                    break;
                }
            }
        } while (is_duplicate); // ulangi jika duplikat

        cout << "Masukkan Nama Barang: ";
        cin .ignore();
        getline(cin, goods_name);
        cout << "Masukkan Kategori Barang: ";
        cin .ignore();
        getline(cin, goods_category);

        while (true)
        {
            cout << "Masukkan Jumlah Stok: ";
            cin >> stock_amount;

            if (cin.fail())
            {
                cin.clear(); // Menghapus flag kesalahan
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
                cout << "\nInput tidak valid. Silahkan masukkan angka." << endl;
            }

            else
            {
                break; // Input valid, keluar dari loop
            }
        }

        // Validate date input
        do
        {
            cout << "Masukkan Tanggal (YYYY-MM-DD): ";
            cin >> date;

            if (!isValidDate(date))
            {
                cout << "\nFormat tanggal tidak valid atau hari/bulan yang diinput di luar rentang. Silakan coba lagi.\n";
            }
        } while (!isValidDate(date));

        cout << "Masukkan Supplier: ";
        cin .ignore();
        getline(cin, supplier);

        incoming_goods newGoods(goods_id, goods_name, goods_category, stock_amount, date, supplier);
        incoming_goods_list .push_back(newGoods);

        cout << "\nIncoming goods added successfully!" << endl;
        cout << "Tekan 1 untuk menambahkan barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Pemasukan Barang: ";
        cin >> next;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    } while (next == '1');
}

void inventory_management::view_incoming_goods() 
{
    char next;
    do
    {
        if (incoming_goods_list .empty())
        {
            cout << "Tidak ada barang dalam daftar." << endl;
        }

        else
        {
            cout << "=== Daftar Barang Pemasukan ===\n";

            for (const auto &goods : incoming_goods_list) 
            {
                goods .display_goods();
            }
        }
        cout << "\nKetik bebas untuk balik ke Menu Manajemen Barang.";
        cin >> next;

        while (getchar() != '\n');
    } while (next == '1');
}

void inventory_management::find_incoming_goods()
{
    string goods_id;
    char next;
    do
    {
        clearScreen();
        cout << "Masukkan ID Barang yang dicari: ";
        cin >> goods_id;
        cout << endl;

        bool found = false;
        for (const auto &goods : incoming_goods_list)
        {
            if (goods .get_goods_code() == goods_id)
            {
                goods .display_goods();
                found = true;

                break;
            }
        }

        if (!found)
        {
            cout << "\nBarang tidak ditemukan." << endl;
        }
        cout << "\nTekan 1 untuk mencari barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Pemasukan Barang: ";
        cin >> next;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    } while (next == '1');
}

void inventory_management::update_incoming_goods() 
{
    string goods_id;
    char next;
    do
    {
        clearScreen();
        cout << "Masukkan ID Barang yang Akan Diubah: ";
        cin >> goods_id;

        bool found = false;
        for (auto &goods : incoming_goods_list)
        {
            if (goods.get_goods_code() == goods_id) 
            {
                string goods_name, goods_category, date, supplier;
            
                int stock_amount;
                cout << "\nMasukkan Nama Barang Baru: ";
                cin .ignore();
                getline(cin, goods_name);
                cout << "Masukkan Kategori Barang Baru: ";
                cin .ignore();
                getline(cin, goods_category);
                
                while (true)
                {
                    cout << "Masukkan Jumlah Stok Baru: ";
                    cin >> stock_amount;

                    if (cin .fail())
                    {
                        cin .clear(); // Menghapus flag kesalahan
                        cin .ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
                        cout << "\nInput tidak valid. Silahkan masukkan angka." << endl;
                    }

                    else
                    {
                        break; // Input valid, keluar dari loop
                    }
                }

                do
                {
                    cout << "Masukkan Tanggal Baru (YYYY-MM-DD): ";
                    cin >> date;

                    if (!isValidDate(date))
                    {
                        cout << "\nFormat tanggal tidak valid atau hari/bulan yang diinput di luar rentang. Silakan coba lagi." << endl;
                    }
                } while (!isValidDate(date));

                cout << "Masukkan Supplier Baru: ";
                cin .ignore();
                getline(cin, supplier);

                goods .set_goods_name(goods_name);
                goods .set_goods_category(goods_category);
                goods .set_stock_amount(stock_amount);
                goods .set_data(date);
                goods .set_supplier(supplier);

                cout << "Incoming goods updated successfully!" << endl;
                found = true;

                break;
            } 
        }

        if (!found)
        {
            cout << "Barang tidak ditemukan." << endl;
        }
        cout << "\nTekan 1 untuk mengubah barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Pemasukan Barang: ";
        cin >> next;
        cin .ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    } while (next == '1');
}

void inventory_management::delete_incoming_goods() 
{
    string goods_id;
    char next;
    
    do
    {
        clearScreen();
        cout << "Masukkan ID Barang yang Akan Dihapus: ";
        cin >> goods_id;

        bool found = false;
        for (auto it = incoming_goods_list .begin(); it != incoming_goods_list .end(); ++it) 
        {
            if (it ->get_goods_code() == goods_id) 
            {
                incoming_goods_list .erase(it);
                cout << "Barang berhasil dihapus!" << endl;
                found = true;

                break;
            }
        }

        if (!found)
        {
            cout << "Barang tidak ditemukan." << endl;
        }
        cout << "\nTekan 1 untuk menghapus barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Pemasukan Barang: ";
        cin >> next;
        cin .ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    } while (next == '1');
}

void inventory_management::manage_incoming_goods() 
{
    clearScreen();
    int choices;
    do {
        clearScreen();
        cout << "\n===============================================" << endl;
        cout << "        MENU MANAJEMEN PEMASUKAN BARANG" << endl;
        cout << "===============================================" << endl;
        cout << "1. Tambah Data Pemasukan Barang Baru" << endl;
        cout << "2. Tampilkan Semua Data Pemasukan Barang" << endl;
        cout << "3. Cari Data Pemasukan Barang" << endl;
        cout << "4. Ubah Data Pemasukan Barang" << endl;
        cout << "5. Hapus Data Pemasukan Barang" << endl;
        cout << "6. Kembali ke Menu utama" << endl;
        cout << "Pilih opsi: ";
        cin >> choices;

        switch (choices) 
        {
            case 1:
                clearScreen();
                add_incoming_goods();
                break;
            case 2:
                clearScreen();
                view_incoming_goods();
                break;
            case 3:
                clearScreen();
                find_incoming_goods();
                break;
            case 4:
                clearScreen();
                update_incoming_goods();
                break;
            case 5:
                clearScreen();
                delete_incoming_goods();
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

class outgoing_goods : public Goods 
{
private:
    string destination;

public:
    outgoing_goods(string goods_id, string goods_name, string goods_category, int stock_amount, string date, string destination)
        : Goods(goods_id, goods_name, goods_category, stock_amount, date), destination(destination) {}

    string get_destination() const 
    { 
        return destination; 
    }
    
    void set_destination(const string &destination) 
    { 
        this ->destination = destination; 
    }

    void display_goods() const override 
    {
        Goods::display_goods();
        cout << "Destination: " << destination << endl << endl;
    }
};

class outgoing_inventory_management 
{
private:
    vector <outgoing_goods>outgoing_goods_list;

    outgoing_goods *find_outgoing_goods_list(const string &goods_id) 
    {
        for (auto& goods : outgoing_goods_list) 
        {
            if (goods .get_goods_code() == goods_id) 
            {
                return &goods;
            }
        }
        
        return nullptr;
    }

    bool isValidDate(const string &date) 
    {
        // Check format YYYY-MM-DD
        regex datePattern(R"((\d{4})-(\d{2})-(\d{2}))");
        smatch match;
    
        if (!regex_match(date, match, datePattern)) 
        {
            return false;
        }

        int year = stoi(match[1] .str());
        int month = stoi(match[2] .str());
        int day = stoi(match[3] .str());

        if (month < 1 || month > 12) 
        {
            return false;
        }

        vector <int>daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
        {
            daysInMonth[1] = 29;
        }

        if (day < 1 || day > daysInMonth[month - 1]) 
        {
            return false;
        }

        return true;
    }

public:
    void add_outgoing_goods();
    void view_outgoing_goods();
    void find_outgoing_goods();
    void update_outgoing_goods();
    void delete_outgoing_goods();
    void manage_outgoing_goods();
};

void outgoing_inventory_management::add_outgoing_goods()
{
   string goods_id, goods_name, goods_category, date, destination;
   char next;
   int stock_amount;

   do
   {
       clearScreen();
       bool is_duplicate;

       // Looping sampai pengguna memasukkan kode barang yang tidak duplikat
       do
       {
           is_duplicate = false;
           cout << "Masukkan ID Barang: ";
           cin >> goods_id;

           // Memeriksa apakah kode barang sudah ada
           for (const auto &goods : outgoing_goods_list)
           {
               if (goods.get_goods_code() == goods_id)
               {
                   is_duplicate = true;
                   cout << "\nKode barang sudah ada. Silakan masukkan kode barang yang berbeda." << endl;
                   break;
               }
           }
       } while (is_duplicate); // Ulangi jika duplikat

       cout << "Masukkan Nama Barang: ";
       cin.ignore();
       getline(cin, goods_name);
       cout << "Masukkan Kategori Barang: ";
       cin.ignore();
       getline(cin, goods_category);

       while (true)
       {
           cout << "Masukkan Jumlah Stok: ";
           cin >> stock_amount;

           if (cin.fail())
           {
               cin.clear(); // Menghapus flag kesalahan
               cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
               cout << "\nInput tidak valid. Silahkan masukkan angka." << endl;
           }
           else
           {
               break; // Input valid, keluar dari loop
           }
       }
       
       // Validais date input
       do
       {
           cout << "Masukkan Tanggal (YYYY-MM-DD): ";
           cin >> date;

           if (!isValidDate(date))
           {
               cout << "\nFormat tanggal tidak valid atau hari/bulan yang diinput di luar rentang. Silakan coba lagi.\n";
           }
       } while (!isValidDate(date));

       cout << "Masukkan Tujuan Pengiriman: ";
       cin.ignore();
       getline(cin, destination);

       outgoing_goods newGoods(goods_id, goods_name, goods_category, stock_amount, date, destination);
       outgoing_goods_list.push_back(newGoods);

       cout << "\nOutgoing goods added successfully!" << endl;
       cout << "Tekan 1 untuk menambahkan barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Pengeluaran Barang: ";
       cin >> next;
       cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
   } while (next == '1');
}

void outgoing_inventory_management::view_outgoing_goods()
{
   char next;
   do
   {
       if (outgoing_goods_list.empty())
       {
           cout << "Tidak ada barang dalam daftar." << endl;
       }
       else
       {
           cout << "=== Daftar Barang Pengeluaran ===\n";

           for (const auto &goods : outgoing_goods_list)
           {
               goods.display_goods();
           }
       }
       cout << "\nKetik bebas untuk balik ke Menu Manajemen Pengeluaran Barang.";
       cin >> next;

       while (getchar() != '\n');
   } while (next == '1');
}

void outgoing_inventory_management::find_outgoing_goods()
{
    string goods_id;
    char next;
    do
    {
        clearScreen();
        cout << "Masukkan ID Barang yang dicari: ";
        cin >> goods_id;
        cout << endl;

        bool found = false;
        for (const auto &goods : outgoing_goods_list)
        {
            if (goods .get_goods_code() == goods_id)
            {
                goods .display_goods();
                found = true;

                break;
            }
        }

        if (!found)
        {
            cout << "\nBarang tidak ditemukan." << endl;
        }
        cout << "\nTekan 1 untuk mencari barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Pemasukan Barang: ";
        cin >> next;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    } while (next == '1');
}

void outgoing_inventory_management::update_outgoing_goods()
{
   string goods_id;
   char next;
   do
   {
       clearScreen();
       cout << "Masukkan ID Barang yang Akan Diubah: ";
       cin >> goods_id;

       bool found = false;
       for (auto &goods : outgoing_goods_list)
       {
           if (goods.get_goods_code() == goods_id)
           {
               string goods_name, goods_category, date, destination;
               int stock_amount;

               cout << "\nMasukkan Nama Barang Baru: ";
               cin.ignore();
               getline(cin, goods_name);
               cout << "Masukkan Kategori Barang Baru: ";
               cin.ignore();
               getline(cin, goods_category);

               while (true)
               {
                   cout << "Masukkan Jumlah Stok Baru: ";
                   cin >> stock_amount;

                   if (cin.fail())
                   {
                       cin.clear(); // Menghapus flag kesalahan
                       cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
                       cout << "\nInput tidak valid. Silahkan masukkan angka." << endl;
                   }
                   else
                   {
                       break; // Input valid, keluar dari loop
                   }
               }

               do
               {
                   cout << "Masukkan Tanggal Baru (YYYY-MM-DD): ";
                   cin >> date;

                   if (!isValidDate(date))
                   {
                       cout << "\nFormat tanggal tidak valid atau hari/bulan yang diinput di luar rentang. Silakan coba lagi." << endl;
                   }
               } while (!isValidDate(date));

               cout << "Masukkan Tujuan Pengiriman Baru: ";
               cin.ignore();
               getline(cin, destination);

               goods.set_goods_name(goods_name);
               goods.set_goods_category(goods_category);
               goods.set_stock_amount(stock_amount);
               goods.set_data(date);
               goods.set_destination(destination);

               cout << "Outgoing goods updated successfully!" << endl;
               found = true;
               break;
           }
       }

       if (!found)
       {
           cout << "Barang tidak ditemukan." << endl;
       }

       cout << "\nTekan 1 untuk mengubah barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Pengeluaran Barang: ";
       cin >> next;
       cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
   } while (next == '1');
}

void outgoing_inventory_management::delete_outgoing_goods()
{
   string goods_id;
   char next;

   do
   {
       clearScreen();
       cout << "Masukkan ID Barang yang Akan Dihapus: ";
       cin >> goods_id;

       bool found = false;
       for (auto it = outgoing_goods_list.begin(); it != outgoing_goods_list.end(); ++it)
       {
           if (it->get_goods_code() == goods_id)
           {
               outgoing_goods_list.erase(it);
               cout << "Barang berhasil dihapus!" << endl;
               found = true;
               break;
           }
       }

       if (!found)
       {
           cout << "Barang tidak ditemukan." << endl;
       }

       cout << "\nTekan 1 untuk menghapus barang lagi, atau tekan karakter lain untuk kembali ke Menu Manajemen Pengeluaran Barang: ";
       cin >> next;
       cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
   } while (next == '1');
}

void outgoing_inventory_management::manage_outgoing_goods()
{
   clearScreen();
   int choices;
   do
   {
       clearScreen();
       cout << "\n===============================================" << endl;
       cout << "        MENU MANAJEMEN PENGELUARAN BARANG" << endl;
       cout << "===============================================" << endl;
       cout << "1. Tambah Data Pengeluaran Barang Baru" << endl;
       cout << "2. Tampilkan Semua Data Pengeluaran Barang" << endl;
       cout << "3. Cari Data Pengeluaran Barang" << endl;
       cout << "4. Ubah Data Pengeluaran Barang" << endl;
       cout << "5. Hapus Data Pengeluaran Barang" << endl;
       cout << "6. Kembali ke Menu Utama" << endl;
       cout << "Pilih opsi: ";
       cin >> choices;

       switch (choices)
       {
       case 1:
           clearScreen();
           add_outgoing_goods();
           break;
       case 2:
           clearScreen();
           view_outgoing_goods();
           break;
       case 3:
           clearScreen();
           find_outgoing_goods();
           break;
       case 4:
           clearScreen();
           update_outgoing_goods();
           break;
       case 5:
           clearScreen();
           delete_outgoing_goods();
           break;
       case 6:
           clearScreen();
           break;
       default:
           cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
       }
   } while (choices != 6);
}

void report();

void main_menu() 
{
    inventory_management inventory_management;
    outgoing_inventory_management outgoing_inventory_management;
    int choices;
    do {
        cout << "\n===============================================" << endl;
        cout << "                  MENU UTAMA" << endl;
        cout << "===============================================" << endl;
        cout << "1. Menu Manajemen Pemasukan Barang" << endl;
        cout << "2. Menu Manajemen Pengeluaran Barang" << endl;
        cout << "3. Laporan" << endl;
        cout << "4. Keluar dari Program" << endl;
        cout << "Pilih opsi: ";
        cin >> choices;

        switch (choices) 
        {
            case 1:
                inventory_management.manage_incoming_goods();
                break;
            case 2:
                outgoing_inventory_management.manage_outgoing_goods();
                break;
            case 3:
                clearScreen();
                // report();
                break;
            case 4:
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } 
    
    while (choices != 4);
}

int main() {
    main_menu();

    return 0;
}
