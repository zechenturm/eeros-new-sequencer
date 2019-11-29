//
// Created by moritz on 28/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP


#include "SequenceController.hpp"

class Sequence {
public:
    virtual void action(std::shared_ptr<SequenceController> controller) {}
};


#endif //NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP
