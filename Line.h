#pragma once
#include <string>
#include <vector>
#include <iostream>

class Line {
private:
    int id;
    std::string name;
    std::vector<int> stationIds;   // station IDs in order
    bool open;                     // true = open, false = closed

public:
    Line();
    Line(int id, const std::string& name, const std::vector<int>& stationIds);

    int getId() const;
    const std::string& getName() const;
    const std::vector<int>& getStationIds() const;

    bool isOpen() const;
    void toggleOpen();
};

std::ostream& operator<<(std::ostream& os, const Line& l);
