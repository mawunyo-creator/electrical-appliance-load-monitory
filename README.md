# Electrical Appliance Load Monitoring

## Overview
This project is a C++ console application that helps users register electrical appliances and view their power usage details.  
It is designed to demonstrate the use of structs, vectors, basic input validation, and modular programming.

## Features (Week 1)
- Register an appliance (name, power rating in watts, and usage hours per day)
- View all registered appliances in a formatted table
- Basic input validation to prevent invalid entries

## Technologies / Concepts Used
- C++ Standard Library
- `struct` for storing appliance data
- `vector` to store multiple appliances dynamically
- Functions for modular programming
- Input validation using `cin.fail()` and `limits`

## How to Run
1. Compile the program:
   ```bash
   g++ main.cpp -o main