# Electrical Appliance Load Monitoring

## Project Overview
This C++ console application allows users to register electrical appliances, calculate daily energy consumption, and display energy summaries.  

The program demonstrates structured programming, modular design, and energy computation using real-world electrical formulas.

---

## Features Implemented

### 1. Appliance Registration
Users can enter:
- Appliance name
- Power rating (Watts)
- Usage hours per day

Input validation ensures:
- Name is not empty
- Power rating is positive
- Usage hours are between 0 and 24

---

### 2. View Appliances
Displays all registered appliances in a formatted table including:
- Appliance name
- Power rating
- Daily usage hours

---

### 3. Energy Summary (kWh/day)
The program calculates energy consumption using:


Energy (kWh/day) = (Power × Hours) / 1000


It displays:
- Individual appliance energy consumption
- Total daily energy consumption

---

## Concepts Applied

- `struct` for appliance data modeling
- `vector` for dynamic data storage
- Member functions inside struct
- Formatted output using `iomanip`
- Input validation using `cin.fail()`
- Modular programming with functions

---

## How to Compile and Run

Compile:

g++ main.cpp -o main


Run:

./main

(On Windows: `main.exe`)

---

## Author
Abiwu Francis