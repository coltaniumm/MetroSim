#include "TransportUnit.h"

TransportUnit::TransportUnit(int id, const std::string& name)
    : id(id), name(name) {
}

int TransportUnit::getId() const {
    return id;
}

const std::string& TransportUnit::getName() const {
    return name;
}
