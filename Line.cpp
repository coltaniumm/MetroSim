#include "Line.h"

Line::Line() : id(-1), name(""), open(true) {}

Line::Line(int id, const std::string& name, const std::vector<int>& stationIds)
    : id(id), name(name), stationIds(stationIds), open(true) {
}

int Line::getId() const {
    return id;
}

const std::string& Line::getName() const {
    return name;
}

const std::vector<int>& Line::getStationIds() const {
    return stationIds;
}

bool Line::isOpen() const {
    return open;
}

void Line::toggleOpen() {
    open = !open;
}

std::ostream& operator<<(std::ostream& os, const Line& l) {
    os << "Line " << l.getId() << " - " << l.getName()
        << " (" << (l.isOpen() ? "Open" : "Closed") << ")";
    return os;
}
