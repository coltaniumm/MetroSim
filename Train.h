#pragma once
#include <string>
#include <iostream>

class Train {
private:
    int id;
    std::string name;
    int lineId;            // ID of the line this train runs on
    int currentStopIndex;  // index into the line's station list
    int minutesToNextStop; // simple countdown, 5 min between stops

public:
    Train();
    Train(int id, const std::string& name, int lineId);

    int getId() const;
    const std::string& getName() const;
    int getLineId() const;
    int getCurrentStopIndex() const;
    int getMinutesToNextStop() const;

    void update(int minutes, int numberOfStops, bool lineOpen);
    std::string getStatusString() const;
};

std::ostream& operator<<(std::ostream& os, const Train& t);
