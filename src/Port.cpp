#include "Port.h"

Port::Port(std::string name) : name(std::move(name)) {}

std::string Port::getName() const {
    return name;
}

int Port::getBalance(int dateTime) const {
    int balance = 0;
    for (const auto &t: balanceHistory) {
        if (t.first <= dateTime) {
            balance += t.second;
        } else {
            break;
        }
    }
    return balance;
}

void Port::updateBalance(int dateTime, int containers) {
    balanceHistory[dateTime] += containers;
}
