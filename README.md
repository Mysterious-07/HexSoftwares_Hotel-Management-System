🏨 Hotel Management System in C++

A beginner–friendly console-based C++ project
#Hex #HexSoftware

📌 Project Overview

This Hotel Management System is a simple and interactive console-based project built using Object-Oriented Programming (OOP) in C++.

It manages:
✔ Room allotment
✔ Food ordering
✔ Stock / menu management
✔ Daily sales tracking
✔ File-based data storage

This project is perfect for beginners learning C++, classes, file handling, and basic application development.

🧰 Features
🛏 Room Management

Display all rooms

Allot room to customer

Release room after checkout

Auto-calculate room charges

🍔 Food Ordering System

Display food menu

Order food items

Deduct stock automatically

Add to daily sales

📦 Stock / Menu Management (Admin)

Update food stock

Add new menu items

💰 Sales & Reporting

Calculate total sales for the day

Save all records automatically

💾 Data Persistence

Data is saved and loaded through:

rooms.dat

menu.dat

sales.dat

🖥 Output Preview

(You can replace these with real screenshots later from your system.)

--- Hotel Management ---
1. Show rooms
2. Allot room
3. Release room
4. Show food menu
5. Order food
6. Update food stock
7. Show today's collection
8. Exit

🛠 Technologies Used

C++ (Classes, OOP)

File Handling (fstream)

Vectors (std::vector)

Basic Console UI

📦 How to Run the Program
1️⃣ Clone the repository:
git clone https://github.com/your-username/Hotel-Management-System-Cpp.git

2️⃣ Compile the source file:
g++ -std=c++17 hotel.cpp -o hotel

3️⃣ Run the application:
./hotel

🔍 Explanation of the Project

This system simulates a hotel’s basic operations:

✔ Room allotment:

The user assigns a customer to a room, enters nights, and the program calculates room charges.

✔ Food ordering:

Customer orders food; stock decreases, sales increase.

✔ Stock management:

Admin can increase food stock anytime.

✔ Sales tracking:

Every room allotment and food order adds to the dailyCollection, which can be viewed anytime.

✔ File handling:

All data persists after program exit:

Room status

Menu stock

Daily sales

📁 File Structure
Hotel-Management-System/
│
├── hotel.cpp
├── rooms.dat
├── menu.dat
├── sales.dat
└── README.md

🚀 Future Enhancements

Add login system (Admin/User)

Add detailed bill printing

Add date-wise sales reports

JSON or SQLite storage

GUI using Qt / SFML / Web UI

🏢 Developed For

Hex Software — Task-1 Project
#Hex #HexSoftware

🤝 Contributing

Pull requests are welcome!
Feel free to open issues for improvements or bugs.

📜 License

This project is open-source and available under the MIT License.
