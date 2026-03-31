#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

// Function template: same logic reused for multiple types.
// Tradeoff: can increase code size because each used type instantiates code.
template <typename T>
T ClampValue(T value, T low, T high) {
    assert(low <= high);

    if (value < low) {
        return low;
    }

    if (value > high) {
        return high;
    }

    return value;
}

// Class template: compile-time sized ring buffer.
//
// For embedded systems, this pattern is useful because capacity is fixed and
// memory footprint is known at compile time.
template <typename T, std::size_t Capacity>
class RingBuffer {
public:
    static_assert(Capacity > 0U, "RingBuffer capacity must be greater than zero");

    RingBuffer()
        : head_(0U)
        , tail_(0U)
        , count_(0U) {}

    bool Push(const T& value) {
        if (count_ == Capacity) {
            return false;
        }

        data_[head_] = value;
        head_ = (head_ + 1U) % Capacity;
        ++count_;
        return true;
    }

    bool Pop(T& out_value) {
        if (count_ == 0U) {
            return false;
        }

        out_value = data_[tail_];
        tail_ = (tail_ + 1U) % Capacity;
        --count_;
        return true;
    }

    std::size_t Size() const {
        return count_;
    }

private:
    std::array<T, Capacity> data_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
};

int main() {
    int clamped_int = ClampValue<int>(15, 0, 10);
    double clamped_double = ClampValue<double>(-1.5, -1.0, 1.0);

    assert(clamped_int == 10);
    assert(clamped_double == -1.0);

    RingBuffer<int, 3> queue;
    assert(queue.Size() == 0U);

    assert(queue.Push(10));
    assert(queue.Push(20));
    assert(queue.Push(30));
    assert(!queue.Push(40));
    assert(queue.Size() == 3U);

    int out = 0;
    assert(queue.Pop(out));
    assert(out == 10);
    assert(queue.Pop(out));
    assert(out == 20);
    assert(queue.Pop(out));
    assert(out == 30);
    assert(!queue.Pop(out));

    std::cout << "PASS: 07_templates_function_class" << std::endl;
    return 0;
}
