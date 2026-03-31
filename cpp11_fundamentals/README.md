# C++11 Fundamentals Sprint (1 Week)

This workspace is a focused practice track for someone with strong C experience and newer C++ experience.
The goal is to build practical fluency with core C++11 features using small, isolated files.

## Study Format

- One concept per source file in `src/`
- Each file has:
  - A focused example
  - Detailed comments that explain intent and tradeoffs
  - Runtime verification with `assert`
  - A `PASS` message when all checks succeed
- Build/run on Linux (WSL2) with `g++`

## Daily Sequence (~1 hour/day)

1. `01_class_basics_and_static.cpp`
2. `02_constructors_destructors_raii.cpp`
3. `03_raw_pointers_and_references.cpp`
4. `04_smart_pointers_unique_shared_weak.cpp`
5. `05_virtual_functions_and_polymorphism.cpp`
6. `06_interfaces_override_final.cpp`
7. `07_templates_function_class.cpp`
8. `08_stl_string_vector_and_embedded_tradeoffs.cpp`

The sequence prioritizes OOP, pointer ownership, and templates first, while still covering essential STL and embedded-minded tradeoffs.

## Build And Run

From `cpp11_fundamentals/`:

```bash
make build
make run EX=04_smart_pointers_unique_shared_weak
make run-all
make clean
```

## Expected Behavior

- `make build` compiles all examples with C++11 and warning flags.
- `make run-all` executes every binary and stops if an assertion fails.
- Each executable prints a clear `PASS: <exercise>` line on success.

## Notes For Embedded Engineers

These exercises run on Linux but include comments on embedded tradeoffs:
- Where dynamic allocation appears and why it might be restricted on MCU targets
- When deterministic memory patterns (e.g., `std::array`) may be preferred
- Why interfaces/RAII/templates still matter even in constrained systems
