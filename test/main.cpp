#include <iostream>
#include <fstream>

#include "deferlib/deferlib.hpp"

#define print(x) std::cout << x << std::endl

int main() {
    // Initializes the deferrer
    defer_init;
    print("Hello World!");
    defer(print("Goodbye World!"));  // Last ever string printed to the console by this program

    // Shows the deletion at the end of the scope of a heap-allocated object
    int* testVar = new int(5);
    defer(delete testVar; print("Deleted testVar"));
    std::cout << "New int: " << *testVar << " at address " << testVar << std::endl;

    // Shows the automatic closing at the end of the scope of a file
    std::ifstream textFile("test/test.txt");
    defer(textFile.close());
    if (textFile.is_open()) {
        std::cout << textFile.rdbuf();
    }

    return 0;
}