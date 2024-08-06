// done
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <regex.h>

// Define the Function
#define MAX_USERS 99
#define PASSWORD_LENGTH 20
#define MOBILE_NUMBER_LENGTH 11
#define ADDRESS_LENGTH 100
#define NAME_LENGTH 50
#define EMAIL_LENGTH 50
#define ANSI_COLOR_CYAN "\033[0;36m"
#define ANSI_COLOR_LIGHTGREEN "\033[0;32m"
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_COLOR_YELLOW "\033[0;33m"
#define ANSI_COLOR_CAYN "\033[0;36m"
#define ANSI_COLOR_RED "\033[0;31m"
#define EMAIL_REGEX "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"

// Element that can Contain
typedef struct
{
    char name[NAME_LENGTH];
    char email[EMAIL_LENGTH];
    char mobile_number[MOBILE_NUMBER_LENGTH];
    char address[ADDRESS_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

// Function List
void create_new_account(User users[], int *num_users);
int is_valid_mobile_number(const char *number);
bool is_strong_password(const char *password);
bool is_valid_email(const char *email);
void login(User users[], int num_users);
void Sports_Bike();
void OffRoading_Bike();
void Scooter_bike();
void Cruiser_Bike();
void Ev_Bike();
void company();
void Time();

// Main Content
int main()
{
    User users[MAX_USERS];
    int num_users = 0;
    clock_t start = clock();
    clock_t end;
    int choice;

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    while (1)
    {
        printf(ANSI_COLOR_YELLOW "\nWelcome to the Bike System!\n\n");
        printf(ANSI_COLOR_CYAN "1. Create new account\n");
        printf("2. Login\n");
        printf("3. New Page\n");
        printf("4. Exit\n");

        printf(ANSI_COLOR_RESET "\nEnter your choice : " ANSI_COLOR_LIGHTGREEN);

        // Use a loop to handle invalid input
        while (scanf("%d", &choice) != 1)
        {
            printf(ANSI_COLOR_RED "Invalid input. Please enter a number between 1 and 4.\n" ANSI_COLOR_RESET);
            while (getchar() != '\n')
                ; // Clear the input buffer
        }

        switch (choice)
        {
        case 1:
            create_new_account(users, &num_users);
            break;
        case 2:
            login(users, num_users);
            break;
        case 3:
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            break;
        case 4:
            printf(ANSI_COLOR_RED "Exiting the Program. Goodbye ! ");
            do
            {
                end = clock();
            } while ((end - start) / CLOCKS_PER_SEC < 3);
            exit(0);
        default:
            printf(ANSI_COLOR_RED "Invalid choice. Please enter 1, 2, or 3.\n" ANSI_COLOR_RESET);
            break;
        }
    }

    return 0;
}

// New Account Creating
void create_new_account(User users[], int *num_users)
{
    if (*num_users >= MAX_USERS)
    {
        printf(ANSI_COLOR_RED "Maximum number of users reached. Cannot create new account.\n" ANSI_COLOR_RESET);
        return;
    }

    User new_user;

    long long mobile_number;
    int digits;
    char choice;
    scanf("%*c");

    printf(ANSI_COLOR_RESET "\nEnter Name : " ANSI_COLOR_LIGHTGREEN);
    scanf("%[^\n]", new_user.name);

    printf(ANSI_COLOR_RESET "Enter Email: " ANSI_COLOR_LIGHTGREEN);
    scanf("%s", new_user.email);
    while (!is_valid_email(new_user.email))
    {
        printf(ANSI_COLOR_RED "Invalid Email Format.");
        printf(ANSI_COLOR_RESET "\nPlease Enter a Valid Email: " ANSI_COLOR_LIGHTGREEN);
        scanf("%s", new_user.email);
    }

    printf(ANSI_COLOR_RESET "Enter mobile number : " ANSI_COLOR_LIGHTGREEN);
    scanf("%s", new_user.mobile_number);
    while (!is_valid_mobile_number(new_user.mobile_number))
    {
        printf(ANSI_COLOR_RED "Invalid mobile number format.");
        printf(ANSI_COLOR_RESET "\nPlease enter a valid number: " ANSI_COLOR_LIGHTGREEN);
        scanf("%s", new_user.mobile_number);
    }

    printf(ANSI_COLOR_RESET "Enter your Address: " ANSI_COLOR_LIGHTGREEN);
    scanf(" %[^\n]", new_user.address);

    while (1)
    {
        // Input password from the user
        printf(ANSI_COLOR_RESET "Create Password: " ANSI_COLOR_LIGHTGREEN);
        scanf("%s", new_user.password);

        // Check if the password is strong
        if (is_strong_password(new_user.password))
        {
           
            break;
        }
        else
        {
            printf(ANSI_COLOR_RED "Password is not Strong enough.\n");
        }
    }

    users[*num_users] = new_user;
    (*num_users)++;

    printf("\nNew Account Created Successfully.\n");
    // Save the new user to a text file
    FILE *file = fopen("Bike_System_Information_Data.txt", "a");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    fprintf(file, "USER DATA : \n Username : %s\n Mobile : %10s\n Address : %s\n Email : %s\n Password : %s\n\n", new_user.name, new_user.mobile_number, new_user.address, new_user.email, new_user.password);
    fclose(file);
}

// Function to validate password format
bool is_strong_password(const char *password)
{
    // Check if password length is at least 6 characters
    if (strlen(password) < 6)
        return false;

    bool has_letter = false, has_digit = false, has_symbol = false;
    // Check each character in the password
    for (int i = 0; password[i] != '\0'; i++)
    {
        // Check if the character is a letter
        if (isalpha(password[i]))
            has_letter = true;
        // Check if the character is a digit
        else if (isdigit(password[i]))
            has_digit = true;
        // Check if the character is a symbol
        else if (!isalnum(password[i]))
            has_symbol = true;
    }

    // Check if the password contains at least one letter, one digit, and one symbol
    return has_letter && has_digit && has_symbol;
}

// Function to validate email format
bool is_valid_email(const char *email)
{
    regex_t regex;
    int reti;

    reti = regcomp(&regex, EMAIL_REGEX, REG_EXTENDED);
    if (reti)
    {
        return false;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return !reti;
}

// Function to validate mobile number format
int is_valid_mobile_number(const char *number)
{
    // Simple validation, checking for presence of digits and correct length
    return strspn(number, "0123456789") == MOBILE_NUMBER_LENGTH - 1;
}

// Login the User
void login(User users[], int num_users)
{
    char emailornumber[50];
    char password[PASSWORD_LENGTH];

    printf(ANSI_COLOR_RESET "\nEnter your Email or Number : " ANSI_COLOR_LIGHTGREEN);
    scanf("%s", emailornumber); // No input validation for email format in this example

    printf(ANSI_COLOR_RESET "Enter your Password: " ANSI_COLOR_LIGHTGREEN);
    scanf("%s", password);

    for (int i = 0; i < num_users; i++)
    {
        if (strcmp(users[i].email, emailornumber) == 0 || strcmp(users[i].mobile_number, emailornumber) == 0 && strcmp(users[i].password, password) == 0)
        {
            printf("\nLogin Successful!\n");
            company();
        }
    }

    printf(ANSI_COLOR_RED "Invalid email or password. Please try again.\n" ANSI_COLOR_RESET);
}

// Company Bike Content
void company()
{
    printf(ANSI_COLOR_YELLOW "\nWelcome To Bike Information System .\n");
    int i = 0;
    clock_t start = clock();
    clock_t end;

    while (true)
    {
        printf(ANSI_COLOR_CYAN "\n1. Off Roading Bike \n2. Ev Bike \n3. Sport's Bike \n4. Cruiser Bike \n5. Scooter Bike \n6. New Page \n7. Exit the Program \n8. Back to Main Menu ");
        printf(ANSI_COLOR_RESET "\n\nEnter the Company : " ANSI_COLOR_LIGHTGREEN);
        int company;

        scanf("%d", &company);
        if (company == 8)
            break;
        switch (company)
        {
        case 1:
            OffRoading_Bike();
            break;

        case 2:
            Ev_Bike();
            break;

        case 3:
            Sports_Bike();
            break;
        case 4:
            Cruiser_Bike();
            break;
        case 5:
            Scooter_bike();
            break;
        case 6:
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            break;
        case 7:
            do
            {
                end = clock();
            } while ((end - start) / CLOCKS_PER_SEC < 4);
            printf(ANSI_COLOR_LIGHTGREEN "Exiting the Program. Goodbye...!");
            exit(0);
            break;

        default:

            printf(ANSI_COLOR_RED "Entered Wrong Company Retry it..\n" ANSI_COLOR_RESET);
            break;
        }
    }
}

// Timer
void Time()
{
    clock_t start = clock();
    clock_t end;
    do
    {
        end = clock();
    } while ((end - start) / CLOCKS_PER_SEC < 3);
}

// Sports_Bike Content
void Sports_Bike()
{
    while (1)
    {
        printf(ANSI_COLOR_RESET "\nSport's Bike");
        printf(ANSI_COLOR_LIGHTGREEN "\n1. Aprilia RSV4 RR");
        printf("\n2. Triumph Street Triple RS");
        printf("\n3.  Kawasaki Ninja ZX-10R");
        printf("\n4. Ducati Panigale V4");
        printf("\n5. Go back to Main Manu");
        printf(ANSI_COLOR_RESET "\n\nEnter the Bike Model : " ANSI_COLOR_LIGHTGREEN);
        int model;
        scanf("%d", &model);
        if (model == 5)
            break;

        switch (model)
        {
        case 1:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "1. Aprilia RSV4 RR: \n* Engine: 999.6cc, liquid-cooled, 65-degree V4 engine \n* Power Output: 201 horsepower \n* Torque: 115 Nm \n* Transmission: 6-speed gearbox with quick-shift system \n* Frame: Aluminum dual-beam chassis \n* Suspension: Front inverted fork with adjustable preload, rebound, and compression; Rear monoshock with adjustable preload, rebound, and compression \n* Brakes: Dual 320mm front discs with Brembo calipers; Single 220mm rear disc with Brembo caliper \n* Tires: 120/70 ZR17 front, 200/55 ZR17 rear \n* Weight: 199 kg (dry) \n* Features: Ride-by-wire throttle, traction control, wheelie control, cornering ABS, launch control\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 2:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "1.Triumph Street Triple RS: \n* Engine: 765cc, inline-three, liquid-cooled\n* Power: 121 hp\n* Torque: 79 Nm\n* Transmission: 6-speed\n* Frame: Aluminum beam twin-spar\n* Suspension: Showa 41mm upside-down fork (front), Öhlins STX40 fully adjustable monoshock (rear)\n* Brakes: Dual 310mm discs with Brembo M50 4-piston radial monobloc calipers (front), Single 220mm disc with Brembo single-piston caliper (rear)\n* Weight: 166 kg (dry)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 3:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "1. Kawasaki Ninja ZX-10R:\n* Engine: 998cc, inline-four, liquid-cooled\n* Power: 200 hp\n* Torque: 114 Nm\n* Transmission: 6-speed\n* Frame: Aluminum perimeter\n* Suspension: Showa Balance Free Fork (front), Horizontal Back-Link with BFRC lite gas-charged shock (rear)\n* Brakes: Dual semi-floating 330mm discs with Brembo M50 monobloc calipers (front), Single 220mm disc with Brembo caliper (rear)\n* Weight: 206 kg (kerb)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 4:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "1. Ducati Panigale V4:\n* Engine: 1,103cc, Desmosedici Stradale V4, liquid-cooled\n* Power: 214 hp\n* Torque: 124 Nm\n* Transmission: 6-speed with Ducati Quick Shift (DQS) up/down EVO\n* Frame: Aluminum alloy 'Front Frame'\n* Suspension: Fully adjustable Öhlins NIX30 43mm fork (front), Fully adjustable Öhlins TTX36 rear shock with titanium spring (rear)\n* Brakes: Dual 330mm semi-floating discs with Brembo Stylema monobloc calipers (front), Single 245mm disc with 2-piston caliper (rear)\n* Weight: 198 kg (dry)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        default:
            printf(ANSI_COLOR_RED "Entered Wrong Model" ANSI_COLOR_RESET);
            break;
        }
    }
}

// OffRoading_ike Content
void OffRoading_Bike()
{
    while (1)
    {
        printf(ANSI_COLOR_RESET "\nOff Roading Bike");
        printf(ANSI_COLOR_LIGHTGREEN "\n1. Triumph Street Triple RS");
        printf("\n2. Santa Cruz Nomad ");
        printf("\n3. Yeti SB150");
        printf("\n4. Trek Slash");
        printf("\n5. Go back to Main Manu");
        printf(ANSI_COLOR_RESET "\n\nEnter the Bike Model : " ANSI_COLOR_LIGHTGREEN);
        int model;
        scanf("%d", &model);
        if (model == 5)
            break;
        switch (model)
        {
        case 1:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "1. Santa Cruz Nomad: \n* Frame Material: Carbon fiber \n* Suspension: 170mm front and rear travel \n* Wheel Size: 27.5-inch or 29-inch options available \n* Drivetrain: SRAM or Shimano options, typically 1x12-speed \n* Brakes: Hydraulic disc brakes \n* Features: VPP suspension design, adjustable geometry, dropper seat post \n* Price: Starting around $4,499 (as of last update)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 2:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "2. Yeti SB150: \n* Frame Material: Carbon fiber \n* Suspension: 150mm front and 150mm rear travel \n* Wheel Size: 29-inch \n* Drivetrain: SRAM or Shimano options, typically 1x12-speed \n* Brakes: Hydraulic disc brakes \n* Features: Switch Infinity suspension design, adjustable geometry, carbon frame options \n* Price: Starting around $5,199 (as of last update)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 3:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "3. Specialized Enduro: \n* Frame Material: Carbon fiber or aluminum \n* Suspension: 170mm front and rear travel \n* Wheel Size: 29-inch \n* Drivetrain: SRAM or Shimano options, typically 1x12-speed \n* Brakes: Hydraulic disc brakes \n* Features: SWAT storage system, adjustable geometry, Command Post dropper seat post \n* Price: Starting around $4,500 (as of last update)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 4:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "4. Trek Slash: \n* Frame Material: Carbon fiber \n* Suspension: 160mm front and rear travel \n* Wheel Size: 29-inch \n* Drivetrain: SRAM or Shimano options, typically 1x12-speed \n* Brakes: Hydraulic disc brakes \n* Features: ABP suspension design, Knock Block frame protection, Mino Link adjustable geometry \n* Price: Starting around $4,999 (as of last update)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        default:
            printf(ANSI_COLOR_RED "Entered Wrong Model" ANSI_COLOR_RESET);
            break;
        }
    }
}

// Scooter_Bike Content
void Scooter_bike()
{
    while (1)
    {
        printf(ANSI_COLOR_RESET "\nScooter bike");
        printf(ANSI_COLOR_LIGHTGREEN "\n1. Honda PCX150");
        printf("\n2. Yamaha NMAX 155");
        printf("\n3. Vespa GTS Super 300");
        printf("\n4. BMW C 400 X ");
        printf("\n5. Go back to Main Manu");
        printf(ANSI_COLOR_RESET "\n\nEnter the Bike Model : " ANSI_COLOR_LIGHTGREEN);
        int model;
        scanf("%d", &model);
        if (model == 5)
            break;
        switch (model)
        {
        case 1:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "1. Honda PCX150 \n* Engine: 149cc liquid-cooled 80º single-cylinder four-stroke \n* Power: Approximately 14.5 HP \n* Torque: 13.6 Nm \n* Fuel Capacity: 8 liters \n* Weight: Around 130 kg \n* Seat Height: 764 mm \n* Features: LED lighting, digital instrument panel, ABS, ample under-seat storage, and a 12V accessory socket.)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 2:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "2. Yamaha NMAX 155\n* Engine: 155cc liquid-cooled, 4-stroke, SOHC, 4-valve, single-cylinder\n* Power: 15 HP\n* Torque: 14.4 Nm\n* Fuel Capacity: 6.6 liters\n* Weight: Approximately 127 kg\n* Seat Height: 765 mm\n* Features: VVA (Variable Valve Actuation), ABS, start-stop system, LED lighting, and a digital instrument panel.\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 3:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "3.  Vespa GTS Super 300\n* Engine: 278cc, 4-stroke single cylinder, 4-valves, liquid-cooled\n* Power: 21.2 HP\n* Torque: 22 Nm\n* Fuel Capacity: 8.5 liters\n* Weight: 158 kg\n* Seat Height: 790 mm\n* Features: ABS, ASR traction control, LED daytime running lights and tail light, USB charging port, and a bike finder and remote seat opener feature.\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 4:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "4. BMW C 400 X \n* Engine: 350cc, liquid-cooled, single-cylinder 4-stroke engine, four valves, overhead camshaft with rocker arm \n* Power: 34 HP \n* Torque: 35 Nm \n* Fuel Capacity: 12.8 liters \n* Weight: 204 kg (ready to ride) \n* Seat Height: 775 mm \n* Features: Connectivity with TFT display, full LED lighting, ABS, Automatic Stability Control (ASC), Flexcase under-seat storage, and keyless ride.\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        default:
            printf(ANSI_COLOR_RED "Entered Wrong Model" ANSI_COLOR_RESET);
            break;
        }
    }
}

// Cruiser_Bike Content
void Cruiser_Bike()
{
    while (1)
    {
        printf(ANSI_COLOR_RESET "\nCruiser Bike");
        printf(ANSI_COLOR_LIGHTGREEN "\n1. Harley-Davidson Softail Slim");
        printf("\n2. Indian Chief Dark Horse");
        printf("\n3. Honda Rebel 1100 ");
        printf("\n4.  Yamaha V Star 250 ");
        printf("\n5. Go back to Main Manu");
        printf(ANSI_COLOR_RESET "\n\nEnter the Bike Model : " ANSI_COLOR_LIGHTGREEN);
        int model;
        scanf("%d", &model);
        if (model == 5)
            break;
        switch (model)
        {
        case 1:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "1. Harley-Davidson Softail Slim\n* Engine: Milwaukee-Eight® 107, V-Twin, 1,746 cc\n* Power: Approximately 86 HP\n* Torque: 145 Nm at 3,000 rpm\n* Weight: 291 kg (dry weight)\n* Seat Height: 660 mm\n* Fuel Capacity: 18.9 liters\n* Features: LED lighting, keyless ignition, ABS, and digital instrumentation integrated into the handlebar riser.\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 2:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "2. Indian Chief Dark Horse \n* Engine: Thunderstroke 116, V-Twin, 1,890 cc \n* Power: N/A \n* Torque: 162 Nm at 2,900 rpm \n* Weight: 304 kg (dry weight) \n* Seat Height: 662 mm \n* Fuel Capacity: 15.1 liters \n* Features: Ride Modes (Tour, Standard, Sport), keyless ignition, ABS, cruise control, and a 4-inch touchscreen display with ride data and smartphone connectivity.\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 3:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "3. Honda Rebel 1100 \n* Engine: 1,084 cc liquid-cooled SOHC parallel-twin \n* Power: 87 HP \n* Torque: 98 Nm at 4,750 rpm \n* Weight: 223 kg (wet weight) \n* Seat Height: 700 mm \n* Fuel Capacity: 13.6 liters \n* Features: Honda Selectable Torque Control (HSTC), throttle by wire with three ride modes and a user mode, cruise control, LED lighting, and a slipper clutch.\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 4:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "4. Yamaha V Star 250 \n* Engine: 249 cc air-cooled, SOHC, 2-valves per cylinder, V-twin \n* Power: Approximately 21 HP \n* Torque: 20.6 Nm at 6,000 rpm \n* Weight: 147 kg (wet weight) \n* Seat Height: 685 mm \n* Fuel Capacity: 9.5 liters \n* Features: Classic cruiser styling, lightweight and maneuverable, electric starting, and a 5-speed transmission.\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        default:
            printf(ANSI_COLOR_RED "Entered Wrong Model" ANSI_COLOR_RESET);
            break;
        }
    }
}

// Ev_Bike
void Ev_Bike()
{
    while (1)
    {
        printf(ANSI_COLOR_RESET "\nEv_Bike");
        printf(ANSI_COLOR_LIGHTGREEN "\n1. Rad Power Bikes RadRover 6 Plus");
        printf("\n2. Specialized Turbo Vado SL");
        printf("\n3. Giant Trance E+ 1 Pro");
        printf("\n4. Trek Allant+ 9.9S");
        printf("\n5. Go back to Main Manu");
        printf(ANSI_COLOR_RESET "\n\nEnter the Bike Model : " ANSI_COLOR_LIGHTGREEN);
        int model;
        scanf("%d", &model);
        if (model == 5)
            break;
        switch (model)
        {
        case 1:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "1. Rad Power Bikes RadRover 6 Plus:\n* Motor: 750W geared hub motor\n* Battery: 48V, 14Ah (672Wh) lithium-ion battery\n* Range: Up to 45+ miles per charge\n* Top Speed: 20 mph (Class 2 e-bike)\n* Frame: Aluminum alloy\n* Tires: 26' x 4 ' all-terrain fat tires\n* Features: LCD display, front suspension fork, integrated brake lights, fenders, rear rack\n* Price: Around $1,999 \n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 2:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "2. Specialized Turbo Vado SL:\n* Motor: Specialized SL 1.1 custom lightweight motor (240W nominal)\n* Battery: 320Wh internal battery, optional 160Wh range extender\n* Range: Up to 80 miles with range extender\n* Top Speed: 28 mph (Class 3 e-bike)\n* Frame: Aluminum\n* Tires: 700c\n* Features: Mission Control app connectivity, integrated lights, fenders, rack mounts\n* Price: Starting around $3,350 (as of last update)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 3:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "3. Giant Trance E+ 1 Pro:\n* Motor: Giant SyncDrive Pro, 80Nm torque\n* Battery: Giant EnergyPak 500Wh or 625Wh\n* Range: Up to 70 miles\n* Top Speed: 20 mph (Class 1 e-bike)\n* Frame: ALUXX SL-grade aluminum\n* Tires: 27.5' or 29 ' wheels\n* Features: Maestro suspension system, RideControl ONE handlebar control, integrated battery and motor design\n* Price: Starting around $5,300 (as of last update)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        case 4:
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf(ANSI_COLOR_RESET "4. Trek Allant+ 9.9S:\n* Motor: Bosch Performance Line Speed, 85Nm torque\n* Battery: Bosch PowerTube 625Wh\n* Range: Up to 100 miles\n* Top Speed: 28 mph (Class 3 e-bike)\n* Frame: Alpha Aluminum\n* Tires: 27.5' or 28 ' wheels\n* Features: Integrated lighting system, Bosch Kiox display, Shimano Deore XT 12-speed drivetrain, hydraulic disc brakes\n* Price: Starting around $6,799 (as of last update)\n\n");
            printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        default:
            printf(ANSI_COLOR_RED "Entered Wrong Model" ANSI_COLOR_RESET);
            break;
        }
    }
}