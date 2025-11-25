#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

struct Room {
    int id;
    bool occupied;
    string customerName;
    int nights;
    double ratePerNight;
};

struct MenuItem {
    int id;
    string name;
    double price;
    int stock;
};

class HotelManager {
private:
    vector<Room> rooms;
    vector<MenuItem> menu;
    double dailyCollection = 0.0;
    string roomsFile = "rooms.dat";
    string menuFile = "menu.dat";
    string salesFile = "sales.dat";

public:
    HotelManager() {
        initDefaultRooms();
        initDefaultMenu();
        loadState();
    }

    ~HotelManager() {
        saveState();
    }

    void initDefaultRooms() {
        if(!rooms.empty()) return;
        for (int i = 1; i <= 10; ++i) {
            Room r;
            r.id = i;
            r.occupied = false;
            r.customerName = "";
            r.nights = 0;
            r.ratePerNight = 100 + (i - 1) * 20;
            rooms.push_back(r);
        }
    }

    void initDefaultMenu() {
        if(!menu.empty()) return;
        menu.push_back({1, "Burger", 80.0, 30});
        menu.push_back({2, "Pasta", 120.0, 20});
        menu.push_back({3, "Coffee", 40.0, 50});
        menu.push_back({4, "Sandwich", 60.0, 25});
        menu.push_back({5, "Salad", 70.0, 15});
    }

    void saveState() {
        ofstream ofsR(roomsFile);
        if (ofsR) {
            for (auto &r : rooms) {
                ofsR << r.id << '|' << r.occupied << '|' << escape(r.customerName)
                     << '|' << r.nights << '|' << r.ratePerNight << '\n';
            }
            ofsR.close();
        }

        ofstream ofsM(menuFile);
        if (ofsM) {
            for (auto &m : menu) {
                ofsM << m.id << '|' << m.name << '|' << m.price << '|' << m.stock << '\n';
            }
            ofsM.close();
        }

        ofstream ofsS(salesFile, ios::app);
        if (ofsS) {
            ofsS << dailyCollection << '\n';
            ofsS.close();
        }
    }

    void loadState() {
        ifstream ifsR(roomsFile);
        if (ifsR) {
            rooms.clear();
            string line;
            while (getline(ifsR, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                Room r;
                string occupiedStr, nameEsc;

                getline(ss, line, '|'); r.id = stoi(line);
                getline(ss, occupiedStr, '|'); r.occupied = stoi(occupiedStr);
                getline(ss, nameEsc, '|'); r.customerName = unescape(nameEsc);
                getline(ss, line, '|'); r.nights = stoi(line);
                getline(ss, line); r.ratePerNight = stod(line);

                rooms.push_back(r);
            }
            ifsR.close();
        }

        ifstream ifsM(menuFile);
        if (ifsM) {
            menu.clear();
            string line;
            while (getline(ifsM, line)) {
                if (line.empty()) continue;

                stringstream ss(line);
                MenuItem m;
                string token;

                getline(ss, token, '|'); m.id = stoi(token);
                getline(ss, m.name, '|');
                getline(ss, token, '|'); m.price = stod(token);
                getline(ss, token); m.stock = stoi(token);

                menu.push_back(m);
            }
            ifsM.close();
        }
    }

    string escape(const string &s) {
        string out;
        for (char c : s) {
            if (c == '|') out += "\\|";
            else if (c == '\n') out += "\\n";
            else out += c;
        }
        return out;
    }

    string unescape(const string &s) {
        string out;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '\\' && i + 1 < s.size()) {
                if (s[i+1] == '|') { out += '|'; ++i; }
                else if (s[i+1] == 'n') { out += '\n'; ++i; }
                else out += s[i+1], ++i;
            } 
            else out += s[i];
        }
        return out;
    }

    /* -----------------------------------------------------------
       ROOM DISPLAY (With Simple Border)
    ------------------------------------------------------------*/
    void showRooms() {
        cout << "\n==================== ROOM STATUS ====================\n";

        cout << left << setw(6)  << "ID"
             << setw(12) << "Status"
             << setw(20) << "Customer"
             << setw(10) << "Nights"
             << setw(8)  << "Rate" << "\n";

        cout << "------------------------------------------------------\n";

        for (auto &r : rooms) {
            cout << left 
                << setw(6)  << r.id
                << setw(12) << (r.occupied ? "Occupied" : "Available")
                << setw(20) << (r.occupied ? r.customerName : "-")
                << setw(10) << (r.occupied ? to_string(r.nights) : "-")
                << setw(8)  << r.ratePerNight
                << "\n";
        }

        cout << "======================================================\n";
    }

    /* -----------------------------------------------------------
       MENU DISPLAY (With Simple Border)
    ------------------------------------------------------------*/
    void showMenu() {
        cout << "\n======================= FOOD MENU =====================\n";

        cout << left 
             << setw(6)  << "ID"
             << setw(18) << "Item"
             << setw(10) << "Price"
             << setw(8)  << "Stock" << "\n";

        cout << "-------------------------------------------------------\n";

        for (auto &m : menu) {
            cout << left
                 << setw(6)  << m.id
                 << setw(18) << m.name
                 << setw(10) << m.price
                 << setw(8)  << m.stock << "\n";
        }

        cout << "=======================================================\n";
    }

    bool allotRoom(int roomId, const string &custName, int nights) {
        for (auto &r : rooms) {
            if (r.id == roomId) {
                if (r.occupied) return false;

                r.occupied = true;
                r.customerName = custName;
                r.nights = nights;

                double bill = nights * r.ratePerNight;
                dailyCollection += bill;

                cout << "\n[✔] Room " << roomId << " allotted to " << custName 
                     << ". Room charge: " << bill << "\n";

                return true;
            }
        }
        return false;
    }

    bool releaseRoom(int roomId) {
        for (auto &r : rooms) {
            if (r.id == roomId) {
                if (!r.occupied) return false;

                r.occupied = false;
                r.customerName = "";
                r.nights = 0;

                cout << "\n[✔] Room " << roomId << " is now available.\n";
                return true;
            }
        }
        return false;
    }

    bool orderFood(int itemId, int quantity) {
        for (auto &m : menu) {
            if (m.id == itemId) {
                if (m.stock < quantity) {
                    cout << "\n[✖] Only " << m.stock << " left in stock.\n";
                    return false;
                }

                m.stock -= quantity;
                double bill = quantity * m.price;
                dailyCollection += bill;

                cout << "\n[✔] Ordered " << quantity << " x " << m.name
                     << ". Amount: " << bill << "\n";

                return true;
            }
        }
        return false;
    }

    void updateStock(int itemId, int added) {
        for (auto &m : menu) {
            if (m.id == itemId) {
                m.stock += added;

                cout << "\n[✔] Stock updated! New stock of " 
                     << m.name << " = " << m.stock << "\n";

                return;
            }
        }
        cout << "\n[✖] Menu item not found.\n";
    }

    void showSalesSummary() {
        cout << "\n==================== TODAY'S COLLECTION ====================\n";
        cout << "Total: " << dailyCollection << "\n";
        cout << "===========================================================\n";
    }
};


void showMainMenu() {
    cout << "\n================= HOTEL MANAGEMENT =================\n";
    cout << "1. Show rooms\n";
    cout << "2. Allot room\n";
    cout << "3. Release room\n";
    cout << "4. Show food menu\n";
    cout << "5. Order food\n";
    cout << "6. Update food stock (admin)\n";
    cout << "7. Show today's collection\n";
    cout << "8. Exit\n";
    cout << "=====================================================\n";
    cout << "Choose an option: ";
}

int main() {
    HotelManager hm;
    int choice;

    while (true) {
        showMainMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }

        if (choice == 1) hm.showRooms();
        else if (choice == 2) {
            int rid, nights;
            string name;

            cout << "Enter room id to allot: "; cin >> rid;
            cin.ignore();
            cout << "Enter customer name: "; getline(cin, name);
            cout << "Enter number of nights: "; cin >> nights;

            if (!hm.allotRoom(rid, name, nights))
                cout << "[✖] Failed to allot room.\n";

        } else if (choice == 3) {
            int rid;
            cout << "Enter room id to release: "; cin >> rid;

            if (!hm.releaseRoom(rid))
                cout << "[✖] Room already free or invalid ID.\n";

        } else if (choice == 4) hm.showMenu();

        else if (choice == 5) {
            int itemId, qty;
            cout << "Enter menu item id: "; cin >> itemId;
            cout << "Enter quantity: "; cin >> qty;
            hm.orderFood(itemId, qty);

        } else if (choice == 6) {
            int itemId, add;
            cout << "Enter menu item id: "; cin >> itemId;
            cout << "Add quantity: "; cin >> add;
            hm.updateStock(itemId, add);

        } else if (choice == 7) hm.showSalesSummary();

        else if (choice == 8) {
            cout << "Saving data & exiting...\n";
            break;
        }

        else cout << "Choose a valid option.\n";
    }

    return 0;
}
