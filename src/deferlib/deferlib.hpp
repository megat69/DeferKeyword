#pragma once

#ifndef DEFERLIB_DEFERRER_NAME
#define DEFERLIB_DEFERRER_NAME deferrer
#endif

#include <functional>
#include <stack>

/// @brief The function type expected by the deferrer : a function with no return value nor parameters.
using deferred_call_t = std::function<void()>;

/// @class Calls all deferred calls when going out of scope/getting destroyed
class Deferrer {
    /// @brief A stack of deferred calls, so the last deferred call is the first to be called on destruction
    std::stack<deferred_call_t> deferredCalls;

public:
    Deferrer() = default;

    /**
     * @brief Calls each deferred call before the class is destroyed
     */
    ~Deferrer() {
        while (!deferredCalls.empty()) {
            const deferred_call_t& defferredCall = deferredCalls.top();
            defferredCall();
            deferredCalls.pop();
        }
    }

    /**
     * @brief Makes the given call execute at the end of the scope/when this class is deleted.
     * @param call A function with no parameters nor return value (preferrably a lambda with its scope captured)
     */
    void defer_call(deferred_call_t call) {
        deferredCalls.push(call);
    }
};


/**
 * @brief Defers the given call to the end of the scope
 * @warning Prerequisite : A `Deferrer` previously created in the scope with the name `deferrer`.
 */
#define defer(x) DEFERLIB_DEFERRER_NAME.defer_call([&](){ x ; })

/// @brief Creates a new deferrer with the name `deferrer`
#define defer_init Deferrer DEFERLIB_DEFERRER_NAME

