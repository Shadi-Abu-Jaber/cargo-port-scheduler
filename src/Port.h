#ifndef ADVANCE_OOP_HW2_PORT_H
#define ADVANCE_OOP_HW2_PORT_H

#include <iostream>
#include <map>
#include <string>

class Port {
private:
    std::string name;
    //date (minutes from start of the year) --to--> containers quantity in port
    std::map<int, int> balanceHistory;

public:
    explicit Port(std::string name);

    std::string getName() const;

    int getBalance(int dateTime) const;

    void updateBalance(int dateTime, int containers);

};

#endif //ADVANCE_OOP_HW2_PORT_H