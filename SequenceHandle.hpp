//
// Created by moritz on 28/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCEHANDLE_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCEHANDLE_HPP

#include <memory>
#include <thread>
#include "Sequence.hpp"
#include "SequenceController.hpp"
#include <iostream>

struct SequenceHandle
{
    SequenceHandle():
        sequence(std::make_shared<Sequence>()),
        controller(std::make_shared<SequenceController>()),
        thread(nullptr) {}

    explicit SequenceHandle(std::shared_ptr<Sequence>  ptr):
            sequence(std::move(ptr)),
            controller(std::make_shared<SequenceController>()),
            thread(nullptr) {}

    SequenceHandle(const SequenceHandle& old):
            sequence(old.sequence),
            controller(old.controller),
            thread(nullptr) {}

    SequenceHandle(SequenceHandle&& old) noexcept:
            sequence(std::move(old.sequence)),
            controller(std::move(old.controller)),
            thread(old.thread)
    {
        old.thread = nullptr;
    }

    auto operator= (const SequenceHandle& rhs) -> SequenceHandle&
    {
        this->sequence = rhs.sequence;
        this->controller = rhs.controller;
        this->thread = nullptr;
        return *this;
    };

    auto operator= (SequenceHandle&& rhs) noexcept -> SequenceHandle&
    {
        this->sequence = std::move(rhs.sequence);
        this->controller = std::move(rhs.controller);
        this->thread = rhs.thread;
        rhs.thread = nullptr;
        return *this;
    }


    ~SequenceHandle()
    {
        if (thread != nullptr)
        {
            thread->join();
            delete(thread);
        }
    }

    auto start() -> void
    {
        using State = SequenceController::State;
        if (thread == nullptr)
        {
            auto seq = this->sequence;
            auto ctlr = this->controller;
            thread = new std::thread{ [seq, ctlr] {
                runSequence(seq, ctlr);
            }};
        }
    }

    static auto runSequence(const std::shared_ptr<Sequence>& seq, const std::shared_ptr<SequenceController>& controller) -> void
    {
        controller->state = SequenceController::State::running;
        while (controller->state != SequenceController::State::done)
            switch (controller->state.load())
            {
                case SequenceController::State::idle:
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    break;
                case SequenceController::State::running:
                    if (!seq->checkEntryCondition())
                    {
                        controller->state = SequenceController::State::done;
                        break;
                    }
                    seq->action();
                    if (seq->checkExitCondition())
                    {
                        controller->state = SequenceController::State::done;
                    }
                    break;
            }
    };

    std::thread *thread;
    std::shared_ptr<Sequence> sequence;
    std::shared_ptr<SequenceController> controller;
};

#endif //NEWSEQUENCERPLAYGROUND_SEQUENCEHANDLE_HPP
