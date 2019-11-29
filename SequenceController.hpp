//
// Created by moritz on 29/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCECONTROLLER_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCECONTROLLER_HPP

#include <atomic>

class SequenceController
{
public:
    enum class State
    {
        idle,
        running,
        done
    };

    std::atomic<State> state;
};

#endif //NEWSEQUENCERPLAYGROUND_SEQUENCECONTROLLER_HPP
