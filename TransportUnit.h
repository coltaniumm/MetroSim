#pragma once

#include <string>

class TransportUnit {
protected:
    int id;
    std::string name;

public:
    TransportUnit(int id, const std::string& name);
    virtual ~TransportUnit() = default;

    int getId() const;
    const std::string& getName() const;

    virtual void update(int minutes) = 0;
    virtual std::string getStatusString() const = 0;
};
