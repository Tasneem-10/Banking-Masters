#include <iostream>
#include <string>
#include <cstdlib>  
#include <fstream>                         
#include <windows.h>              

using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

////////////////////////////////////////////////////////////////////////////////////

void AccountMenu()
{
    system("cls");
    setColor(11); 
    cout << "\n";
    cout << " ****************************************************\n";
    cout << " *                                                  *\n";
    cout << " *             WELCOME TO NEXA BANK SYSTEM          *\n";
    cout << " *                                                  *\n";
    cout << " ****************************************************\n";
    cout << " *                                                  *\n";
    cout << " *   1 - Create a new account                       *\n";
    cout << " *   2 - Login to your account                      *\n";
    cout << " *   3 - Logout                                     *\n";
    cout << " *   4 - Withdraw money                             *\n";
    cout << " *   5 - Deposit money                              *\n";
    cout << " *   6 - View account details                       *\n";
    cout << " *   7 - View transaction history                   *\n";
    cout << " *   8 - Exit the system                            *\n";
    cout << " *                                                  *\n";
    cout << " ****************************************************\n";
    setColor(7); // يرجع للون الافتراضي
}

///////////////////////////////////////////////////////////////////////////////////////

bool isIDExists(const string& ID)
{
    ifstream file("accounts.txt");
    string fileID, fileUsername, filePassword;
    double fileBalance;
    while (file >> fileID >> fileUsername >> filePassword >> fileBalance)
    {
        if (fileID == ID)
        {
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////

void NewAccount()
{
    string name, password1, password2, ID;
    setColor(10); // أخضر فاتح
    cout << "Please enter your name: ";
    cin >> name;
    cout << "Enter your ID (12 digits): " << endl;
    cin >> ID;
    while (true)
    {
        if (ID.size() != 12)
        {
            setColor(12); // أحمر
            cout << "ID must be exactly 12 digits. Try again: ";
        }
        else if (ID.find_first_not_of("0123456789") != string::npos)
        {
            setColor(12);
            cout << "ID must contain only digits. Try again: ";
        }
        else if (isIDExists(ID))
        {
            setColor(12);
            cout << "This ID already exists. Please enter a different one: ";
        }
        else
        {
            break;
        }
        cin >> ID;
    }

    setColor(10);
    cout << "Please enter new password: ";
    cin >> password1;
    cout << "Please confirm password: ";
    cin >> password2;
    while (password1 != password2)
    {
        setColor(12);
        cout << "Passwords don't match, please try again." << endl;
        setColor(10);
        cout << "Please enter new password: ";
        cin >> password1;
        cout << "Please confirm password: ";
        cin >> password2;
    }

    ofstream file("accounts.txt", ios::app);
    file << ID << " " << name << " " << password1 << " 0" << endl;
    file.close();
    setColor(11);
    cout << "Account created successfully " << endl;
    setColor(7);
    system("pause");
    system("cls");
    ofstream log("transactions_" + name + ".txt");
    log << "Transaction history for " << name << ":\n";
    log.close();
}

//////////////////////////////////////////////////////////////////////////////////////////

void login(string& currentUser, double& balance)
{
    string username, password, fileUsername, filePassword, fileID;
    double fileBalance;
    setColor(10);
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    ifstream file("accounts.txt");
    while (file >> fileID >> fileUsername >> filePassword >> fileBalance)
    {
        if (fileUsername == username && filePassword == password)
        {
            currentUser = username;
            balance = fileBalance;
            setColor(11);
            cout << "Login successful" << endl;
            file.close();
            setColor(7);
            system("pause");
            return;
        }
    }
    setColor(12);
    cout << "Invalid username or password!" << endl;
    file.close();
    setColor(7);
    system("pause");
    system("cls");
}

/////////////////////////////////////////////////////////////////////////////////////

void logout(string& currentUser, double& balance)
{
    currentUser = "";
    balance = 0;
    setColor(10);
    cout << "You have logged out successfully" << endl;
    setColor(7);
    system("pause");
    system("cls");
}

///////////////////////////////////////////////////////////////////////////////////

void updateBalanceInFile(const string& currentUser, double newBalance)
{
    ifstream file("accounts.txt");
    ofstream tempFile("temp.txt");
    string fileID, fileUsername, filePassword;
    double fileBalance;
    while (file >> fileID >> fileUsername >> filePassword >> fileBalance)
    {
        if (fileUsername == currentUser)
        {
            fileBalance = newBalance;
        }
        tempFile << fileID << " " << fileUsername << " " << filePassword << " " << fileBalance << endl;
    }
    file.close();
    tempFile.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

////////////////////////////////////////////////////////////////////////////////////////

void Withdraw(string& currentUser, double& balance)
{
    double amount;
    setColor(10);
    cout << "Enter the amount to withdraw: ";
    cin >> amount;
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
        updateBalanceInFile(currentUser, balance);
        ofstream log("transactions_" + currentUser + ".txt", ios::app);
        log << "Withdraw: -" << amount << ", Balance: " << balance << endl;
        log.close();
        setColor(11);
        cout << "Successfully withdrawn. Your new balance is: " << fixed << balance << endl;
    }
    else
    {
        setColor(12);
        cout << "The amount is invalid or the money is not enough" << endl;
    }
    setColor(7);
    system("pause");
    system("cls");
}

///////////////////////////////////////////////////////////////////////////////////////

void deposit(string& currentUser, double& balance)
{
    double amount;
    setColor(10);
    cout << "Enter the amount to deposit: ";
    cin >> amount;
    if (amount > 0)
    {
        balance += amount;
        updateBalanceInFile(currentUser, balance);
        ofstream log("transactions_" + currentUser + ".txt", ios::app);
        log << "Deposit: +" << amount << ", Balance: " << balance << endl;
        log.close();
        setColor(11);
        cout << "Successfully deposited. Your new balance is: " << fixed << balance << endl;
    }
    else
    {
        setColor(12);
        cout << "The amount is invalid" << endl;
    }
    setColor(7);
    system("pause");
    system("cls");
}

////////////////////////////////////////////////////////////////////////////////////

void viewAccountDetails(string currentUser, double balance)
{
    if (currentUser != "")
    {
        setColor(11);
        cout << "Account details for " << currentUser << ":" << endl;
        cout << "Username: " << currentUser << endl;
        cout << "Balance: " << fixed << balance << endl;
    }
    else
    {
        setColor(12);
        cout << "You need to log in first!" << endl;
    }
    setColor(7);
    system("pause");
    system("cls");
}

////////////////////////////////////////////////////////////////////////////////////

void viewTransactionHistory(const string& username)
{
    ifstream logfile("transactions_" + username + ".txt");
    if (!logfile)
    {
        setColor(12);
        cout << "No transaction history found." << endl;
    }
    else
    {
        string line;
        setColor(11);
        cout << "Transaction history for " << username << ":\n";
        while (getline(logfile, line))
        {
            cout << line << endl;
        }
    }
    logfile.close();
    setColor(7);
    system("pause");
    system("cls");
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int choice = 0;
    string currentUser = "";
    double balance = 0;
    char input;
    do
    {
        system("cls");
        AccountMenu();
        setColor(10);
        cout << "Enter your choice (1-8): ";
        cin >> input;
        setColor(7);
        if (input >= '1' && input <= '8')
        {
            choice = input - '0';
        }
        else
        {
            setColor(12);
            cout << "Invalid input! Please enter a number between 1 and 8." << endl;
            setColor(7);
            system("pause");
            continue;
        }
        switch (choice)
        {
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
            if (currentUser != "")
            {
                Withdraw(currentUser, balance);
            }
            else
            {
                setColor(12);
                cout << "You need to log in first" << endl;
                setColor(7);
                system("pause");
            }
            break;
        case 5:
            if (currentUser != "")
            {
                deposit(currentUser, balance);
            }
            else
            {
                setColor(12);
                cout << "You need to log in first" << endl;
                setColor(7);
                system("pause");
            }
            break;
        case 6:
            viewAccountDetails(currentUser, balance);
            break;
        case 7:
            if (currentUser != "")
            {
                viewTransactionHistory(currentUser);
            }
            else
            {
                setColor(12);
                cout << "You need to log in first!" << endl;
                setColor(7);
                system("pause");
            }
            break;
        case 8:
            setColor(11);
            cout << "Exit " << endl;
            cout << "Thank you for using our banking system!" << endl;
            setColor(7);
            break;
        default:
            setColor(12);
            cout << "Your choice is not available, try again." << endl;
            setColor(7);
            system("pause");
        }
        cout << endl;
    } while (choice != 8);

    return 0;
}
