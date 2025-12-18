#pragma once
#include <vector>
#include <string>

#include "Station.h"
#include "Line.h"
#include "Train.h"

class Network {
private:
    std::vector<Station> stations;
    std::vector<Line> lines;
    std::vector<Train> trains;

    Station* findStationById(int id);
    Line* findLineById(int id);
    Train* findTrainById(int id);

public:
    void addStation(int id, const std::string& name);
    void addLine(int id, const std::string& name, const std::vector<int>& stationIds);

    void addTrain(int id, const std::string& name, int lineId);

    bool deleteTrain(int trainId);

    void listStations() const;
    void listLines() const;
    void listTrains() const;

    void toggleLineStatus(int lineId);
    void updateAll(int minutes);


    Train* getTrainById(int trainId);

    void buildSampleNetwork();
};
