CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -O0 -g3

SRC_DIR := src
BUILD_DIR := bin
QUIZ_DIR := quiz
QUIZ_BUILD_DIR := $(BUILD_DIR)/quiz

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
EXERCISES := $(patsubst $(SRC_DIR)/%.cpp,%,$(SOURCES))
BINARIES := $(addprefix $(BUILD_DIR)/,$(EXERCISES))

QUIZ_SOURCES := $(wildcard $(QUIZ_DIR)/*.cpp)
QUIZ_EXERCISES := $(patsubst $(QUIZ_DIR)/%.cpp,%,$(QUIZ_SOURCES))
QUIZ_BINARIES := $(addprefix $(QUIZ_BUILD_DIR)/,$(QUIZ_EXERCISES))

.PHONY: all build run run-all clean list quiz-build quiz-run quiz-list

all: build

build: $(BINARIES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(QUIZ_BUILD_DIR): | $(BUILD_DIR)
	mkdir -p $(QUIZ_BUILD_DIR)

$(QUIZ_BUILD_DIR)/%: $(QUIZ_DIR)/%.cpp | $(QUIZ_BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

run: build
ifndef EX
	$(error Usage: make run EX=04_smart_pointers_unique_shared_weak)
endif
	@echo "Running $(EX)"
	@./$(BUILD_DIR)/$(EX)

run-all: build
	@set -e; \
	for ex in $(EXERCISES); do \
		echo "Running $$ex"; \
		./$(BUILD_DIR)/$$ex; \
	done

quiz-build: $(QUIZ_BINARIES)

quiz-run: quiz-build
ifndef Q
	$(error Usage: make quiz-run Q=01_buggy_shared_ptr_cycle)
endif
	@echo "Running quiz $(Q)"
	@./$(QUIZ_BUILD_DIR)/$(Q)

quiz-list:
	@for ex in $(QUIZ_EXERCISES); do echo $$ex; done

list:
	@for ex in $(EXERCISES); do echo $$ex; done

clean:
	rm -rf $(BUILD_DIR)
