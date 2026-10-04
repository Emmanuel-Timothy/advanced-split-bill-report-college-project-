#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Item {
    string name;
    double price;
};

struct Person {
    string name;
    double* qty;
    double subtotal = 0;
};

int main() {
    int nPeople, nItems;

    cout << "Enter number of people: ";
    cin >> nPeople;
    Person* people = new Person[nPeople];

    for (int i = 0; i < nPeople; ++i) {
        cout << "Person " << i + 1 << " name: ";
        cin >> people[i].name;
    }

    cout << "\nEnter number of items: ";
    cin >> nItems;
    Item* items = new Item[nItems];

    for (int i = 0; i < nItems; ++i) {
        cout << "Item " << i + 1 << " name & price: ";
        cin >> items[i].name >> items[i].price;
    }

    cout << "\n--- Enter Portion Eaten (e.g. '6 9' for 6/9, '1 1' for whole, '0 1' for none) ---\n";
    for (int i = 0; i < nPeople; ++i) {
        people[i].qty = new double[nItems];
        cout << "\nConsumption for " << people[i].name << ":\n";
        
        for (int j = 0; j < nItems; ++j) {
            double eaten, total;
            cout << "  " << items[j].name << " (Eaten / Total): ";
            cin >> eaten >> total;

            double portion = (total > 0) ? (eaten / total) : 0;
            people[i].qty[j] = portion;
            people[i].subtotal += portion * items[j].price;
        }
    }

    double taxPct, grandSubtotal = 0;
    cout << "\nEnter tax percentage: ";
    cin >> taxPct;

    for (int i = 0; i < nPeople; ++i) grandSubtotal += people[i].subtotal;
    double grandTax = grandSubtotal * (taxPct / 100.0);

    cout << "\n================ BILL RESULT ================\n" << fixed << setprecision(0);
    for (int i = 0; i < nPeople; ++i) {
        double personTax = (grandSubtotal > 0) ? (people[i].subtotal / grandSubtotal) * grandTax : 0;
        cout << "\nPerson: " << people[i].name << "\nItems:\n";
        
        for (int j = 0; j < nItems; ++j) {
            if (people[i].qty[j] > 0) {
                cout << "  - " << items[j].name << " x" << setprecision(2) 
                     << people[i].qty[j] << " = Rp" << setprecision(0) 
                     << people[i].qty[j] * items[j].price << "\n";
            }
        }
        cout << "Subtotal: Rp" << people[i].subtotal 
             << "\nTax: Rp" << personTax 
             << "\nTotal: Rp" << people[i].subtotal + personTax << "\n";
    }

    cout << "=============================================\n";
    cout << "Grand Subtotal: Rp" << grandSubtotal 
         << "\nGrand Tax: Rp" << grandTax 
         << "\nGrand Total: Rp" << grandSubtotal + grandTax << "\n";

    for (int i = 0; i < nPeople; ++i) delete[] people[i].qty;
    delete[] people;
    delete[] items;

    return 0;
}
