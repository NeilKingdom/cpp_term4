#include <iostream>

#include "Vehicle.h"

using namespace std;

void createVehicle(Vehicle& v, int w = 4, int d = 2) {
    v.setNumWheels(w);
    v.setNumDoors(d);
}

int main(int argc, char **argv) {

    Vehicle original;
    Vehicle copy(original); //Copy constructor by reference

    cout << "Original is:" << original << "Copy is:" << copy << endl;

    cout << "Increment original:" << original++ << endl;
    cout << "Increment copy:" << ++copy << endl;

    cout << "Decrement original:" << --original << endl;
    cout << "Decrement copy:" << copy-- << endl;

    //Should be true                   //this    //veh
    cout << "Compare equality 1: " << (original==copy) << endl;
    //Should be false
    cout << "Compare equality 2: " << (--original == ++copy) << endl;
    //Should be true
    cout << "Compare inequality: " << (original != copy) << endl;

    //This should make original = copy, and then return a Vehicle for output
    cout << "Assignment operator:" << (original = copy) << endl;

    return 0;
}