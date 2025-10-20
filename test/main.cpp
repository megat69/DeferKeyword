#include <iostream>
#include <fstream>

#include "deferlib/deferlib.hpp"

#define print(x) std::cout << x << std::endl

int main() {
    defer_init;
    defer(print("Hello World!"));

    int* testVar = new int(5);
    defer(delete testVar; print("Deleted testVar"));
    std::cout << "New int: " << *testVar << " at address " << testVar << std::endl;

    std::ifstream textFile("test/test.txt");
    defer(textFile.close());
    if (textFile.is_open()) {
        std::cout << textFile.rdbuf();
    }

    return 0;
}