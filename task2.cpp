#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
    string type;
    double amount;
    string details;
public:
    Transaction(string t, double a, string d) : type(t), amount(a), details(d) {}
    void display() const {
        cout << type << " | Amount: " << amount << " | " << details << endl;
    }
};

class Account {
    int accountNumber;
    double balance;
    vector<Transaction> transactions;
public:
    Account(int accNo, double bal = 0.0) : accountNumber(accNo), balance(bal) {}

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount, "Amount deposited"));
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount, "Amount withdrawn"));
        } else {
            cout << "Insufficient funds!\n";
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (amount <= balance) {
            balance -= amount;
            toAccount.balance += amount;
            transactions.push_back(Transaction("Transfer", amount, "Sent to Account " + to_string(toAccount.getAccountNumber())));
            toAccount.transactions.push_back(Transaction("Transfer", amount, "Received from Account " + to_string(accountNumber)));
        } else {
            cout << "Insufficient funds for transfer!\n";
        }
    }

    void showTransactions() const {
        cout << "--- Transaction History for Account " << accountNumber << " ---\n";
        for (const auto &t : transactions) {
            t.display();
        }
    }

    void showAccountInfo() const {
        cout << "Account Number: " << accountNumber << " | Balance: " << balance << endl;
    }
};

class Customer {
    string name;
    int id;
    vector<Account> accounts;
public:
    Customer(string n, int i) : name(n), id(i) {}

    void addAccount(int accountNumber, double initialBalance = 0) {
        accounts.push_back(Account(accountNumber, initialBalance));
    }

    Account* getAccount(int accountNumber) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accountNumber) return &acc;
        }
        return nullptr;
    }

    void showCustomerInfo() const {
        cout << "Customer ID: " << id << " | Name: " << name << endl;
        for (const auto &acc : accounts) {
            acc.showAccountInfo();
        }
    }

    int getId() const { return id; }
};

int main() {
    vector<Customer> customers;
    int choice, custId, accNo;
    string name;
    double amount;

    while (true) {
        cout << "\n=== Banking System Menu ===\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer\n";
        cout << "6. Show Customer Info\n";
        cout << "7. Show Transactions\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1:
            cout << "Enter Customer ID: ";
            cin >> custId;
            cout << "Enter Customer Name: ";
            cin >> name;
            customers.push_back(Customer(name, custId));
            cout << "Customer created successfully!\n";
            break;

        case 2:
            cout << "Enter Customer ID: ";
            cin >> custId;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Initial Balance: ";
            cin >> amount;
            for (auto &c : customers) {
                if (c.getId() == custId) {
                    c.addAccount(accNo, amount);
                    cout << "Account created successfully!\n";
                }
            }
            break;

        case 3:
            cout << "Enter Customer ID: ";
            cin >> custId;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            for (auto &c : customers) {
                if (c.getId() == custId) {
                    Account* acc = c.getAccount(accNo);
                    if (acc) acc->deposit(amount);
                }
            }
            break;

        case 4:
            cout << "Enter Customer ID: ";
            cin >> custId;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            for (auto &c : customers) {
                if (c.getId() == custId) {
                    Account* acc = c.getAccount(accNo);
                    if (acc) acc->withdraw(amount);
                }
            }
            break;

        case 5:
            int custId2, accNo2;
            cout << "Enter Sender Customer ID: ";
            cin >> custId;
            cout << "Enter Sender Account Number: ";
            cin >> accNo;
            cout << "Enter Receiver Customer ID: ";
            cin >> custId2;
            cout << "Enter Receiver Account Number: ";
            cin >> accNo2;
            cout << "Enter Transfer Amount: ";
            cin >> amount;
            {
                Account *from = nullptr, *to = nullptr;
                for (auto &c : customers) {
                    if (c.getId() == custId) from = c.getAccount(accNo);
                    if (c.getId() == custId2) to = c.getAccount(accNo2);
                }
                if (from && to) from->transfer(*to, amount);
                else cout << "Account not found!\n";
            }
            break;

        case 6:
            cout << "Enter Customer ID: ";
            cin >> custId;
            for (auto &c : customers) {
                if (c.getId() == custId) {
                    c.showCustomerInfo();
                }
            }
            break;

        case 7:
            cout << "Enter Customer ID: ";
            cin >> custId;
            cout << "Enter Account Number: ";
            cin >> accNo;
            for (auto &c : customers) {
                if (c.getId() == custId) {
                    Account* acc = c.getAccount(accNo);
                    if (acc) acc->showTransactions();
                }
            }
            break;

        default:
            cout << "Invalid choice!\n";
        }
    }

    cout << "Exiting Banking System...\n";
    return 0;
}
