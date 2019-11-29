#include <iostream>
#include "Sequencer.hpp"

class MySequence: public Sequence
{
public:
    std::string text = "hello";
    void action(std::shared_ptr<SequenceController> controller) override
    {
        std::cout << "hello from action\n";
        controller->state = SequenceController::State::stopped;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto s = Sequencer{};
    auto mySequence = s.constructAndAdd<MySequence>("test");
    std::cout << s.exists("test") << '\n';
    std::cout << s.exists("test2") << '\n';
    std::cout << mySequence->text << '\n';
    return 0;
}