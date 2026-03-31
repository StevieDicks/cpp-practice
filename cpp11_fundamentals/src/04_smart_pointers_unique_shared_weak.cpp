#include <cassert>
#include <iostream>
#include <memory>

// Helper type for tracking object lifetime across ownership examples.
class TrackedObject {
public:
    explicit TrackedObject(int id)
        : id_(id) {
        ++live_count_;
    }

    ~TrackedObject() {
        --live_count_;
    }

    int id() const {
        return id_;
    }

    static int live_count() {
        return live_count_;
    }

private:
    int id_;
    static int live_count_;
};

int TrackedObject::live_count_ = 0;

int main() {
    assert(TrackedObject::live_count() == 0);

    {
        // unique_ptr: single-owner model.
        std::unique_ptr<TrackedObject> owner(new TrackedObject(7));
        assert(owner != nullptr);
        assert(owner->id() == 7);
        assert(TrackedObject::live_count() == 1);

        // Ownership transfer uses std::move.
        std::unique_ptr<TrackedObject> new_owner = std::move(owner);
        assert(owner == nullptr);
        assert(new_owner != nullptr);
        assert(new_owner->id() == 7);
    }

    // Scope exit releases the unique_ptr-owned object.
    assert(TrackedObject::live_count() == 0);

    std::weak_ptr<TrackedObject> observer;
    {
        // make_shared creates object + control block efficiently.
        std::shared_ptr<TrackedObject> shared_a = std::make_shared<TrackedObject>(21);
        assert(shared_a.use_count() == 1);

        std::shared_ptr<TrackedObject> shared_b = shared_a;
        assert(shared_a.use_count() == 2);
        assert(shared_b.use_count() == 2);

        observer = shared_a;
        assert(!observer.expired());

        // weak_ptr::lock gives temporary shared ownership if still alive.
        // We keep this in its own scope so ref-count checks below remain clear.
        {
            std::shared_ptr<TrackedObject> locked = observer.lock();
            assert(locked != nullptr);
            assert(locked->id() == 21);
        }

        shared_a.reset();
        assert(shared_b.use_count() == 1);
        assert(!observer.expired());

        shared_b.reset();
        assert(observer.expired());
    }

    assert(TrackedObject::live_count() == 0);

    std::cout << "PASS: 04_smart_pointers_unique_shared_weak" << std::endl;
    return 0;
}
