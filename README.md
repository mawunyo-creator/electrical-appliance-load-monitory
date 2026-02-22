# Electrical Appliance Load Monitoring

## Project Overview

The Electrical Appliance Load Monitoring system is a C++ console-based application developed to monitor electrical appliance usage, calculate daily energy consumption, and generate electricity billing reports.

The program allows users to register appliances, store appliance data persistently using text files, compute daily energy usage, and generate billing reports based on a user-defined electricity tariff.

This project demonstrates structured programming, file handling, input validation, and modular design in C++.

---

## Features

### 1. Appliance Registration
Users can register appliances by entering:
- Appliance name
- Power rating (Watts)
- Usage hours per day

Input validation ensures:
- Appliance name is not empty
- Power rating is positive
- Usage hours are between 0 and 24

---

### 2. View Appliances
Displays all registered appliances in a formatted table including:
- Appliance name
- Power rating
- Usage hours per day
- Daily energy consumption (kWh/day)

---

### 3. Energy Calculation

Daily energy consumption is calculated using:

Energy (kWh/day) = (Power × Hours) / 1000

The system calculates:
- Individual appliance daily energy
- Total daily energy consumption

---

### 4. Persistent Data Storage

Appliance records are saved automatically to:

appliances.txt

When the program starts, previously saved appliance data is loaded automatically.

Data format used:

Name|Watts|Hours

Example:

Fan|50|5  
TV|25|6  
Radio|15|3  

---

### 5. Billing Report Generation

The user enters an electricity tariff (cost per kWh).

The system calculates:

- Individual appliance daily energy
- Individual appliance daily cost
- Total daily energy consumption
- Total daily cost
- Monthly energy (30 days)
- Monthly cost (30 days)

The billing report is displayed on the console and automatically saved to:

billing_summary.txt

---

## Concepts Applied

- Structs for modeling appliance data
- Vectors for dynamic storage
- Modular programming using separate functions
- File handling using `<fstream>`
- File parsing using `<sstream>`
- Input validation using `cin.fail()`
- Formatted output using `<iomanip>`
- Basic string manipulation and trimming

---

## Project Structure

Electrical-Appliance-Load-Monitoring/  
│  
├── main.cpp  
├── appliances.txt  
├── billing_summary.txt  
├── README.md  
└── .gitignore  

---

## How to Compile and Run

Compile:

g++ main.cpp -o main

Run:

./main

(On Windows, run `main.exe`)

---

## Conclusion

This project simulates a real-world electrical energy monitoring and billing system. It demonstrates the practical application of C++ programming concepts including data structures, file persistence, modular design, and cost calculation based on energy consumption.

---

## Author

Abiwu Francis