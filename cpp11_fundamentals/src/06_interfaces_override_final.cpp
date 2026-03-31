#include <cassert>
#include <cstdint>
#include <iostream>

// Interface-style class: only pure virtual functions.
// This is a common pattern for hardware abstraction layers.
class IBus {
public:
    virtual ~IBus() {}

    virtual bool Write(std::uint8_t address, std::uint8_t value) = 0;
    virtual bool Read(std::uint8_t address, std::uint8_t& out_value) = 0;
};

// final prevents further inheritance.
// This can protect behavior that must not be altered in downstream classes.
class FakeBus final : public IBus {
public:
    FakeBus()
        : register_address_(0x10U)
        , register_value_(0U) {}

    bool Write(std::uint8_t address, std::uint8_t value) override {
        if (address != register_address_) {
            return false;
        }

        register_value_ = value;
        return true;
    }

    bool Read(std::uint8_t address, std::uint8_t& out_value) override {
        if (address != register_address_) {
            return false;
        }

        out_value = register_value_;
        return true;
    }

private:
    std::uint8_t register_address_;
    std::uint8_t register_value_;
};

// Consumer class depends on interface, not concrete bus implementation.
class RegisterMirror {
public:
    explicit RegisterMirror(IBus& bus)
        : bus_(bus)
        , threshold_register_(0x10U) {}

    bool SetThreshold(std::uint8_t threshold) {
        return bus_.Write(threshold_register_, threshold);
    }

    bool GetThreshold(std::uint8_t& out_threshold) {
        return bus_.Read(threshold_register_, out_threshold);
    }

private:
    IBus& bus_;
    std::uint8_t threshold_register_;
};

class SamplerBase {
public:
    virtual ~SamplerBase() {}

    virtual int Sample() const {
        return 0;
    }
};

class LinearSampler : public SamplerBase {
public:
    LinearSampler(int slope, int offset, int x)
        : slope_(slope)
        , offset_(offset)
        , x_(x) {}

    // override asks compiler to verify an actual override.
    // final blocks derived classes from replacing Sample() again.
    int Sample() const override final {
        return (slope_ * x_) + offset_;
    }

private:
    int slope_;
    int offset_;
    int x_;
};

int main() {
    FakeBus bus;
    RegisterMirror mirror(bus);

    assert(mirror.SetThreshold(42U));

    std::uint8_t threshold = 0U;
    assert(mirror.GetThreshold(threshold));
    assert(threshold == 42U);

    LinearSampler sampler(3, 1, 5);
    SamplerBase& base_ref = sampler;

    // Dynamic dispatch still works because Sample() is virtual.
    assert(base_ref.Sample() == 16);

    std::cout << "PASS: 06_interfaces_override_final" << std::endl;
    return 0;
}
