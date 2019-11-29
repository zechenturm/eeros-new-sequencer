//
// Created by moritz on 28/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP


#include "SequenceController.hpp"

class Sequence {
public:
    virtual void action() {}
    virtual bool checkEntryCondition() { return true; }
    virtual bool checkExitCondition() { return false; }
};


#endif //NEWSEQUENCERPLAYGROUND_SEQUENCE_HPP
