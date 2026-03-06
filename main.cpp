#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct stock {
    string symbol;
    int shares;
    double price;

    stock(string s, int sh, double p) : symbol(s), shares(sh), price(p) {}
};

queue<stock> fifoQueue;
stack<stock> lifoStack;

double sellFIFO(string symbol, int sharesToSell) {
    int sharesNeeded = sharesToSell;
    double totalCost = 0;
    queue<stock> tempQueue;

    while (!fifoQueue.empty() && sharesNeeded > 0) {
        stock current = fifoQueue.front();
        fifoQueue.pop();
        if (current.symbol == symbol) {
            if (current.shares <= sharesNeeded) {
                totalCost += current.shares * current.price;
                sharesNeeded -= current.shares;
            } else {
                totalCost += sharesNeeded * current.price;
                current.shares -= sharesNeeded;
                sharesNeeded = 0;
                tempQueue.push(current);
            }
        } else {
            tempQueue.push(current);
        }
    }

    // Put back remaining stocks
    while (!tempQueue.empty()) {
        fifoQueue.push(tempQueue.front());
        tempQueue.pop();
    }

    if (sharesNeeded > 0) {
        cout << "Not enough shares to sell for FIFO.\n";
        return -1;
    }

    return totalCost / sharesToSell;
}

double sellLIFO(string symbol, int sharesToSell) {
    int sharesNeeded = sharesToSell;
    double totalCost = 0;
    stack<stock> tempStack;

    while (!lifoStack.empty() && sharesNeeded > 0) {
        stock current = lifoStack.top();
        lifoStack.pop();
        if (current.symbol == symbol) {
            if (current.shares <= sharesNeeded) {
                totalCost += current.shares * current.price;
                sharesNeeded -= current.shares;
            } else {
                totalCost += sharesNeeded * current.price;
                current.shares -= sharesNeeded;
                sharesNeeded = 0;
                tempStack.push(current);
            }
        } else {
            tempStack.push(current);
        }
    }

    // Put back remaining stocks
    while (!tempStack.empty()) {
        lifoStack.push(tempStack.top());
        tempStack.pop();
    }

    if (sharesNeeded > 0) {
        cout << "Not enough shares to sell for LIFO.\n";
        return -1;
    }

    return totalCost / sharesToSell;
}

void addStock(string symbol, int shares, double price) {
    stock newStock(symbol, shares, price);
    fifoQueue.push(newStock);
    lifoStack.push(newStock);
}

int main() {
    int choice;
    do {
        cout << "\nPress 1 to enter a new stock\n";
        cout << "Press 2 to find the LIFO and FIFO price for a stock\n";
        cout << "Press 0 to exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string symbol;
            int shares;
            double price;
            cout << "Enter stock symbol: ";
            cin >> symbol;
            cout << "Enter number of shares: ";
            cin >> shares;
            cout << "Enter purchase price: ";
            cin >> price;
            addStock(symbol, shares, price);
        } else if (choice == 2) {
            string symbol;
            int shares;
            cout << "Enter stock symbol: ";
            cin >> symbol;
            cout << "Enter number of shares to sell: ";
            cin >> shares;
            double fifoPrice = sellFIFO(symbol, shares);
            double lifoPrice = sellLIFO(symbol, shares);
            if (fifoPrice != -1 && lifoPrice != -1) {
                cout << "FIFO average price: $" << fifoPrice << endl;
                cout << "LIFO average price: $" << lifoPrice << endl;
            }
        } else if (choice == 0) {
            cout << "Exiting program.\n";
        } else {
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}

