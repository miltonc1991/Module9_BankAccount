#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

const string TRANSACTIONS_FILE = "transactions.txt";
const string ACCOUNT_FILE = "account.txt";

string currentDateTime() {
    time_t now = time(nullptr);
    char buf[64];
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buf);
}

void initializeTransactionsFile() {
    ofstream file(TRANSACTIONS_FILE, ios::app);
    if (file.is_open()) {
        file << "***** Transaction log started: " << currentDateTime() << " *****" << endl;
        file.close();
    }
}

class BankAccount {
private:
    double balance;
    void logTransaction(const string& message) const {
        ofstream file(TRANSACTIONS_FILE, ios::app);
        if (file.is_open()) {
            file << "[" << currentDateTime() << "] " << message << endl;
            file.close();
        }
    }
public:
    BankAccount(double initialBalance = 0) {
        balance = initialBalance;
        logTransaction("Account created with balance: $" + to_string(balance));
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit must be positive." << endl;
            return;
        }
        balance += amount;
        cout << fixed << setprecision(2);
        cout << "Deposited: $" << amount << endl;
        cout << "New balance: $" << balance << endl;
        logTransaction("Deposited: $" + to_string(amount) + " | New balance: $" + to_string(balance));
    }

    void purchase(double amount) {
        if (amount <= 0) {
            cout << "Purchase must be positive." << endl;
            return;
        }
        if (amount > balance) {
            cout << "Insufficient funds." << endl;
            return;
        }
        balance -= amount;
        cout << fixed << setprecision(2);
        cout << "Purchase: $" << amount << endl;
        cout << "New balance: $" << balance << endl;
        logTransaction("Purchase: $" + to_string(amount) + " | New balance: $" + to_string(balance));
    }

    void printBalance() const {
        cout << fixed << setprecision(2);
        cout << "Current balance: $" << balance << endl;
    }

    void saveAccountSummary() const {
        ofstream file(TRANSACTIONS_FILE, ios::app);
        if (file.is_open()) {
            file << "[" << currentDateTime() << "] Final balance: $" << balance << endl;
            file << "********************************" << endl;
            file.close();
        }
    }

    void saveAccountDetails() const {
        ofstream file(ACCOUNT_FILE, ios::out);
        if (file.is_open()) {
            file << "Account saved at: " << currentDateTime() << endl;
            file << "Final balance: $" << fixed << setprecision(2) << balance << endl;
            file << "********************************" << endl;
            file.close();
            cout << "Account details saved to " << ACCOUNT_FILE << endl;
        }
    }
};

int main() {
    cout << "********************************" << endl;
    cout << "     Welcome to the Bank App    " << endl;
    cout << "********************************" << endl;

    initializeTransactionsFile();

    double initialDeposit;
    cout << "Enter your initial deposit: $";
    cin >> initialDeposit;

    BankAccount account(initialDeposit);

    int choice;
    do {
        cout << "\n************ MENU ************" << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. Make a Purchase" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Save and Exit" << endl;
        cout << "******************************" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            cout << "Enter deposit amount: $";
            cin >> amount;
            account.deposit(amount);
        }
        else if (choice == 2) {
            double amount;
            cout << "Enter purchase amount: $";
            cin >> amount;
            account.purchase(amount);
        }
        else if (choice == 3) {
            account.printBalance();
        }
        else if (choice == 4) {
            account.saveAccountSummary();
            account.saveAccountDetails();
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 4);

    return 0;
}
