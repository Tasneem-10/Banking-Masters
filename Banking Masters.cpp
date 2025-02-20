#include <iostream>
#include <string>
#include <cstdlib> // «” Œœ«„ œ«·… system
#include <fstream> //  ” Œœ„ ·· ⁄«„· „⁄ «·„·›« 
#include <windows.h> // ·≈÷«›… «·√·Ê«‰

using namespace std;

// œ«·… · €ÌÌ— ·Ê‰ «·‰’
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void AccountMenu() {
    setColor(11);
    cout << "=======MENU=======" << endl;
    setColor(14);
    cout << "1: Create a new account " << endl;
    cout << "2: Login " << endl;
    cout << "3: Logout " << endl;
    cout << "4: Withdraw money " << endl;
    cout << "5: Deposit money " << endl;
    cout << "6: Account details" << endl;
    cout << "7: Exit " << endl;
    setColor(11);
    cout << "==================" << endl;
    setColor(7);
}

void NewAccount() {
    string name, password1, password2, ID;
    setColor(10);
    cout << "Please enter your name (without space): ";
    cin >> name;
    cout << "Enter your ID (12 digits): " << endl;
    cin >> ID;
    while (true) {
        if (ID.size() != 12) {
            setColor(12);
            cout << "ID must be exactly 12 digits and positive. Please try again: " << endl;
        } else if (ID.find_first_not_of("0123456789") != std::string::npos) {
            cout << "ID must contain only digits (0-9). Please try again: " << endl;
        } else {
            break;
        }
        cin >> ID;
    }
    setColor(10);
    cout << "Please enter new password: ";
    cin >> password1;
    cout << "Please confirm password: ";
    cin >> password2;
    while (password1 != password2) {
        setColor(12);
        cout << "Passwords do not match, please try again." << endl;
        setColor(10);
        cout << "Please enter new password: ";
        cin >> password1;
        cout << "Please confirm password: ";
        cin >> password2;
    }

    ofstream file("accounts.txt", ios::app); // Õ›Ÿ «·»Ì«‰«  ›Ì „·›
    file << ID << " " << name << " " << password1 << " 0" << endl;  // «·—’Ìœ Ì»œ√ » 0
    file.close(); // ≈€·«ﬁ «·„·›
    setColor(10);
    cout << "Account created successfully!" << endl;
    system("pause"); // ≈ŸÂ«— ¬Œ— —”«·…
    system("cls"); //  ‰ŸÌ› «·‘«‘…
}

void login(string &currentUser, double &balance) {
    string username, password, fileUsername, filePassword, fileID;
    double fileBalance;
    setColor(14);
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    ifstream file("accounts.txt"); // ﬁ—«¡… «·„·›
    while (file >> fileID >> fileUsername >> filePassword >> fileBalance) {
        if (fileUsername == username && filePassword == password) {
            currentUser = username; // Ì÷„‰  ”ÃÌ· «·œŒÊ· „„« Ì”„Õ »⁄„·Ì«  «·”Õ» Ê«·≈Ìœ«⁄ œÊ‰ «·Õ«Ã… · ”ÃÌ· «·œŒÊ· „—… √Œ—Ï
            balance = fileBalance;
            setColor(10);
            cout << "Login successful!" << endl;
            file.close();
            system("pause");
            return;
        }
    }
    setColor(12);
    cout << "Invalid username or password!" << endl;
    file.close();
    system("pause");
    system("cls");
}

void logout(string &currentUser, double &balance) {
    currentUser = "";
    balance = 0;
    setColor(10); // ·Ê‰ √Œ÷—
    cout << "You have logged out successfully!" << endl;
    system("pause");
    system("cls");
}

void updateBalanceInFile(const string &currentUser, double newBalance) {
    ifstream file("accounts.txt"); // ﬁ—«¡… «·»Ì«‰« 
    ofstream tempFile("temp.txt"); // ‰› Õ „·› ÃœÌœ ·‰ﬂ » «·»Ì«‰«  ﬂ·Â« „⁄ «· ⁄œÌ·« 
    string fileID, fileUsername, filePassword;
    double fileBalance;
    while (file >> fileID >> fileUsername >> filePassword >> fileBalance) {
        if (fileUsername == currentUser) {
            fileBalance = newBalance;  //  ÕœÌÀ «·„»·€
        }
        tempFile << fileID << " " << fileUsername << " " << filePassword << " " << fileBalance << endl;
    }
    file.close();
    tempFile.close();
    remove("accounts.txt"); // ‰Õ–› «·„·› «·ﬁœÌ„
    rename("temp.txt", "accounts.txt"); // ‰⁄Ìœ  ”„Ì… «·„·› «·ÃœÌœ
}

void Withdraw(string &currentUser, double &balance) {
    double amount;
    setColor(14);
    cout << "Enter the amount to withdraw: ";
    cin >> amount;
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        updateBalanceInFile(currentUser, balance); // ‰ÕœÀ «·„·› »⁄œ «· ⁄œÌ·
        setColor(10);
        cout << "Successfully withdrawn. Your new balance is: " << fixed << balance << endl;
    } else {
        setColor(12);
        cout << "The amount is invalid or the money is not enough" << endl;
    }
    system("pause");
    system("cls");
}

void deposit(string &currentUser, double &balance) {
    double amount;
    setColor(14);
    cout << "Enter the amount to deposit: ";
    cin >> amount;
    if (amount > 0) {
        balance += amount;
        updateBalanceInFile(currentUser, balance); // ‰ÕœÀ «·„·› »⁄œ «· ⁄œÌ·
        setColor(10);
        cout << "Successfully deposited. Your new balance is: " << fixed << balance << endl;
    } else {
        setColor(12);
        cout << "The amount is invalid" << endl;
    }
    system("pause");
    system("cls");
}

void viewAccountDetails(string currentUser, double balance) {
    if (currentUser != "") {
        setColor(11);
        cout << "Account details for " << currentUser << ":" << endl;
        setColor(14);
        cout << "Username: " << currentUser << endl;
        cout << "Balance: " << fixed << balance << endl;
    } else {
        setColor(12);
        cout << "You need to log in first!" << endl;
    }
    system("pause");
    system("cls");
}

int main() {
    int choice;
    string currentUser = "";
    double balance = 0;
    do {
        system("cls");
        AccountMenu();
        setColor(14);
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                NewAccount();
                break;
            case 2:
                login(currentUser, balance);
                break;
            case 3:
                logout(currentUser, balance);
                break;
            case 4:
                if (currentUser != "") {
                    Withdraw(currentUser, balance);
                } else {
                    setColor(12);
                    cout << "You need to log in first" << endl;
                    system("pause");
                }
                break;
            case 5:
                if (currentUser != "") {
                    deposit(currentUser, balance);
                } else {
                    setColor(12);
                    cout << "You need to log in first" << endl;
                    system("pause");
                }
                break;
            case 6:
                viewAccountDetails(currentUser, balance);
                break;
            case 7:
                setColor(10);
                cout << "Exit " << endl;
                cout << "Thank you for using our banking system!" << endl;
                break;
            default:
                setColor(12);
                cout << "Your choice is not available, try again." << endl;
                system("pause");
        }
        cout << endl;
    } while (choice != 7);

    return 0;
}
