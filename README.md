Electrical Appliance Load Monitoring System
Author

Abiwu Francis
Email: theablemawunyo@gmail.com

Project Description

The Electrical Appliance Load Monitoring System is a C++ console-based program designed to monitor household electrical appliance energy consumption and calculate electricity billing.

This system allows users to register appliances, calculate daily energy usage in kilowatt-hours (kWh), and generate both daily and monthly billing reports based on a specified electricity tariff.

The project demonstrates the use of structured programming, file handling, input validation, and basic data persistence in C++.

Features

Register new appliances

Store appliance data in a file (appliances.txt)

View all registered appliances

Calculate total daily energy consumption

Generate billing report

Save billing report to file (billing_summary.txt)

Monthly cost calculation (30-day estimate)

Input validation for accurate data entry

Technologies Used

C++

Standard Template Library (STL)

File handling using fstream

Vectors for dynamic data storage

Structured programming with functions

Git & GitHub for version control

File Structure
.gitignore
README.md
main.cpp
appliances.txt
billing_summary.txt
How It Works

User registers appliances by entering:

Appliance name

Power rating (Watts)

Usage hours per day

The system calculates:

Daily energy usage:

Energy (kWh/day) = (Power × Hours) ÷ 1000

Daily cost:

Daily Cost = Energy × Tariff

Monthly estimate (30 days):

Monthly Cost = Daily Cost × 30

Billing results are:

Displayed on screen

Saved to billing_summary.txt

Sample Demo Data
appliances.txt
Fan|50|4
TV|80|2
billing_summary.txt
Total Energy (per day): 0.360 kWh/day
Total Cost (per day): 8.28
Monthly Energy (30d): 10.800 kWh
Monthly Cost (30d): 248.40
Learning Outcomes

This project demonstrates understanding of:

Structs in C++

Vectors for dynamic storage

File handling (read/write)

String manipulation

Input validation

Modular programming

Basic billing automation logic

Version control using Git

Conclusion

The Electrical Appliance Load Monitoring System provides a simple but effective solution for estimating household energy usage and electricity cost. It reinforces core C++ programming principles and practical software development practices.