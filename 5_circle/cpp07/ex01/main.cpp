#include "iter.hpp"

int main() {
    int intArray[5] = {1, 2, 3, 4, 5};
    std::string strArray[4] = {"jacha", "student", "5circle", "fighting"};

    ::iter(intArray, 5, printElement);
    ::iter(strArray, 4, printElement);

    return 0;
}
