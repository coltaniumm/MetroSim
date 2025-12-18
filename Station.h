#pragma once
#include <string>
#include <iostream>

class Station {
private:
    int id;
    std::string name;

public:
    Station();
    Station(int id, const std::string& name);

    int getId() const;
    const std::string& getName() const;
};

std::ostream& operator<<(std::ostream& os, const Station& s);
