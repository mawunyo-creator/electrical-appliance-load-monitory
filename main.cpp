#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Device {
    string label;
    double watts{};
    double hours{};
};

static const string APPLIANCE_DB = "appliances.txt";
static const string BILL_FILE    = "billing_summary.txt";

static void flushInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static double readDouble(const string& prompt, double minVal, double maxVal) {
    double x;
    while (true) {
        cout << prompt;
        cin >> x;

        if (!cin.fail() && x >= minVal && x <= maxVal) return x;

        cout << "Invalid input. Enter a value between " << minVal << " and " << maxVal << ".\n";
        flushInput();
    }
}

static string readLineNonEmpty(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);

        // trim spaces (simple)
        s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char c){ return !isspace(c); }));
        s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char c){ return !isspace(c); }).base(), s.end());

        if (!s.empty()) return s;
        cout << "Input cannot be empty.\n";
    }
}

static double kwhPerDay(const Device& d) {
    return (d.watts * d.hours) / 1000.0;
}

static void saveDB(const vector<Device>& devices) {
    ofstream out(APPLIANCE_DB);
    if (!out) {
        cout << "Error: could not save to " << APPLIANCE_DB << "\n";
        return;
    }

    // Format: label|watts|hours
    for (const auto& d : devices) {
        out << d.label << "|" << d.watts << "|" << d.hours << "\n";
    }
}

static vector<Device> loadDB() {
    vector<Device> devices;
    ifstream in(APPLIANCE_DB);
    if (!in) return devices;

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string label, wStr, hStr;

        if (!getline(ss, label, '|')) continue;
        if (!getline(ss, wStr, '|')) continue;
        if (!getline(ss, hStr, '|')) continue;

        try {
            Device d;
            d.label = label;
            d.watts = stod(wStr);
            d.hours = stod(hStr);

            if (d.label.empty()) continue;
            if (d.watts <= 0) continue;
            if (d.hours < 0 || d.hours > 24) continue;

            devices.push_back(d);
        } catch (...) {
            continue;
        }
    }
    return devices;
}

static void listDevices(const vector<Device>& devices) {
    if (devices.empty()) {
        cout << "No appliances found.\n";
        return;
    }

    cout << "\n------------------- APPLIANCES -------------------\n";
    cout << left
         << setw(4)  << "#"
         << setw(20) << "Name"
         << setw(10) << "Watts"
         << setw(10) << "Hours"
         << setw(12) << "kWh/day"
         << "\n--------------------------------------------------\n";

    for (size_t i = 0; i < devices.size(); i++) {
        cout << left
             << setw(4)  << (i + 1)
             << setw(20) << devices[i].label
             << setw(10) << fixed << setprecision(2) << devices[i].watts
             << setw(10) << fixed << setprecision(2) << devices[i].hours
             << setw(12) << fixed << setprecision(3) << kwhPerDay(devices[i])
             << "\n";
    }
    cout << "--------------------------------------------------\n";
}

static void energyTotals(const vector<Device>& devices) {
    if (devices.empty()) {
        cout << "No appliances found.\n";
        return;
    }

    double total = 0.0;
    for (const auto& d : devices) total += kwhPerDay(d);

    cout << "\nTotal Daily Energy: " << fixed << setprecision(3) << total << " kWh/day\n";
}

static void generateBill(const vector<Device>& devices) {
    if (devices.empty()) {
        cout << "No appliances found.\n";
        return;
    }

    double tariff = readDouble("Enter tariff (per kWh): ", 0.0001, 1000000);

    // Console report + file report
    ofstream out(BILL_FILE);
    if (!out) {
        cout << "Error: could not write to " << BILL_FILE << "\n";
    }

    cout << "\n==================== BILLING REPORT ====================\n";
    cout << left
         << setw(4)  << "#"
         << setw(20) << "Name"
         << setw(12) << "kWh/day"
         << setw(12) << "Cost/day"
         << "\n--------------------------------------------------------\n";

    if (out) {
        out << "==================== BILLING REPORT ====================\n";
        out << left
            << setw(4)  << "#"
            << setw(20) << "Name"
            << setw(12) << "kWh/day"
            << setw(12) << "Cost/day"
            << "\n--------------------------------------------------------\n";
    }

    double totalKwhDay = 0.0, totalCostDay = 0.0;

    for (size_t i = 0; i < devices.size(); i++) {
        double kwh = kwhPerDay(devices[i]);
        double cost = kwh * tariff;

        totalKwhDay += kwh;
        totalCostDay += cost;

        cout << left
             << setw(4)  << (i + 1)
             << setw(20) << devices[i].label
             << setw(12) << fixed << setprecision(3) << kwh
             << setw(12) << fixed << setprecision(2) << cost
             << "\n";

        if (out) {
            out << left
                << setw(4)  << (i + 1)
                << setw(20) << devices[i].label
                << setw(12) << fixed << setprecision(3) << kwh
                << setw(12) << fixed << setprecision(2) << cost
                << "\n";
        }
    }

    double monthKwh  = totalKwhDay * 30;
    double monthCost = totalCostDay * 30;

    cout << "--------------------------------------------------------\n";
    cout << "Tariff: " << fixed << setprecision(2) << tariff << " per kWh\n";
    cout << "Total Energy (per day): " << fixed << setprecision(3) << totalKwhDay << " kWh/day\n";
    cout << "Total Cost (per day):   " << fixed << setprecision(2) << totalCostDay << "\n";
    cout << "Monthly Energy (30d):   " << fixed << setprecision(3) << monthKwh << " kWh\n";
    cout << "Monthly Cost (30d):     " << fixed << setprecision(2) << monthCost << "\n";
    cout << "========================================================\n";

    if (out) {
        out << "--------------------------------------------------------\n";
        out << "Tariff: " << fixed << setprecision(2) << tariff << " per kWh\n";
        out << "Total Energy (per day): " << fixed << setprecision(3) << totalKwhDay << " kWh/day\n";
        out << "Total Cost (per day):   " << fixed << setprecision(2) << totalCostDay << "\n";
        out << "Monthly Energy (30d):   " << fixed << setprecision(3) << monthKwh << " kWh\n";
        out << "Monthly Cost (30d):     " << fixed << setprecision(2) << monthCost << "\n";
        out << "========================================================\n";
        out.close();
        cout << "Billing report saved to " << BILL_FILE << "\n";
    }
}

static int showMenu() {
    cout << "\n==============================\n";
    cout << " Electrical Appliance Load Monitor\n";
    cout << "==============================\n";
    cout << "1. Add appliance\n";
    cout << "2. List appliances\n";
    cout << "3. Total energy (kWh/day)\n";
    cout << "4. Generate billing report\n";
    cout << "0. Exit\n";
    cout << "Choose: ";

    int ch;
    cin >> ch;
    if (cin.fail()) {
        flushInput();
        return -1;
    }
    return ch;
}

int main() {
    vector<Device> devices = loadDB();

    while (true) {
        int ch = showMenu();

        if (ch == 1) {
            flushInput(); // clear newline
            Device d;
            d.label = readLineNonEmpty("Appliance name: ");
            d.watts = readDouble("Power (Watts): ", 0.0001, 1e9);
            d.hours = readDouble("Hours per day (0 - 24): ", 0.0, 24.0);

            devices.push_back(d);
            saveDB(devices);
            cout << "Saved!\n";
        }
        else if (ch == 2) {
            listDevices(devices);
        }
        else if (ch == 3) {
            energyTotals(devices);
        }
        else if (ch == 4) {
            generateBill(devices);
        }
        else if (ch == 0) {
            saveDB(devices);
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}