//
// Created by moritz on 28/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP

#include <atomic>
#include <utility>
#include <iostream>
#include "SequenceInterface.hpp"

class Sequence {
public:
    enum class State
    {
        idle,
        running,
        done
    };

    Sequence(): sequenceInterface(), state(State::idle) {}

    explicit Sequence( std::unique_ptr<SequenceInterface>  si): sequenceInterface(std::move(si)), state(State::idle) {}

    auto start() -> void
    {
        state = State::running;
    }

    auto operator()() -> bool
    {
        switch (state.load())
        {
            case State::idle:
                std::cout << "idle\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            case State::running:
                if (!sequenceInterface->checkEntryCondition())
                {
                    state = State::done;
                    break;
                }
                sequenceInterface->action();
                if (sequenceInterface->checkExitCondition())
                {
                    state = State::done;
                }
                break;
            case State::done:
                std::cout << "done\n";
                return true;
        }
        return false;
    }
private:
    std::unique_ptr<SequenceInterface> sequenceInterface;
    std::atomic<State> state;
};


#endif //NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP
