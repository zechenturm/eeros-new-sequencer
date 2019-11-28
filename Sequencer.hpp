//
// Created by moritz on 28/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP

#include <memory>
#include <vector>
#include <map>
#include "Sequence.hpp"

class Sequencer {
public:
    auto exists (const std::string& name) -> bool;

    template <typename SeqType, typename... Args>
    auto constructAndAdd(const std::string& name, Args&&... args) -> std::shared_ptr<SeqType>
    {
        using namespace std;
        auto ptr = make_shared<SeqType>(forward(args)...);
        sequences.emplace(pair<string, decltype(ptr)>{name, ptr});
        return ptr;
    }

private:
    std::map<std::string, std::shared_ptr<Sequence>> sequences;
};


#endif //NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP
