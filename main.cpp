#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

struct Appliance {
    string name;
    double powerW;
    double hoursPerDay;

    double energyKWhPerDay() const {
        return (powerW * hoursPerDay) / 1000.0;
    }
};

const string FILE_NAME = "appliances.txt";

static void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---------- FILE FUNCTIONS ----------
void saveAppliances(const vector<Appliance>& appliances) {
    ofstream out(FILE_NAME);

    for (const auto& a : appliances) {
        out << a.name << "|"
            << a.powerW << "|"
            << a.hoursPerDay << "\n";
    }
}

vector<Appliance> loadAppliances() {
    vector<Appliance> appliances;
    ifstream in(FILE_NAME);

    if (!in) return appliances;

    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string name, powerStr, hoursStr;

        if (!getline(ss, name, '|')) continue;
        if (!getline(ss, powerStr, '|')) continue;
        if (!getline(ss, hoursStr, '|')) continue;

        Appliance a;
        a.name = name;
        a.powerW = stod(powerStr);
        a.hoursPerDay = stod(hoursStr);

        appliances.push_back(a);
    }

    return appliances;
}

// ---------- MENU ----------
int menu() {
    cout << "\n==============================\n";
    cout << " Electrical Appliance Load Monitoring\n";
    cout << "==============================\n";
    cout << "1. Register appliance\n";
    cout << "2. View all appliances\n";
    cout << "3. Energy summary (kWh/day)\n";
    cout << "0. Exit\n";
    cout << "Choose: ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
        clearBadInput();
        return -1;
    }
    return choice;
}

// ---------- FEATURES ----------
Appliance registerAppliance() {
    Appliance a{};

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Enter appliance name: ";
        getline(cin, a.name);
    } while (a.name.empty());

    while (true) {
        cout << "Enter power rating (W): ";
        cin >> a.powerW;
        if (!cin.fail() && a.powerW > 0) break;
        clearBadInput();
    }

    while (true) {
        cout << "Enter usage hours per day (0 - 24): ";
        cin >> a.hoursPerDay;
        if (!cin.fail() && a.hoursPerDay >= 0 && a.hoursPerDay <= 24) break;
        clearBadInput();
    }

    return a;
}

void viewAllAppliances(const vector<Appliance>& appliances) {
    if (appliances.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << "\nAppliances:\n";
    for (size_t i = 0; i < appliances.size(); i++) {
        cout << i + 1 << ". "
             << appliances[i].name
             << " (" << appliances[i].powerW
             << "W, " << appliances[i].hoursPerDay
             << "h/day)\n";
    }
}

void showEnergySummary(const vector<Appliance>& appliances) {
    if (appliances.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    double total = 0;

    cout << "\nEnergy Summary:\n";

    for (const auto& a : appliances) {
        double kwh = a.energyKWhPerDay();
        total += kwh;

        cout << a.name
             << " -> " << fixed << setprecision(3)
             << kwh << " kWh/day\n";
    }

    cout << "Total Energy: "
         << fixed << setprecision(3)
         << total << " kWh/day\n";
}

// ---------- MAIN ----------
int main() {
    vector<Appliance> appliances = loadAppliances();

    while (true) {
        int choice = menu();

        switch (choice) {
            case 1: {
                Appliance a = registerAppliance();
                appliances.push_back(a);
                saveAppliances(appliances);
                break;
            }
            case 2:
                viewAllAppliances(appliances);
                break;
            case 3:
                showEnergySummary(appliances);
                break;
            case 0:
                saveAppliances(appliances);
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}