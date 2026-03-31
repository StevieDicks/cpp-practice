CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -O0 -g3

SRC_DIR := src
BUILD_DIR := bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
EXERCISES := $(patsubst $(SRC_DIR)/%.cpp,%,$(SOURCES))
BINARIES := $(addprefix $(BUILD_DIR)/,$(EXERCISES))

.PHONY: all build run run-all clean list

all: build

build: $(BINARIES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
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

list:
	@for ex in $(EXERCISES); do echo $$ex; done

clean:
	rm -rf $(BUILD_DIR)
