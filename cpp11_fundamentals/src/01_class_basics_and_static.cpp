#include <cassert>
#include <iostream>

// This class models a simple object with per-instance state (id_) and shared
// class-wide state (live_count_, total_constructed_, next_id_).
//
// Key learning goal:
// - Instance members belong to each object.
// - static members belong to the class itself and are shared by all instances.
class DeviceCounter {
public:
    // Constructor allocates a unique id and updates shared counters.
    DeviceCounter()
        : id_(next_id_) {
        ++next_id_;
        ++live_count_;
        ++total_constructed_;
    }

    // Destructor updates only the "live" count.
    // total_constructed_ intentionally keeps historical total.
    ~DeviceCounter() {
        --live_count_;
    }

    int id() const {
        return id_;
    }

    // static accessor functions are convenient for reading static state.
    static int live_count() {
        return live_count_;
    }

    static int total_constructed() {
        return total_constructed_;
    }

private:
    int id_; // Per-object state: each instance gets a different id.

    // Class-wide shared state.
    static int live_count_;
    static int total_constructed_;
    static int next_id_;
};

// Static data members must be defined exactly once in a .cpp file.
int DeviceCounter::live_count_ = 0;
int DeviceCounter::total_constructed_ = 0;
int DeviceCounter::next_id_ = 1;

int main() {
    assert(DeviceCounter::live_count() == 0);
    assert(DeviceCounter::total_constructed() == 0);

    {
        DeviceCounter first;
        DeviceCounter second;

        // Different objects should not share instance state.
        assert(first.id() != second.id());

        // Static counter is shared across all instances.
        assert(DeviceCounter::live_count() == 2);
        assert(DeviceCounter::total_constructed() == 2);
    }

    // Both objects are now out of scope; destructor calls reduced live_count_.
    assert(DeviceCounter::live_count() == 0);

    DeviceCounter third;
    assert(third.id() == 3);
    assert(DeviceCounter::live_count() == 1);
    assert(DeviceCounter::total_constructed() == 3);

    std::cout << "PASS: 01_class_basics_and_static" << std::endl;
    return 0;
}
