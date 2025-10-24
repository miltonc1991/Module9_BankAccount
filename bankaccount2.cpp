#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

const string TRANSACTIONS_FILE = "transactions.txt";
const string ACCOUNT_FILE = "account.txt";

string currentDateTime();
void initializeTransactionsFile();

class BankAccount {
private:
    double balance;
    void logTransaction(const string& message) const;
public:
    BankAccount(double initialBalance = 0);
    void deposit(double amount);
    void purchase(double amount);
    void printBalance() const;
    void showTransactionHistory() const;
    void saveAccountSummary() const;
    void saveAccountDetails() const;
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
        cout << "4. View Transaction History" << endl;
        cout << "5. Save Account and Exit" << endl;
        cout << "******************************" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            double amount;
            cout << "Enter deposit amount: $";
            cin >> amount;
            account.deposit(amount);
            break;
        }
        case 2: {
            double amount;
            cout << "Enter purchase amount: $";
            cin >> amount;
            account.purchase(amount);
            break;
        }
        case 3:
            account.printBalance();
            break;
        case 4:
            account.showTransactionHistory();
            break;
        case 5:
            cout << "\nSaving account summary..." << endl;
            account.saveAccountSummary();
            account.saveAccountDetails();
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please select 1–5." << endl;
        }
    } while (choice != 5);

    return 0;
}

// ================== FUNCTION DEFINITIONS ==================
string currentDateTime() {
    time_t now = time(nullptr);
    char buf[64];
    struct tm timeinfo;
    localtime_s(&timeinfo, &now); // Use localtime_s for safety
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

void BankAccount::logTransaction(const string& message) const {
    ofstream file(TRANSACTIONS_FILE, ios::app);
    if (file.is_open()) {
        file << "[" << currentDateTime() << "] " << message << endl;
        file.close();
    }
}

BankAccount::BankAccount(double initialBalance) {
    balance = initialBalance;
    logTransaction("Account created with balance: $" + to_string(balance));
}

void BankAccount::deposit(double amount) {
    if (amount <= 0) {
        cout << "Deposit amount must be positive." << endl;
        return;
    }
    balance += amount;
    cout << fixed << setprecision(2);
    cout << "Deposited: $" << amount << endl;
    cout << "New balance: $" << balance << endl;
    logTransaction("Deposited: $" + to_string(amount) + " | New balance: $" + to_string(balance));
}

void BankAccount::purchase(double amount) {
    if (amount <= 0) {
        cout << "Purchase amount must be positive." << endl;
        return;
    }
    if (amount > balance) {
        cout << "Insufficient funds for purchase." << endl;
        return;
    }
    balance -= amount;
    cout << fixed << setprecision(2);
    cout << "Purchase made: $" << amount << endl;
    cout << "New balance: $" << balance << endl;
    logTransaction("Purchase made: $" + to_string(amount) + " | New balance: $" + to_string(balance));
}

void BankAccount::printBalance() const {
    cout << fixed << setprecision(2);
    cout << "Current balance: $" << balance << endl;
}

void BankAccount::showTransactionHistory() const {
    ifstream file(TRANSACTIONS_FILE);
    if (!file.is_open()) {
        cout << "Error: Could not open " << TRANSACTIONS_FILE << endl;
        return;
    }
    cout << "\n***** Transaction History *****" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    cout << "********************************" << endl;
    file.close();
}

void BankAccount::saveAccountSummary() const {
    ofstream file(TRANSACTIONS_FILE, ios::app);
    if (file.is_open()) {
        file << "[" << currentDateTime() << "] Final balance: $" << balance << endl;
        file << "********************************" << endl;
        file.close();
    }
}

void BankAccount::saveAccountDetails() const {
    ofstream file(ACCOUNT_FILE, ios::out);
    if (file.is_open()) {
        file << "Account summary saved at: " << currentDateTime() << endl;
        file << "Final balance: $" << fixed << setprecision(2) << balance << endl;
        file << "********************************" << endl;
        file.close();
        cout << "Account details saved to " << ACCOUNT_FILE << endl;
    }
}

// ================= FUNCTION DESCRIPTIONS =================
// currentDateTime(): Returns the current date and time as a string.
// initializeTransactionsFile(): Creates or appends to transactions.txt with a log header.
// BankAccount::logTransaction(): Records a transaction with timestamp.
// BankAccount::deposit(): Adds money to balance and logs it.
// BankAccount::purchase(): Deducts money from balance and logs it.
// BankAccount::printBalance(): Shows current balance.
// BankAccount::showTransactionHistory(): Displays all logged transactions.
// BankAccount::saveAccountSummary(): Saves final balance to transactions.txt.
// BankAccount::saveAccountDetails(): Saves readable summary to account.txt.
