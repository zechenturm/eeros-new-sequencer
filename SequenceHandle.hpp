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

    SequenceHandle& operator= (const SequenceHandle& rhs)
    {
        this->sequence = rhs.sequence;
        this->controller = rhs.controller;
        this->thread = nullptr;
        return *this;
    };

    SequenceHandle& operator= (SequenceHandle&& rhs) noexcept
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
        if (thread == nullptr)
        {
            auto seq = this->sequence;
            auto ctlr = this->controller;
            thread = new std::thread{ [seq, ctlr] {
                ctlr->state = SequenceController::State::running;
                while (ctlr->state == SequenceController::State::running)
                    seq->action(ctlr);
            }};
        }
    };

    std::thread *thread;
    std::shared_ptr<Sequence> sequence;
    std::shared_ptr<SequenceController> controller;
};

#endif //NEWSEQUENCERPLAYGROUND_SEQUENCEHANDLE_HPP
