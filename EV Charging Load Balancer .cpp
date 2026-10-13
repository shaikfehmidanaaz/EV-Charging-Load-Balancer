
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class EVChargingLoadBalancer {
private:
    double stationCapacity;
    vector<string> evNames;
    vector<double> requestedPower;
    vector<double> allocatedPower;

public:
    EVChargingLoadBalancer(double capacity) {
        stationCapacity = capacity;
    }

    void addEV(string name, double power) {
        evNames.push_back(name);
        requestedPower.push_back(power);
        allocatedPower.push_back(0);
    }

    void balanceLoad() {
        double totalDemand = 0;

        for (double power : requestedPower) {
            totalDemand += power;
        }

        cout << "\n----- EV Charging Load Balancer -----\n";
        cout << "Station Capacity : "
             << stationCapacity << " kW\n";
        cout << "Total EV Demand  : "
             << totalDemand << " kW\n\n";

        // If demand is within station capacity
        if (totalDemand <= stationCapacity) {
            allocatedPower = requestedPower;
        } else {
            // Share power proportionally to each EV's demand
            for (int i = 0; i < requestedPower.size(); i++) {
                allocatedPower[i] =
                    (requestedPower[i] / totalDemand)
                    * stationCapacity;
            }
        }

        cout << left << setw(12) << "EV"
             << setw(18) << "Requested (kW)"
             << setw(18) << "Allocated (kW)" << "\n";

        cout << "-----------------------------------------------\n";

        double totalAllocated = 0;

        for (int i = 0; i < evNames.size(); i++) {
            cout << left << setw(12) << evNames[i]
                 << setw(18) << fixed << setprecision(2)
                 << requestedPower[i]
                 << setw(18) << allocatedPower[i] << "\n";

            totalAllocated += allocatedPower[i];
        }

        cout << "-----------------------------------------------\n";
        cout << "Total Allocated : "
             << totalAllocated << " kW\n";

        if (totalDemand > stationCapacity) {
            cout << "Status: Power shared to prevent overload.\n";
        } else {
            cout << "Status: All EVs receive requested power.\n";
        }
    }
};

int main() {
    // Maximum station capacity = 100 kW
    EVChargingLoadBalancer station(100);

    // Add EVs and their requested charging power
    station.addEV("EV1", 50);
    station.addEV("EV2", 40);
    station.addEV("EV3", 30);

    station.balanceLoad();

    return 0;
}
