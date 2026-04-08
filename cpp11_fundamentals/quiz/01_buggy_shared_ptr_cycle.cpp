#include <cassert>
#include <iostream>
#include <memory>
#include <string>

// Quiz 01: subtle shared_ptr ownership bug.
//
// Current behavior:
// - Compiles and runs.
// - Fails at runtime on final assertion because an ownership cycle prevents
//   destructors from running.
//
// Your task:
// - Keep intent the same (two linked nodes).
// - Fix ownership so both nodes are correctly destroyed after scope exit.
// - Avoid adding raw owning pointers.
class Node {
public:
    explicit Node(const std::string& name)
        : name_(name) {
        ++live_count_;
        std::cout << "Constructed node: " << name_ << std::endl;
    }

    ~Node() {
        --live_count_;
        std::cout << "Destroyed node: " << name_ << std::endl;
    }

    const std::string& name() const {
        return name_;
    }

    static int live_count() {
        return live_count_;
    }

    // BUG source:
    // Using shared ownership in both directions can create a cycle.
    // Consider whether one direction should be non-owning.
    std::shared_ptr<Node> peer;

private:
    std::string name_;
    static int live_count_;
};

int Node::live_count_ = 0;

int main() {
    assert(Node::live_count() == 0);

    {
        std::shared_ptr<Node> node_a = std::make_shared<Node>("A");
        std::shared_ptr<Node> node_b = std::make_shared<Node>("B");

        node_a->peer = node_b;
        node_b->peer = node_a;

        assert(node_a->name() == "A");
        assert(node_b->name() == "B");

        // Each node now has at least two owners due to cyclic links.
        assert(node_a.use_count() >= 2);
        assert(node_b.use_count() >= 2);
    }

    // Expected final state after you fix ownership model:
    // both nodes should be destroyed at scope exit.
    assert(Node::live_count() == 0);

    std::cout << "PASS: 01_buggy_shared_ptr_cycle" << std::endl;
    return 0;
}
