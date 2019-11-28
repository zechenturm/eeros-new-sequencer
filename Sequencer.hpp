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
    bool exists (const std::string& name);

    template <typename SeqType, typename... Args>
    auto constructAndAdd(std::string name, Args&&... args) -> std::shared_ptr<SeqType>
    {
        sequences.emplace(std::pair<std::string, std::shared_ptr<SeqType>>{name, std::shared_ptr<SeqType>(std::forward(args)...)});
    }

private:
    std::map<std::string, std::shared_ptr<Sequence>> sequences;
};


#endif //NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP
