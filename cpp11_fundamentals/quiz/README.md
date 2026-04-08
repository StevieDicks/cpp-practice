# C++11 Quiz Challenges

These quizzes are intentionally not "green" by default.
Each file is a mini debugging/implementation exercise that targets the same concepts as `src/`.

## Implemented Challenges

1. `01_buggy_shared_ptr_cycle.cpp`
- Type: subtle runtime bug.
- Concepts: `shared_ptr`, `weak_ptr`, ownership cycles, destructor/lifetime behavior.
- Current behavior: compiles, then fails an assertion at runtime because objects never release.
- Goal: break the cycle without introducing raw ownership hazards.

2. `02_unfinished_virtual_template_pipeline.cpp`
- Type: unfinished implementation.
- Concepts: virtual dispatch, `shared_ptr` polymorphism, templates, function correctness.
- Current behavior: compiles, then fails assertions because `ApplyPipeline(...)` is a placeholder.
- Goal: implement the function so the filter chain works correctly.

## Run Commands

From `cpp11_fundamentals/`:

```bash
make quiz-list
make quiz-build
make quiz-run Q=01_buggy_shared_ptr_cycle
make quiz-run Q=02_unfinished_virtual_template_pipeline
```

## Extra Quiz Ideas (not implemented yet)

1. `unique_ptr` ownership transfer bug
- Program occasionally dereferences a moved-from `unique_ptr`.

2. Missing virtual destructor trap
- Deleting through base pointer leaks or misbehaves unless destructor semantics are fixed.

3. Template specialization confusion
- Generic algorithm works for `int` but fails for `float` because of an implicit conversion bug.

4. Embedded-style fixed-capacity queue challenge
- Replace dynamic allocation with compile-time storage while preserving API behavior.
