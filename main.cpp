#include <iostream>
#include "Sequencer.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto s = Sequencer{};
    s.constructAndAdd<Sequence>("test");
    std::cout << s.exists("test2");
    return 0;
}