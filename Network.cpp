#include "Network.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// --- private find helpers ---

Station* Network::findStationById(int id) {
    for (auto& s : stations) {
        if (s.getId() == id) return &s;
    }
    return nullptr;
}

Line* Network::findLineById(int id) {
    for (auto& l : lines) {
        if (l.getId() == id) return &l;
    }
    return nullptr;
}

Train* Network::findTrainById(int id) {
    for (auto& t : trains) {
        if (t.getId() == id) return &t;
    }
    return nullptr;
}

// --- public methods ---

void Network::addStation(int id, const std::string& name) {
    if (findStationById(id) != nullptr) {
        cout << "Station ID " << id << " already exists.\n";
        return;
    }
    stations.emplace_back(id, name);
}

void Network::addLine(int id, const std::string& name, const std::vector<int>& stationIds) {
    if (findLineById(id) != nullptr) {
        cout << "Line ID " << id << " already exists.\n";
        return;
    }
    if (stationIds.empty()) {
        cout << "Cannot create line with no stations.\n";
        return;
    }
    // Simple check: at least station IDs exist
    for (int sid : stationIds) {
        if (findStationById(sid) == nullptr) {
            cout << "Warning: station ID " << sid
                << " does not exist for line " << id << ".\n";
        }
    }
    lines.emplace_back(id, name, stationIds);
}

void Network::addTrain(int id, const std::string& name, int lineId) {
    if (findTrainById(id) != nullptr) {
        cout << "Train ID " << id << " already exists.\n";
        return;
    }
    Line* line = findLineById(lineId);
    if (!line) {
        cout << "Cannot add train: line " << lineId << " does not exist.\n";
        return;
    }
    trains.emplace_back(id, name, lineId);
}

bool Network::deleteTrain(int trainId) {
    for (auto it = trains.begin(); it != trains.end(); ++it) {
        if (it->getId() == trainId) {
            trains.erase(it);
            return true;
        }
    }
    return false;
}

void Network::listStations() const {
    cout << "\n--- Stations ---\n";
    if (stations.empty()) {
        cout << "No stations.\n";
        return;
    }
    for (const auto& s : stations) {
        cout << s << "\n";
    }
}

void Network::listLines() const {
    cout << "\n--- Lines ---\n";
    if (lines.empty()) {
        cout << "No lines.\n";
        return;
    }
    for (const auto& l : lines) {
        cout << l << "\n";
    }
}

void Network::listTrains() const {
    cout << "\n--- Trains ---\n";
    if (trains.empty()) {
        cout << "No trains.\n";
        return;
    }
    for (const auto& t : trains) {
        cout << t << "\n";
    }
}

void Network::toggleLineStatus(int lineId) {
    Line* line = findLineById(lineId);
    if (!line) {
        cout << "Line ID " << lineId << " not found.\n";
        return;
    }
    line->toggleOpen();
    cout << "Line " << line->getName()
        << " is now " << (line->isOpen() ? "Open" : "Closed") << ".\n";
}

void Network::updateAll(int minutes) {
    for (auto& t : trains) {
        Line* line = findLineById(t.getLineId());
        if (!line) continue;
        int numStops = static_cast<int>(line->getStationIds().size());
        bool open = line->isOpen();
        t.update(minutes, numStops, open);
    }
}

Train* Network::getTrainById(int trainId) {
    return findTrainById(trainId);
}

void Network::buildSampleNetwork() {

    addStation(1, "Central");

    addStation(2, "North");
    addStation(3, "East");

    addStation(4, "South");

    addLine(10, "RedLine", { 1, 2, 3, 4 });

    addTrain(100, "R-1", 10);
    addTrain(101, "R-2", 10);
}
