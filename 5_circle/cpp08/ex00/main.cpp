#include "easyfind.hpp"

int main() {
    std::vector<int> vec;
    for (int i = 0; i < 5; ++i)
        vec.push_back(i);

    try {
        std::vector<int>::iterator it = easyfind(vec, 3);
        std::cout << "Found in vector: " << *it << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::list<int> lst;
    for (int i = 10; i < 15; ++i)
        lst.push_back(i);

    try {
        std::list<int>::iterator it = easyfind(lst, 11);
        std::cout << "Found in list: " << *it << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}
