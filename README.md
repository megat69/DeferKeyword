# Deferlib
Allows the developer to defer calls to a piece of code to the end of a scope.  
Strongly inspired by the `defer` Go keyword.

## Building
This project uses CMake.  
Configure the CMake project with `cmake -S . -B build`.  
Build the project with `cmake --build build -j`.  
Run the project with `build/test_deferlib`.  

## Usage
This library is single-header only, and can be found at `src/deferlib/deferlib.hpp` in this repo.

## Requirements
The project uses CMake 3.14+  
The library requires C++11

## Examples
See `tests/main.cpp` for more examples.  

### Basic usage
Declare the start of a scope where deferred calls can happen with `defer_init;`.  
Defer a call with `defer()`.

Example :  
```cpp
print("Before the scope");
{
    defer_init;
    print("Just in the scope");
    int* test = new int(5);
    defer(delete test);
    print("I can use the test variable as normal : " << test);
    defer(print("I can also defer prints ; this one happened just before the test variable gets deleted"));
    print("End of the scope");
}
print("After the scope");
```

Output :
```
Before the scope
Just in the scope
I can use the test variable as normal : 5
End of the scope
I can also defer prints ; this one happened just before the test variable gets deleted
After the scope
```

### Scopes within scopes
Every `defer()` call will refer to the closest `defer_init` in its parent scopes.  
This means the following :  
```cpp
{  // Parent
    defer_init;
    print("Now in parent");
    defer(print("Exiting parent"));
    {  // Child 1
        defer_init;
        print("Now in child 1");
        defer(print("Exiting child 1"));
    }
    {  // Child 2
        print("Still in parent (no defer_init)");
        defer(print("Exiting child 2 from parent (still no defer_init in child 2)"));
    }
    {  // Child 3
        defer_init;
        print("Now in child 3");
        defer(print("Exiting child 3"));
    }
}
```

Will result in :  
```
Now in parent
Now in child 1
Exiting child 1
Still in parent (no defer_init)
Now in child 3
Exiting child 3
Exiting child 2 from parent (still no defer_init in child 2)
Exiting parent
```

## Notes and warnings
- `defer_init` creates a new variable called `deferrer` in your scope. Watch out for name conflicts.
- Each deferred call with `defer()` is wrapped in a lambda capturing the current scope under the hood.
- You can omit the final semicolon in a `defer()` call.
- Each `defer()` call gets executed bottom-to-top ; as such, the last `defer()` call of the scope will be the first to be executed (LIFO).
