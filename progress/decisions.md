# Decisions Log

## 2026-03-31 - C++11 Fundamentals Sprint workspace

- Added `cpp11_fundamentals/` with one-concept-per-file C++11 exercises for focused learning and incremental review.
- Chose lightweight runtime verification (`assert` + PASS output) to keep feedback immediate without introducing test framework overhead in week 1.
- Used mixed embedded style: Linux-runnable examples with comments on deterministic memory and ownership tradeoffs relevant to MCU targets.
- Prioritized OOP, pointer ownership, and templates first due to one-week schedule and C-to-C++ transition needs.
