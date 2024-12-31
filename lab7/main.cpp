#include <iostream>
#include <vector>

#include "HybridVehicle.h"

using namespace std;

namespace Helper {
    template<class T>
    T min(T a, T b) {
        return (a < b) ? a : b;
    }

    template <class T>
    T max(T a, T b) {
        return (a < b) ? b : a;
    }
}

void testTemplateLibrary() {

    std::vector<float> vec = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    for(auto &i : vec)
        cout << i << endl;

    while(!vec.empty()) {
        cout << "Last Element: " << vec.back() << endl;
        vec.pop_back();
    }
}

template<class T>
T testVehicle(T pVehicle, const char* vehicleName) {
    cout << vehicleName << "'s range is now: " << pVehicle->calculateRange() << endl;
    pVehicle->drive(150); // Drive 150km
    cout << vehicleName << "'s energy left is: " << pVehicle->percentEnergyRemaining() << endl;
    cout << vehicleName << "'s range is now: " << pVehicle->calculateRange() << endl;
    return pVehicle;
}

int main(int argc, char **argv) {

    // 50L of gas, 7.1L/100km
    delete testVehicle(new GasolineVehicle<float>(50,7.1), "Corolla");

    // 42L of gas, 4.3L/100km, 8.8kWh, 22kWh/100km
    delete testVehicle(new HybridVehicle<double>(42, 4.3, 8.8, 22.0), "Prius");

    // 75 kWh, 16 kWh/100km
    delete testVehicle(new ElectricVehicle<int>(75, 16), "Tesla 3");

    cout << "min of 5 and 7 is: " << Helper::min(5, 7) << endl;
    cout << "max of 5 and 7 is: " << Helper::max(5, 7) << endl;

    cout << "min of A and B is: " << Helper::min('A', 'B') << endl;
    cout << "max of A and B is: " << Helper::max('A', 'B') << endl;

    cout << "min of string(Hello) and string(world) is: " << Helper::min(std::string("Hello"), std::string("World")) << endl;
    cout << "max of string(Hello) and string(world) is: " << Helper::max(std::string("Hello"), std::string("World")) << endl;
    testTemplateLibrary();

    return 0;
}