#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_PEOPLE = 100;
const int MAX_ITEMS = 100;

struct Item {
    string name;
    double price;
};

struct Person {
    string name;
    double consumption[MAX_ITEMS];
    double subtotal;
};

int main() {
    int numPeople, numItems;

    cout << "Enter number of people: ";
    cin >> numPeople;

    Person people[MAX_PEOPLE];

    for (int i = 0; i < numPeople; ++i) {
        cout << "Person " << i + 1 << " name: ";
        cin >> people[i].name;
        people[i].subtotal = 0;
    }

    cout << "\nEnter number of items: ";
    cin >> numItems;

    Item items[MAX_ITEMS];

    for (int i = 0; i < numItems; ++i) {
        cout << "Item " << i + 1 << " name & price per portion: ";
        cin >> items[i].name >> items[i].price;
    }

    cout << "\n--- Enter Portion Eaten (e.g., enter '6 9' for 6/9, or '1 1' for 1 whole, '0 1' for none) ---\n";
    for (int i = 0; i < numPeople; ++i) {
        cout << "\nConsumption for " << people[i].name << ":\n";
        
        for (int j = 0; j < numItems; ++j) {
            double eaten, totalPortions;
            
            cout << "  " << items[j].name << " (Eaten / Total): ";
            cin >> eaten >> totalPortions;

            double qty = (totalPortions > 0) ? (eaten / totalPortions) : 0;
            
            people[i].consumption[j] = qty;
            people[i].subtotal += qty * items[j].price;
        }
    }

    double taxPercent, totalSubtotal = 0;
    cout << "\nEnter tax percentage: ";
    cin >> taxPercent;

    for (int i = 0; i < numPeople; ++i) {
        totalSubtotal += people[i].subtotal;
    }
    
    double totalTax = totalSubtotal * (taxPercent / 100.0);

    // Print Receipt
    cout << "\n================ BILL RESULT ================\n" << fixed << setprecision(0);
    for (int i = 0; i < numPeople; ++i) {
        double personTax = (totalSubtotal > 0) ? (people[i].subtotal / totalSubtotal) * totalTax : 0;
        cout << "\nPerson: " << people[i].name << "\nItems:\n";
        
        for (int j = 0; j < numItems; ++j) {
            if (people[i].consumption[j] > 0) {
                cout << "  - " << items[j].name << " x" << setprecision(2) 
                     << people[i].consumption[j] << " = Rp" << setprecision(0) 
                     << people[i].consumption[j] * items[j].price << "\n";
            }
        }
        cout << "Subtotal: Rp" << people[i].subtotal << "\nTax: Rp" << personTax 
             << "\nTotal to pay: Rp" << people[i].subtotal + personTax << "\n";
    }

    cout << "=============================================\n";
    cout << "Grand Subtotal: Rp" << totalSubtotal << "\nTotal Tax: Rp" << totalTax 
         << "\nGrand Total: Rp" << totalSubtotal + totalTax << "\n";

    return 0;
}
