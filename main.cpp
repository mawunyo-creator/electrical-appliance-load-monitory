#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

struct Appliance {
    string name;
    double powerW;      // watts
    double hoursPerDay; // 0 - 24

    double energyKWhPerDay() const {
        return (powerW * hoursPerDay) / 1000.0;
    }
};

static void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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

Appliance registerAppliance() {
    Appliance a{};

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Enter appliance name: ";
        getline(cin, a.name);
        if (a.name.empty()) cout << "Name must not be empty.\n";
    } while (a.name.empty());

    while (true) {
        cout << "Enter power rating (W): ";
        cin >> a.powerW;

        if (!cin.fail() && a.powerW > 0) break;

        cout << "Power must be a number greater than zero.\n";
        clearBadInput();
    }

    while (true) {
        cout << "Enter usage hours per day (0 - 24): ";
        cin >> a.hoursPerDay;

        if (!cin.fail() && a.hoursPerDay >= 0 && a.hoursPerDay <= 24) break;

        cout << "Hours must be between 0 and 24.\n";
        clearBadInput();
    }

    cout << "Appliance registered successfully!\n";
    return a;
}

void viewAllAppliances(const vector<Appliance>& appliances) {
    if (appliances.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << "\n================= APPLIANCES =================\n";
    cout << left
         << setw(5)  << "No."
         << setw(20) << "Name"
         << setw(12) << "Power(W)"
         << setw(12) << "Hours/day"
         << "\n----------------------------------------------\n";

    for (size_t i = 0; i < appliances.size(); i++) {
        const auto& a = appliances[i];
        cout << left
             << setw(5)  << (i + 1)
             << setw(20) << a.name
             << setw(12) << fixed << setprecision(2) << a.powerW
             << setw(12) << fixed << setprecision(2) << a.hoursPerDay
             << "\n";
    }
}

void showEnergySummary(const vector<Appliance>& appliances) {
    if (appliances.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << "\n=============== ENERGY SUMMARY (per day) ===============\n";
    cout << left
         << setw(20) << "Name"
         << setw(12) << "Power(W)"
         << setw(12) << "Hours"
         << setw(12) << "kWh/day"
         << "\n--------------------------------------------------------\n";

    double total = 0.0;

    for (const auto& a : appliances) {
        double kwh = a.energyKWhPerDay();
        total += kwh;

        cout << left
             << setw(20) << a.name
             << setw(12) << fixed << setprecision(2) << a.powerW
             << setw(12) << fixed << setprecision(2) << a.hoursPerDay
             << setw(12) << fixed << setprecision(3) << kwh
             << "\n";
    }

    cout << "--------------------------------------------------------\n";
    cout << "TOTAL ENERGY: " << fixed << setprecision(3)
         << total << " kWh/day\n";
    cout << "========================================================\n";
}

int main() {
    vector<Appliance> appliances;

    while (true) {
        int choice = menu();

        switch (choice) {
            case 1: {
                Appliance a = registerAppliance();
                appliances.push_back(a);
                break;
            }
            case 2:
                viewAllAppliances(appliances);
                break;

            case 3:
                showEnergySummary(appliances);
                break;

            case 0:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}