#include "Train.h"

Train::Train()
    : id(-1), name(""), lineId(-1),
    currentStopIndex(0), minutesToNextStop(5) {
}

Train::Train(int id, const std::string& name, int lineId)
    : id(id), name(name), lineId(lineId),
    currentStopIndex(0), minutesToNextStop(5) {
}

int Train::getId() const {
    return id;
}

const std::string& Train::getName() const {
    return name;
}

int Train::getLineId() const {
    return lineId;
}

int Train::getCurrentStopIndex() const {
    return currentStopIndex;
}

int Train::getMinutesToNextStop() const {
    return minutesToNextStop;
}

void Train::update(int minutes, int numberOfStops, bool lineOpen) {
    if (lineId == -1 || numberOfStops <= 0) {
        return; 
    }

    if (!lineOpen) {
       
        return;
    }

    if (minutes <= 0) {
        return;
    }

    minutesToNextStop -= minutes;

    while (minutesToNextStop <= 0) {
 
        currentStopIndex = (currentStopIndex + 1) % numberOfStops;
        minutesToNextStop += 5; 
    }
}

std::string Train::getStatusString() const {
    std::string status = "Train " + name +
        " (ID " + std::to_string(id) + ") on line " +
        std::to_string(lineId) +
        " at stop index " + std::to_string(currentStopIndex) +
        ", minutes to next stop: " + std::to_string(minutesToNextStop);
    return status;
}

std::ostream& operator<<(std::ostream& os, const Train& t) {
    os << t.getStatusString();
    return os;
}
