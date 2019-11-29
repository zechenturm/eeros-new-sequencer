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

private:
    std::atomic<State> state;
    friend class SequenceHandle;
};

#endif //NEWSEQUENCERPLAYGROUND_SEQUENCECONTROLLER_HPP
