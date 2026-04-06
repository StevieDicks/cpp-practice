#include <cassert>
#include <cstddef>
#include <iostream>

// Nullable pointer style: caller may pass nullptr.
static void IncrementIfValid(int* maybe_value) {
    if (maybe_value != nullptr) {
        ++(*maybe_value);
    }
}

// Reference style: caller must pass a valid object.
// References are not reseatable and cannot be null.
static void IncrementRequired(int& value) {
    ++value;
}

// Pointer-to-const: function promises not to mutate array contents.
static int SumFirstTwo(const int* values, std::size_t length) {
    assert(values != nullptr);
    assert(length >= 2U);
    return values[0] + values[1];
}

int main() {
    int value = 10;

    // Plain pointer can be reseated and can be null.
    int* pointer = &value;
    assert(*pointer == 10);

    IncrementIfValid(pointer);
    assert(value == 11);

    // Null pointer path is valid for this API shape.
    IncrementIfValid(nullptr);
    assert(value == 11);

    // int* const => constant pointer to mutable int.
    // Pointer address cannot change after initialization.
    int* const fixed_pointer = &value;
    *fixed_pointer = 15;
    assert(value == 15);

    // Reference is an alias. It is always bound to an existing object.
    int& alias = value;             // Need to look more into aliases
    IncrementRequired(alias);       // What's a good use for them? Why?
    assert(value == 16);
    assert(&alias == &value);

    int samples[3] = { 4, 5, 6 };
    int sum = SumFirstTwo(samples, 3U);
    assert(sum == 9);

    std::cout << "PASS: 03_raw_pointers_and_references" << std::endl;
    return 0;
}
