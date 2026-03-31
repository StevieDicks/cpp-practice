#include <cassert>
#include <cstddef>
#include <iostream>

// This class demonstrates RAII (Resource Acquisition Is Initialization).
//
// Resource in this demo: a dynamic int buffer.
// - Acquired in constructor
// - Released in destructor
//
// For embedded systems, heap use can be restricted or banned depending on
// determinism/safety goals. RAII still applies even when resources are not
// heap memory (e.g., mutex, file descriptor, peripheral lock, DMA channel).
class ScopedBuffer {
public:
    explicit ScopedBuffer(std::size_t element_count)
        : element_count_(element_count)
        , data_(new int[element_count_]) {
        ++live_buffers_;

        // Initialize to known value for predictable test behavior.
        for (std::size_t i = 0; i < element_count_; ++i) {
            data_[i] = 0;
        }
    }

    ~ScopedBuffer() {
        delete[] data_;
        data_ = nullptr;
        --live_buffers_;
    }

    // Copy disabled to avoid accidental double-free ownership bugs.
    ScopedBuffer(const ScopedBuffer&) = delete;
    ScopedBuffer& operator=(const ScopedBuffer&) = delete;

    // Move disabled for simplicity in this first RAII example.
    // A production type may define move operations when transfer of ownership
    // is useful and safe for the design.
    ScopedBuffer(ScopedBuffer&&) = delete;
    ScopedBuffer& operator=(ScopedBuffer&&) = delete;

    int& at(std::size_t index) {
        assert(index < element_count_);
        return data_[index];
    }

    std::size_t size() const {
        return element_count_;
    }

    static int live_buffers() {
        return live_buffers_;
    }

private:
    std::size_t element_count_;
    int* data_;

    static int live_buffers_;
};

int ScopedBuffer::live_buffers_ = 0;

static int FillAndSumBuffer() {
    ScopedBuffer buffer(4);

    for (std::size_t i = 0; i < buffer.size(); ++i) {
        buffer.at(i) = static_cast<int>((i + 1U) * 10U);
    }

    int sum = 0;
    for (std::size_t i = 0; i < buffer.size(); ++i) {
        sum += buffer.at(i);
    }

    return sum;
}

int main() {
    assert(ScopedBuffer::live_buffers() == 0);

    int sum = FillAndSumBuffer();
    assert(sum == 100);

    // RAII guarantee: even though buffer was local to FillAndSumBuffer,
    // resource is released when the function exits.
    assert(ScopedBuffer::live_buffers() == 0);

    std::cout << "PASS: 02_constructors_destructors_raii" << std::endl;
    return 0;
}
