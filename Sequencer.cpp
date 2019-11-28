//
// Created by moritz on 28/11/2019.
//

#include "Sequencer.hpp"
bool Sequencer::exists(const std::string &name)
{
    return sequences.count(name) > 0;
}