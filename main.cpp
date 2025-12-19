// main.cpp
// MetroSim Lite - Final Project
// Entry point and main menu controller for the metro simulation.
// Uses Network to manage data, Validator for safe input, and
// ScheduleViewer to show a simple schedule overview.

#include <iostream>
#include <string>
#include <vector>

#include "Network.h"
#include "Validator.h"
#include "ScheduleViewer.h"

using namespace std;

// Displays the main menu options for the user.
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
    // Network holds all stations, lines, and trains in memory.
    Network network;
    // Preload a small sample network so the user can test immediately.
    network.buildSampleNetwork();

    bool running = true;

    // Main program loop: show menu, handle user choice, repeat.
    while (running) {
        showMenu();

        // Validates that the user enters a menu choice between 1 and 12.
        int choice = Validator::getIntInRange(1, 12, "Choose an option: ");

        switch (choice) {
        case 1:
            // List all stations in the network.
            network.listStations();
            Validator::waitForEnter();
            break;

        case 2:
            // List all lines and whether they are open or closed.
            network.listLines();
            Validator::waitForEnter();
            break;

        case 3:
            // List all trains and their basic status.
            network.listTrains();
            Validator::waitForEnter();
            break;

        case 4: {
            // Advance the simulation clock for all trains.
            int minutes = Validator::getNonNegativeInt("Advance by how many minutes? ");
            network.updateAll(minutes);
            cout << "Simulation advanced by " << minutes << " minutes.\n";
            network.listTrains();
            Validator::waitForEnter();
            break;
        }

        case 5: {
            // Toggle a line between open and closed.
            int lineId = Validator::getNonNegativeInt("Enter line ID to toggle: ");
            network.toggleLineStatus(lineId);
            network.listLines();
            Validator::waitForEnter();
            break;
        }

        case 6: {
            // Add a new station to the network.
            int id = Validator::getNonNegativeInt("Enter new station ID: ");
            cout << "Enter station name (single word): ";
            string name;
            cin >> name; // simple implementation, no spaces in name
            network.addStation(id, name);
            network.listStations();
            Validator::waitForEnter();
            break;
        }

        case 7: {
            // Add a new line with a list of station IDs.
            int lineId = Validator::getNonNegativeInt("Enter new line ID: ");
            cout << "Enter line name (single word): ";
            string name;
            cin >> name;

            int numStops = Validator::getNonNegativeInt("How many station IDs for this line? ");
            vector<int> stops;

            // Collect station IDs that belong to the new line.
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
            // Add a new train that runs on an existing line.
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
            // Delete an existing train by ID.
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
            // Interactive mode: ride a specific train and keep advancing time.
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

                // Allows user to step the simulation while "on" the train.
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
            // Show a simple schedule overview using ScheduleViewer helper.
            ScheduleViewer::showSchedule(network);
            Validator::waitForEnter();
            break;

        case 12:
            // Exit the program.
            running = false;
            break;

        default:
            // Should never hit this because input is validated.
            break;
        }
    }

    cout << "Exiting MetroSim Lite.\n";
    return 0;
}

