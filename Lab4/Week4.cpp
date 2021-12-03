
#include <iostream>

#include "Vehicle.h"

using namespace std;

void createVehicle(Vehicle& v, int w = 4, int d = 2) {
    v.setNumWheels(w);
    v.setNumDoors(d);
}

int main(int argc, char **argv) {

    Vehicle original;

    Vehicle copy(original);

    Vehicle secondCopy(&original);
    copy.printVehicle();
    createVehicle(copy,2);
    copy.printVehicle();
    createVehicle(copy,2,3);
    copy.printVehicle();
    copy = secondCopy;
    copy.printVehicle();

    return 0;
}