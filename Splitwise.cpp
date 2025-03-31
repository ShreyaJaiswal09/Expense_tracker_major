#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Node structure for linked list
struct Expense {
    int id;
    float amount;
    string category;
    string date;
    Expense* next;
};

// Class for Expense Tracker
class ExpenseTracker {
private:
    Expense* head;
    int expenseCount;

public:
    // Constructor
    ExpenseTracker() {
        head = nullptr;
        expenseCount = 0;
    }

    // Add a new expense
    void addExpense(float amount, string category, string date) {
        Expense* newExpense = new Expense();
        newExpense->id = ++expenseCount;
        newExpense->amount = amount;
        newExpense->category = category;
        newExpense->date = date;
        newExpense->next = head;
        head = newExpense;

        cout << "Expense added successfully!\n";
    }

    // Display all expenses
    void displayExpenses() {
        if (head == nullptr) {
            cout << "No expenses to show.\n";
            return;
        }
        Expense* current = head;
        while (current != nullptr) {
            cout << "ID: " << current->id << " | Amount: $" << current->amount << " | Category: " << current->category << " | Date: " << current->date << endl;
            current = current->next;
        }
    }

    // Calculate total expenses
    float calculateTotal() {
        float total = 0;
        Expense* current = head;
        while (current != nullptr) {
            total += current->amount;
            current = current->next;
        }
        return total;
    }

    // Delete an expense by ID
    void deleteExpense(int id) {
        if (head == nullptr) {
            cout << "No expenses to delete.\n";
            return;
        }

        Expense* current = head;
        Expense* previous = nullptr;

        // Find the expense to delete
        while (current != nullptr && current->id != id) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Expense with ID " << id << " not found.\n";
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
        cout << "Expense deleted successfully!\n";
    }

    // Save expenses to a file
    void saveToFile(string filename) {
        ofstream file;
        file.open(filename);

        Expense* current = head;
        while (current != nullptr) {
            file << current->id << "," << current->amount << "," << current->category << "," << current->date << endl;
            current = current->next;
        }

        file.close();
        cout << "Expenses saved to " << filename << " successfully!\n";
    }

    // Load expenses from a file
    void loadFromFile(string filename) {
        ifstream file;
        file.open(filename);

        if (!file.is_open()) {
            cout << "Unable to open file.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            int id;
            float amount;
            string category, date;

            // Parse the line (simple CSV parsing)
            sscanf(line.c_str(), "%d,%f,%[^,],%s", &id, &amount, &category[0], &date[0]);

            // Recreate the linked list
            addExpense(amount, category, date);
        }

        file.close();
        cout << "Expenses loaded from " << filename << " successfully!\n";
    }
};

// Main function
int main() {
    ExpenseTracker tracker;
    int choice;

    while (true) {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n";
        cout << "2. Display Expenses\n";
        cout << "3. Calculate Total Expenses\n";
        cout << "4. Delete Expense\n";
        cout << "5. Save Expenses to File\n";
        cout << "6. Load Expenses from File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            float amount;
            string category, date;
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter date (DD/MM/YYYY): ";
            cin >> date;
            tracker.addExpense(amount, category, date);
            break;
        }
        case 2:
            tracker.displayExpenses();
            break;
        case 3: {
            float total = tracker.calculateTotal();
            cout << "Total Expenses: $" << total << endl;
            break;
        }
        case 4: {
            int id;
            cout << "Enter Expense ID to delete: ";
            cin >> id;
            tracker.deleteExpense(id);
            break;
        }
        case 5: {
            string filename;
            cout << "Enter filename to save expenses: ";
            cin >> filename;
            tracker.saveToFile(filename);
            break;
        }
        case 6: {
            string filename;
            cout << "Enter filename to load expenses from: ";
            cin >> filename;
            tracker.loadFromFile(filename);
            break;
        }
        case 7:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
