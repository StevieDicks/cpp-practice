# Decisions Log

## 2026-03-31 - C++11 Fundamentals Sprint workspace

- Added `cpp11_fundamentals/` with one-concept-per-file C++11 exercises for focused learning and incremental review.
- Chose lightweight runtime verification (`assert` + PASS output) to keep feedback immediate without introducing test framework overhead in week 1.
- Used mixed embedded style: Linux-runnable examples with comments on deterministic memory and ownership tradeoffs relevant to MCU targets.
- Prioritized OOP, pointer ownership, and templates first due to one-week schedule and C-to-C++ transition needs.

## 2026-04-07 - Added C++11 quiz challenge set

- Added `cpp11_fundamentals/quiz/` with two intentionally non-green challenge programs to practice debugging and implementation, not just feature recall.
- Added Make targets `quiz-build`, `quiz-run`, and `quiz-list` so quizzes can be run separately without breaking the regular `run-all` learning flow.
- Chose one subtle lifetime/ownership bug challenge and one unfinished virtual/template pipeline challenge to reinforce smart pointers, polymorphism, and template usage under realistic failure conditions.
