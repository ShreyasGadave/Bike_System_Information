# Bike_System_Information
Mini Project
Mini Project
Program Overview
User Account Management:

Create New Account: Users can create an account by entering their name, email, mobile number, address, and password. The system validates the email format, mobile number format, and password strength. The user data is saved to a text file.
Login: Users can log in using their registered email or mobile number and password. Upon successful login, users can access the bike information system.
Bike Information System:

Company Menu: After logging in, users can browse through different categories of bikes:
Sports Bikes: Displays detailed information on models like Aprilia RSV4 RR, Triumph Street Triple RS, Kawasaki Ninja ZX-10R, and Ducati Panigale V4.
Off-Roading Bikes: Provides details on models like Santa Cruz Nomad, Yeti SB150, and Trek Slash.
Scooter Bikes: Lists models such as Honda PCX150, Yamaha NMAX 155, Vespa GTS Super 300, and BMW C 400 X.
Cruiser Bikes: (The information for this section appears to be cut off but is likely similar to the other categories).
Electric Bikes (EV Bikes): Not detailed in the provided code but presumably similar to the other bike categories.
Navigation: Users can navigate through the different bike categories, return to the main menu, or exit the program.
Utility Functions:

Password Validation: Ensures that passwords contain at least one letter, one digit, and one symbol, and are at least six characters long.
Email Validation: Uses a regular expression to validate the format of the email address.
Mobile Number Validation: Ensures that the mobile number contains the correct number of digits.
Exit Program:

Users can choose to exit the program, which will display a goodbye message and terminate the application after a brief delay.
Key Features
User Input Validation: The program includes basic input validation for email, mobile numbers, and passwords.
Modular Design: The program is divided into functions for account creation, login, and displaying bike information, making it easy to manage and extend.
Interactive Menu System: Users are guided through a menu system to create accounts, log in, and browse bike information.
Potential Improvements
Error Handling: Enhance error handling, especially for file operations (e.g., when saving user data).
User Feedback: Provide more detailed feedback to the user for actions like account creation and login failures.
Additional Features: Consider adding more bike categories or models, or providing the ability for users to save favorite bikes.
The program is a good starting point for a more extensive system and demonstrates basic user management and interaction within a C-based console application.
