#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

// Base class with virtual API. Derived classes specialize behavior.
class OutputDevice {
public:
    virtual ~OutputDevice() {}

    virtual int Apply(int input) const = 0;
    virtual const char* Name() const {
        return "OutputDevice";
    }
};

class ScaleDevice : public OutputDevice {
public:
    explicit ScaleDevice(int factor)
        : factor_(factor) {}

    ~ScaleDevice() {
        ++destructor_calls_;
    }

    int Apply(int input) const override {
        return input * factor_;
    }

    const char* Name() const override {
        return "ScaleDevice";
    }

    static int destructor_calls() {
        return destructor_calls_;
    }

private:
    int factor_;
    static int destructor_calls_;
};

int ScaleDevice::destructor_calls_ = 0;

class ClampDevice : public OutputDevice {
public:
    ClampDevice(int low, int high)
        : low_(low)
        , high_(high) {}

    int Apply(int input) const override {
        if (input < low_) {
            return low_;
        }

        if (input > high_) {
            return high_;
        }

        return input;
    }

    const char* Name() const override {
        return "ClampDevice";
    }

private:
    int low_;
    int high_;
};

static int RunThroughPipeline(const std::vector<OutputDevice*>& devices, int input) {
    int value = input;
    for (std::size_t i = 0; i < devices.size(); ++i) {
        value = devices[i]->Apply(value);
    }
    return value;
}

int main() {
    ScaleDevice scale_by_two(2);
    ClampDevice clamp_to_0_100(0, 100);

    std::vector<OutputDevice*> pipeline;
    pipeline.push_back(&scale_by_two);
    pipeline.push_back(&clamp_to_0_100);

    // Dynamic dispatch: calls resolved based on object type, not pointer type.
    int result_a = RunThroughPipeline(pipeline, 30);
    int result_b = RunThroughPipeline(pipeline, 80);
    int result_c = RunThroughPipeline(pipeline, -9);

    assert(result_a == 60);
    assert(result_b == 100);
    assert(result_c == 0);

    assert(std::string(pipeline[0]->Name()) == "ScaleDevice");
    assert(std::string(pipeline[1]->Name()) == "ClampDevice");

    {
        // This checks that deleting through a base pointer correctly calls
        // derived destructor, which requires a virtual base destructor.
        std::unique_ptr<OutputDevice> owned(new ScaleDevice(3));
        assert(owned->Apply(4) == 12);
    }

    assert(ScaleDevice::destructor_calls() >= 1);

    std::cout << "PASS: 05_virtual_functions_and_polymorphism" << std::endl;
    return 0;
}
