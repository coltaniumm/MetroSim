#include "ScheduleViewer.h"
#include "Network.h"
#include <iostream>

using namespace std;

void ScheduleViewer::showSchedule(const Network& network) {
    cout << "\n=== Network Schedule Overview ===\n";
    cout << "(Lines and current train positions)\n";

    network.listLines();
    network.listTrains();
}
