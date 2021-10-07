
#include <iostream>
#include <limits>

using namespace std;

namespace CST8219 {

    class Vehicle {

    private:
        int numWheels;
        int numDoors;

    public:
        Vehicle(int w, int d) {
            cout << "In constructor with 2 parameters, wheels = " << w << " doors = " << d << endl;
            setNumWheels(w);
            setNumDoors(d);
        }

        Vehicle(int w) : Vehicle(w, 4) {
            cout << "In constructor with 1 parameter, wheels = " << w << endl;
        }

        Vehicle() : Vehicle(4) {
            cout << "In constructor with 0 parameters" << endl;
        }

        ~Vehicle() {
            cout << "In destructor" << endl;
        }

        void setNumWheels(int w) {
            numWheels = w;
        }

        void setNumDoors(int d) {
            numDoors = d;
        }
    };
}

int main(int argc, char **argv) {

    int w,d;
    string c;

    CST8219::Vehicle veh1;
    cout << "Vehicle takes " << sizeof(veh1) << endl;
    CST8219::Vehicle veh2(2);
    cout << "Vehicle takes " << sizeof(veh2) << endl;
    CST8219::Vehicle veh3(4,2);
    cout << "Vehicle takes " << sizeof(veh3) << endl;

    CST8219::Vehicle *pVehicle = NULL;

    do {
        delete pVehicle;

        cout << "Please enter number of wheels: ";
        while(!(cin >> w) || w < 1) {
            cout << "Invalid number, please try again..." << endl;
            //"resets" the buffer to allow user input to be taken again
            cin.clear();
            //clear anything remaining in buffer
            cin.ignore(numeric_limits<int>::max(), '\n');
        }

        cout << "Please enter number of doors: ";
        while(!(cin >> d) || d < 1) {
            cout << "Invalid number, please try again..." << endl;
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }

        cout << "If you would like to quit, press 'q', otherwise, press any key to create another vehicle." << endl;
        //using getline() allows enter/'\n' as valid input
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
        getline(cin, c);

        pVehicle = new CST8219::Vehicle(w,d);

    } while(c != "q");

    delete pVehicle;
    return 0;
}