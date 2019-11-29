//
// Created by moritz on 28/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCEHANDLE_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCEHANDLE_HPP

#include <memory>
#include <thread>
#include "Sequence.hpp"

struct SequenceHandle
{
    SequenceHandle():
        sequence(std::make_shared<Sequence>()),
        thread(nullptr) {}

    explicit SequenceHandle(std::shared_ptr<Sequence>  ptr):
            sequence(std::move(ptr)),
            thread(nullptr) {}

    SequenceHandle(const SequenceHandle& old):
            sequence(old.sequence),
            thread(nullptr) {}

    SequenceHandle(SequenceHandle&& old) noexcept:
            sequence(std::move(old.sequence)),
            thread(old.thread)
    {
        old.thread = nullptr;
    }

    auto operator= (const SequenceHandle& rhs) -> SequenceHandle&
    {
        this->sequence = rhs.sequence;
        this->thread = nullptr;
        return *this;
    };

    auto operator= (SequenceHandle&& rhs) noexcept -> SequenceHandle&
    {
        this->sequence = std::move(rhs.sequence);
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
            thread = new std::thread{ [seq] {
                seq->start();
                while (!seq->operator()());
            }};
        }
    }

    std::thread *thread;
    std::shared_ptr<Sequence> sequence;
};

#endif //NEWSEQUENCERPLAYGROUND_SEQUENCEHANDLE_HPP
