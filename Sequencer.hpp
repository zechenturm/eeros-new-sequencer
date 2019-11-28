//
// Created by moritz on 28/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP

#include <memory>
#include <vector>
#include <map>
#include "Sequence.hpp"

using namespace std;

class Sequencer {
public:
    bool exists (const string& name);

    template <typename SeqType, typename... Args>
    auto constructAndAdd(const string& name, Args&&... args) -> shared_ptr<SeqType>
    {
        auto ptr = make_shared<SeqType>(forward(args)...);
        sequences.emplace(pair<string, decltype(ptr)>{name, ptr});
        return ptr;
    }

private:
    map<string, shared_ptr<Sequence>> sequences;
};


#endif //NEWSEQUENCERPLAYGROUND_SEQUENCER_HPP
