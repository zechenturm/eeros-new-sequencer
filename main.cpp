#include <iostream>
#include "Sequencer.hpp"

class MySequence: public SequenceInterface
{
public:
    std::string text = "hello";
    int count = 0;
    void action() override
    {
        std::cout << "hello from action\n";
        count++;
    }

    bool checkExitCondition() override
    {
        return count >= 10;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto s = Sequencer{};
    auto mySequence = s.add<MySequence>("test");
    std::cout << s.exists("test") << '\n';
    std::cout << s.exists("test2") << '\n';
//    std::cout << mySequence-> << '\n';
    return 0;
}