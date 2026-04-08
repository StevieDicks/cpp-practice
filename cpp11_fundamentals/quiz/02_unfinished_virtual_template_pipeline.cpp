#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

// Quiz 02: unfinished function using virtual dispatch + templates.
//
// Current behavior:
// - Program compiles.
// - Runtime assertions fail because ApplyPipeline(...) is a placeholder.
//
// Your task:
// - Implement ApplyPipeline(...) so each filter is applied in order.
// - Keep function generic over container type (template parameter).
// - Do not change main() assertions.
class IFilter {
public:
    virtual ~IFilter() {}
    virtual int Apply(int input) const = 0;
};

class ScaleFilter : public IFilter {
public:
    explicit ScaleFilter(int factor)
        : factor_(factor) {}

    int Apply(int input) const override {
        return input * factor_;
    }

private:
    int factor_;
};

class OffsetFilter : public IFilter {
public:
    explicit OffsetFilter(int offset)
        : offset_(offset) {}

    int Apply(int input) const override {
        return input + offset_;
    }

private:
    int offset_;
};

template <typename FilterContainer>
int ApplyPipeline(const FilterContainer& filters, int input) {
    // TODO:
    // Apply each filter in sequence using virtual dispatch and return final
    // value. This placeholder intentionally returns incorrect behavior.
    (void)filters;
    return input;
}

int main() {
    std::vector<std::shared_ptr<IFilter> > filters;
    filters.push_back(std::make_shared<ScaleFilter>(3));
    filters.push_back(std::make_shared<OffsetFilter>(2));

    // Expected computation after TODO is implemented:
    // ((4 * 3) + 2) == 14
    int out_a = ApplyPipeline(filters, 4);
    assert(out_a == 14);

    // Check another value to avoid hardcoding one input.
    int out_b = ApplyPipeline(filters, 1);
    assert(out_b == 5);

    std::cout << "PASS: 02_unfinished_virtual_template_pipeline" << std::endl;
    return 0;
}
