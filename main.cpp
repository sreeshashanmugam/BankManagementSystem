#include <iostream>
#include <fstream>
using namespace std;

class BankAccount {
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() const {
        cout << "\nAccount No: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    void deposit() {
        float amt;
        cout << "Enter amount to deposit: ";
        cin >> amt;
        balance += amt;
        cout << "Amount Deposited Successfully!\n";
    }

    void withdraw() {
        float amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;

        if (amt > balance)
            cout << "Insufficient Balance!\n";
        else {
            balance -= amt;
            cout << "Withdrawal Successful!\n";
        }
    }

    int getAccNo() const {
        return accNo;
    }

    float getBalance() const {
        return balance;
    }
};

// Function to write account to file
void writeAccount() {
    BankAccount acc;
    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));

    outFile.close();
    cout << "Account Created Successfully!\n";
}

// Function to display all accounts
void displayAll() {
    BankAccount acc;
    ifstream inFile("bank.dat", ios::binary);

    cout << "\n--- Account List ---\n";
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        acc.showAccount();
        cout << "---------------------\n";
    }

    inFile.close();
}

// Deposit or Withdraw
void modifyAccount(int accNo, int option) {
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while (!file.eof() && !found) {
        streampos pos = file.tellg();
        file.read(reinterpret_cast<char*>(&acc), sizeof(acc));

        if (acc.getAccNo() == accNo) {
            acc.showAccount();

            if (option == 1)
                acc.deposit();
            else
                acc.withdraw();

            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));
            cout << "Record Updated!\n";
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "Account Not Found!\n";
}

// Check balance
void checkBalance(int accNo) {
    BankAccount acc;
    ifstream file("bank.dat", ios::binary);

    bool found = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.getAccNo() == accNo) {
            acc.showAccount();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Account Not Found!\n";
}

// Main Menu
int main() {
    int choice, accNo;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                writeAccount();
                break;

            case 2:
                cout << "Enter Account Number: ";
                cin >> accNo;
                modifyAccount(accNo, 1);
                break;

            case 3:
                cout << "Enter Account Number: ";
                cin >> accNo;
                modifyAccount(accNo, 2);
                break;

            case 4:
                cout << "Enter Account Number: ";
                cin >> accNo;
                checkBalance(accNo);
                break;

            case 5:
                displayAll();
                break;

            case 6:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
