#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

// Class to represent a financial transaction
class Transaction {
private:
    string type; // "Income" or "Expense"
    string category;
    double amount;

public:
    Transaction(string t, string c, double a) : type(t), category(c), amount(a) {}

    string getType() const { return type; }
    string getCategory() const { return category; }
    double getAmount() const { return amount; }

    void display() const {
        cout << left << setw(10) << type << setw(15) << category << "$" << fixed << setprecision(2) << amount << endl;
    }
};

// Class to manage the budget
class BudgetManager {
private:
    vector<Transaction> transactions;

public:
    void addTransaction(const string& type, const string& category, double amount) {
        if (amount <= 0) {
            cout << "Amount must be positive!" << endl;
            return;
        }
        transactions.emplace_back(type, category, amount);
        cout << "Transaction added successfully!" << endl;
    }

    void displaySummary() const {
        double totalIncome = 0, totalExpense = 0;
        cout << "\nTransaction Summary:" << endl;
        cout << left << setw(10) << "Type" << setw(15) << "Category" << "Amount" << endl;
        cout << "----------------------------------------" << endl;
        for (const auto& transaction : transactions) {
            transaction.display();
            if (transaction.getType() == "Income") {
                totalIncome += transaction.getAmount();
            } else if (transaction.getType() == "Expense") {
                totalExpense += transaction.getAmount();
            }
        }
        cout << "----------------------------------------" << endl;
        cout << "Total Income: $" << fixed << setprecision(2) << totalIncome << endl;
        cout << "Total Expenses: $" << totalExpense << endl;
        cout << "Net Savings: $" << (totalIncome - totalExpense) << endl;
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error: Unable to open file for saving!" << endl;
            return;
        }
        for (const auto& transaction : transactions) {
            outFile << transaction.getType() << "," << transaction.getCategory() << "," << transaction.getAmount() << endl;
        }
        outFile.close();
        cout << "Transactions saved to " << filename << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error: Unable to open file for loading!" << endl;
            return;
        }
        transactions.clear();
        string type, category;
        double amount;
        while (inFile >> type) {
            getline(inFile, category, ',');
            inFile >> amount;
            transactions.emplace_back(type, category, amount);
        }
        inFile.close();
        cout << "Transactions loaded from " << filename << endl;
    }
};

// Main function to drive the program
int main() {
    BudgetManager manager;
    int choice;
    string type, category, filename;
    double amount;

    do {
        cout << "\n--- Personal Budget Manager ---" << endl;
        cout << "1. Add Income" << endl;
        cout << "2. Add Expense" << endl;
        cout << "3. View Summary" << endl;
        cout << "4. Save to File" << endl;
        cout << "5. Load from File" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter category for income: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            manager.addTransaction("Income", category, amount);
            break;
        case 2:
            cout << "Enter category for expense: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            manager.addTransaction("Expense", category, amount);
            break;
        case 3:
            manager.displaySummary();
            break;
        case 4:
            cout << "Enter filename to save transactions: ";
            cin >> filename;
            manager.saveToFile(filename);
            break;
        case 5:
            cout << "Enter filename to load transactions: ";
            cin >> filename;
            manager.loadFromFile(filename);
            break;
        case 6:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
