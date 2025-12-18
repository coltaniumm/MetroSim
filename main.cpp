#include <iostream>
#include <string>
#include <vector>

#include "Network.h"
#include "Validator.h"
#include "ScheduleViewer.h"

using namespace std;

static void showMenu() {
    cout << "\n=== MetroSim Lite ===\n\n";
    cout << "1. Show stations\n";
    cout << "2. Show lines\n";
    cout << "3. Show trains\n";
    cout << "4. Advance simulation (minutes)\n";
    cout << "5. Toggle line open/closed\n";
    cout << "6. Add station\n";
    cout << "7. Add line\n";
    cout << "8. Add train\n";
    cout << "9. Delete train\n";
    cout << "10. Ride a train\n";
    cout << "11. View schedule overview\n";
    cout << "12. Exit\n";
}

int main() {
    Network network;
    network.buildSampleNetwork();

    bool running = true;

    while (running) {
        showMenu();
        int choice = Validator::getIntInRange(1, 12, "Choose an option: ");

        switch (choice) {
        case 1:
            
            network.listStations();
            Validator::waitForEnter();
            break;

        case 2:
        
            network.listLines();
            Validator::waitForEnter();
            break;

        case 3:
            
            network.listTrains();
            Validator::waitForEnter();
            break;

        case 4: {
            
            int minutes = Validator::getNonNegativeInt("Advance by how many minutes? ");
            network.updateAll(minutes);
            cout << "Simulation advanced by " << minutes << " minutes.\n";
            network.listTrains();
            Validator::waitForEnter();
            break;
        }

        case 5: {
         
            int lineId = Validator::getNonNegativeInt("Enter line ID to toggle: ");
            network.toggleLineStatus(lineId);
            network.listLines();
            Validator::waitForEnter();
            break;
        }

        case 6: {
            
            int id = Validator::getNonNegativeInt("Enter new station ID: ");
            cout << "Enter station name (single word): ";
            string name;
            cin >> name; 
            network.addStation(id, name);
            network.listStations();
            Validator::waitForEnter();
            break;
        }

        case 7: {
         
            int lineId = Validator::getNonNegativeInt("Enter new line ID: ");
            cout << "Enter line name (single word): ";
            string name;
            cin >> name;

            int numStops = Validator::getNonNegativeInt("How many station IDs for this line? ");
            vector<int> stops;
            for (int i = 0; i < numStops; ++i) {
                int sid = Validator::getNonNegativeInt(
                    "Enter station ID for stop " + to_string(i) + ": ");
                stops.push_back(sid);
            }

            network.addLine(lineId, name, stops);
            network.listLines();
            Validator::waitForEnter();
            break;
        }

        case 8: {
    
            int trainId = Validator::getNonNegativeInt("Enter new train ID: ");
            cout << "Enter train name (single word): ";
            string name;
            cin >> name;

            int lineId = Validator::getNonNegativeInt("Enter line ID this train runs on: ");
            network.addTrain(trainId, name, lineId);
            network.listTrains();
            Validator::waitForEnter();
            break;
        }

        case 9: {

            int trainId = Validator::getNonNegativeInt("Enter train ID to delete: ");
            bool ok = network.deleteTrain(trainId);
            if (ok) {
                cout << "Train " << trainId << " deleted.\n";
            }
            else {
                cout << "No train found with ID " << trainId << ".\n";
            }
            network.listTrains();
            Validator::waitForEnter();
            break;
        }

        case 10: {
  
            int trainId = Validator::getNonNegativeInt("Enter train ID to ride: ");
            Train* t = network.getTrainById(trainId);
            if (!t) {
                cout << "No train found with ID " << trainId << ".\n";
                Validator::waitForEnter();
                break;
            }

            cout << "Riding train " << trainId
                << ". Enter -1 to stop riding.\n";

            bool riding = true;
            while (riding) {
                cout << "\nCurrent status:\n";
                cout << t->getStatusString() << "\n";

                int minutes = Validator::getIntInRange(-1, 1000,
                    "Advance simulation by how many minutes (-1 to stop riding): ");

                if (minutes == -1) {
                    riding = false;
                }
                else {
                    network.updateAll(minutes);
                }
            }
            Validator::waitForEnter();
            break;
        }
        case 11:
            ScheduleViewer::showSchedule(network);
            Validator::waitForEnter();
            break;
        case 12:
            running = false;
            break;
        default:
            break;
        }
    }
    cout << "Exiting MetroSim Lite.\n";
    return 0;
}
