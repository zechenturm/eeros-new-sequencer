//
// Created by moritz on 28/11/2019.
//

#include "Sequencer.hpp"
auto Sequencer::exists(const std::string &name) -> bool
{
    return sequences.count(name) > 0;
}