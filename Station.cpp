#include "Station.h"

Station::Station() : id(-1), name("") {}

Station::Station(int id, const std::string& name)
    : id(id), name(name) {
}

int Station::getId() const {
    return id;
}

const std::string& Station::getName() const {
    return name;
}

std::ostream& operator<<(std::ostream& os, const Station& s) {
    os << "Station " << s.getId() << " - " << s.getName();
    return os;
}
