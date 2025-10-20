#include <iostream>
#include <fstream>

#include "deferlib/deferlib.hpp"

#define print(x) std::cout << x << std::endl


void heapAllocatedDeferrerTests() {
    Deferrer* deferrer = new Deferrer();
    deferrer->defer_call([&](){
        print("Test"); 
    });
    print("\nBefore deletion");
    delete deferrer;
    print("After deletion\n");
}


int main() {
    // Initializes the deferrer
    defer_init;
    print("Hello World!\n");
    defer(print("Goodbye World!"));  // Last ever string printed to the console by this program

    // Shows the deletion at the end of the scope of a heap-allocated object
    int* testVar = new int(5);
    defer(delete testVar; print("Deleted testVar"));
    std::cout << "New int: " << *testVar << " at address " << testVar << "\n" << std::endl;

    // Shows the automatic closing at the end of the scope of a file
    std::ifstream textFile("test/test.txt");
    defer(textFile.close());
    if (textFile.is_open()) {
        print("In the file is :");
        std::cout << textFile.rdbuf();
        print("");
    }

    // In another scope
    {
        defer_init;
        defer(print("From another scope !\n"));
    }
    defer(print("The original deferrer wasn't touched by the scope deferrer."));

    // Tests where the deferrer is heap-allocated
    heapAllocatedDeferrerTests();

    return 0;
}
