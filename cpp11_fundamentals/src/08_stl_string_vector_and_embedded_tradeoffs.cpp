#include <cassert>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

struct Sample {
    std::string label;
    int value;
};

static int AverageRoundedDown(const std::vector<int>& values) {
    assert(!values.empty());

    int total = std::accumulate(values.begin(), values.end(), 0);
    return total / static_cast<int>(values.size());
}

int main() {
    // std::string is safer than C strings for many tasks, but it may allocate.
    // In hard real-time paths, heap behavior may require tighter control.
    std::string status = "TEMP";
    status += "_OK";
    assert(status == "TEMP_OK");

    // reserve() helps avoid repeated reallocations while pushing elements.
    std::vector<int> readings;
    readings.reserve(4);
    readings.push_back(12);
    readings.push_back(15);
    readings.push_back(18);
    readings.push_back(21);

    assert(readings.size() == 4U);
    assert(readings[0] == 12);
    assert(readings[3] == 21);

    int average = AverageRoundedDown(readings);
    assert(average == 16);

    std::vector<Sample> tagged;
    tagged.push_back(Sample{ "sensor_a", 100 });
    tagged.push_back(Sample{ "sensor_b", 90 });

    int tagged_sum = 0;
    for (std::size_t i = 0; i < tagged.size(); ++i) {
        tagged_sum += tagged[i].value;
    }
    assert(tagged_sum == 190);

    // Embedded tradeoff note:
    // vector/string are excellent tools but may be replaced by fixed-capacity
    // containers in safety-critical paths that forbid runtime heap allocation.

    std::cout << "PASS: 08_stl_string_vector_and_embedded_tradeoffs" << std::endl;
    return 0;
}
