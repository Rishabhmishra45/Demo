#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

class Account
{
public:
    int accountNumber;
    string name;
    string aadhaarNumber;
    double balance;
    string accountType;
    vector<string> transactionHistory;

    Account()
    {
        accountNumber = generateAccountNumber();
    }

    int generateAccountNumber()
    {
        srand(time(0));
        return rand() % 9000000 + 1000000;
    }

    void createAccount()
    {
        cout << "Welcome to our Bank! Let's create your account.\n";
        cout << "Your Account Number is: " << accountNumber << endl;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Aadhaar Number: ";
        getline(cin, aadhaarNumber);
        cout << "Enter Account Type (Savings/Current): ";
        getline(cin, accountType);
        balance = 0.0;
        ostringstream ss;
        ss << "Account created with balance: ?" << fixed << setprecision(2) << balance;
        transactionHistory.push_back(ss.str());
        cout << "Account created successfully!\n";
    }

    void deposit(double amount)
    {
        balance += amount;
        ostringstream ss;
        ss << "Deposited: " << fixed << setprecision(2) << amount << ", New Balance: " << balance;
        transactionHistory.push_back(ss.str());
        cout << "Amount deposited successfully!\n";
    }

    void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient balance!\n";
        }
        else
        {
            balance -= amount;
            ostringstream ss;
            ss << "Withdrew: " << fixed << setprecision(2) << amount << ", New Balance: " << balance;
            transactionHistory.push_back(ss.str());
            cout << "Amount withdrawn successfully!\n";
        }
    }

    void displayBalance()
    {
        cout << "Current Balance: " << fixed << setprecision(2) << balance << endl;
    }

    void calculateInterest()
    {
        if (accountType == "Savings")
        {
            double interestRate = 0.04;
            double interest = balance * interestRate;
            balance += interest;
            ostringstream ss;
            ss << "Interest added: " << fixed << setprecision(2) << interest << ", New Balance: " << balance;
            transactionHistory.push_back(ss.str());
            cout << "Interest calculated and added to balance.\n";
        }
        else
        {
            cout << "Interest calculation is only applicable to Savings accounts.\n";
        }
    }

    void showAccountSummary()
    {
        cout << "\nAccount Summary for Account Number: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Aadhaar Number: " << aadhaarNumber << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: " << fixed << setprecision(2) << balance << endl;
        showTransactionHistory();
    }

    void showTransactionHistory()
    {
        cout << "Transaction History:\n";
        for (size_t i = 0; i < transactionHistory.size(); ++i)
        {
            cout << transactionHistory[i] << endl;
        }
    }
};

class Bank
{
private:
    vector<Account> accounts;

    Account *findAccount(int accountNumber)
    {
        for (size_t i = 0; i < accounts.size(); ++i)
        {
            if (accounts[i].accountNumber == accountNumber)
            {
                return &accounts[i];
            }
        }
        return NULL;
    }

public:
    void addAccount()
    {
        Account newAccount;
        newAccount.createAccount();
        accounts.push_back(newAccount);
    }

    void deleteAccount(int accountNumber)
    {
        for (size_t i = 0; i < accounts.size(); ++i)
        {
            if (accounts[i].accountNumber == accountNumber)
            {
                accounts.erase(accounts.begin() + i);
                cout << "Account deleted successfully!\n";
                return;
            }
        }
        cout << "Account not found!\n";
    }

    void performDeposit(int accountNumber, double amount)
    {
        Account *account = findAccount(accountNumber);
        if (account)
        {
            account->deposit(amount);
        }
        else
        {
            cout << "Account not found!\n";
        }
    }

    void performWithdrawal(int accountNumber, double amount)
    {
        Account *account = findAccount(accountNumber);
        if (account)
        {
            account->withdraw(amount);
        }
        else
        {
            cout << "Account not found!\n";
        }
    }

    void checkBalance(int accountNumber)
    {
        Account *account = findAccount(accountNumber);
        if (account)
        {
            account->displayBalance();
        }
        else
        {
            cout << "Account not found!\n";
        }
    }

    void calculateInterestForAll()
    {
        for (size_t i = 0; i < accounts.size(); ++i)
        {
            accounts[i].calculateInterest();
        }
    }

    void showAllAccounts()
    {
        for (size_t i = 0; i < accounts.size(); ++i)
        {
            accounts[i].showAccountSummary();
        }
    }

    void showTransactionHistory(int accountNumber)
    {
        Account *account = findAccount(accountNumber);
        if (account)
        {
            account->showTransactionHistory();
        }
        else
        {
            cout << "Account not found!\n";
        }
    }
};

int main()
{
    Bank bank;
    int choice, accountNumber;
    double amount;

    while (true)
    {
        cout << "\nWelcome to the Bank Management System\n";
        cout << "1. Create Account\n";
        cout << "2. Delete Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Check Balance\n";
        cout << "6. Calculate Interest for All Accounts\n";
        cout << "7. Show All Accounts\n";
        cout << "8. Show Transaction History\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bank.addAccount();
            break;
        case 2:
            cout << "Enter Account Number to delete: ";
            cin >> accountNumber;
            bank.deleteAccount(accountNumber);
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            bank.performDeposit(accountNumber, amount);
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            bank.performWithdrawal(accountNumber, amount);
            break;
        case 5:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            bank.checkBalance(accountNumber);
            break;
        case 6:
            bank.calculateInterestForAll();
            break;
        case 7:
            bank.showAllAccounts();
            break;
        case 8:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            bank.showTransactionHistory(accountNumber);
            break;
        case 9:
            cout << "Thank you for using Bank Management System!\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
}