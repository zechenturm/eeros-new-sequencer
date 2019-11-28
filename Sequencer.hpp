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
    auto exists (const std::string& name) -> bool;

    template <typename SeqType, typename... Args>
    auto constructAndAdd(const std::string& name, Args&&... args) -> std::shared_ptr<SeqType>
    {
        using namespace std;
        auto ptr = make_shared<SeqType>(forward(args)...);
        auto handle =SequenceHandle{ptr};
        sequences[name] = move(handle);
        sequences[name].start();
        return ptr;
    }

private:
    std::map<std::string, SequenceHandle> sequences;
};


#endif //NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP
