//
// Created by moritz on 28/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP

#include <memory>
#include <utility>
#include <vector>
#include <map>
#include <thread>
#include "SequenceHandle.hpp"

class Sequencer {
public:
    auto exists (const std::string& name) -> bool
    {
        return sequences.count(name) > 0;
    }

    template <typename SeqType, typename ... Args>
    auto add(const std::string& name, Args ... args) -> std::shared_ptr<Sequence>
    {
        auto sequencePointer = std::make_shared<Sequence>(std::unique_ptr<SequenceInterface>{new SeqType{std::forward(args)...}});
        sequences.emplace(name, sequencePointer);
        sequences[name].start();
        return sequencePointer;
    }

private:
    std::map<std::string, SequenceHandle> sequences;
};


#endif //NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP
