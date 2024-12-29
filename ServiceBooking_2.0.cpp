#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;


int temp = 0;
// ================================== Main Class of App ===========================================================
class serviceBooking
{
private:
    string selectedService;
    string selectedUrgency;
    string address;
    string paymentMethod;
    int rating;
    string comment;
    double total_amount = 0;
    double platform_fee = 0;

public:
    void choosePersonnel();
    void enterAddress();
    void processPayment();
    void lookurgency();
    void showSuccessMessage();
    friend class payment_method;
    friend class MainMenu;
};

//  ================================== Payment Environment Class =====================================================
class payment_method : public serviceBooking
{
public:
    void paywith();
    void Card();
    void UPI();
};

class MainMenu : public payment_method
{
public:
    void showMainMenu();
    void selectService();
};

// ================================== Dashboard Class ============================================================
class dashboard : public MainMenu
{
public:
    dashboard()
    {
        int choice;
        while (true)
        {
            cout << "\n1. Signup\n";
            cout << "2. Login\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";

            // Validate input
            if (!(cin >> choice))
            {
                cout << "Invalid input! Please enter a numeric value: ";
                cin.clear();                                         // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                continue;                                            // Retry the loop
            }

            switch (choice)
            {
            case 1:
                signup();
                break;
            case 2:
                login();
                if (temp == 0)
                {
                    break; // Exits a loop if temp is 0
                }
                else
                {
                    return;
                }

            case 3:
                cout << "Exiting program...\n";
                exit(0);
            default:
                cout << "Invalid choice! Try again.\n";
                dashboard();
                break;
            }
        }
    }
    void login();
    void signup();
};

// Map to store user credentials (mimics a database)
map<string, string> userDatabase;


// =============================== structure contain data of Personnels =================================================
struct Personnel
{
    string name;
    int age;
    int experience;        // In years
    float rating;          // Out of 5.0
    double distance;       // Distance from user's address in km
    float payment;         // Payment based on rating and experience
    string serviceComment; // Comment about the employee's service
};

Personnel Personnels[5][10];
// personnels [0] -> Electrician
// personnels [1] -> Plumber
// personnels [2] -> Carpentor
// personnels [3] -> HouseKeeper
// personnels [4] -> Gardener
Personnel *currentPersonnelList = nullptr;
Personnel selectedPersonnel;

// Function to load user data from file into memory -----------------------------------------------------------------------
void loadUserData()
{
    ifstream userFile("users.txt");
    string username, password;

    // Read users from file and populate the map
    while (userFile >> username >> password)
    {
        userDatabase[username] = password;
    }
    userFile.close();
}

// Function to save new user data into the file --------------------------------------------------------------------------
void saveUserData()
{
    ofstream userFile("users.txt", ios::trunc); // Open in append mode
    for (const auto &entry : userDatabase)
    {
        userFile << entry.first << " " << entry.second << endl;
    }
    userFile.close();
}



