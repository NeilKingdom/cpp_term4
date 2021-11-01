#include <iostream>

#define usingNamespaces 0

#if usingNamespaces
#pragma message("Using namespaces")

int main() {

    std::cout << "Hello World!" << std::endl;
    return 0;
}

#elif !usingNamespaces
#pragma message("Not using namespaces")

using namespace std;

int main() {

    cout << "Hello World!" << endl;
    return 0;
}

#endif