//
// Created by moritz on 29/11/2019.
//

#ifndef NEWSEQUENCERPLAYGROUND_SEQUENCEINTERFACE_HPP
#define NEWSEQUENCERPLAYGROUND_SEQUENCEINTERFACE_HPP

class SequenceInterface {
public:
    virtual void action() {}
    virtual bool checkEntryCondition() { return true; }
    virtual bool checkExitCondition() { return false; }
};

#endif //NEWSEQUENCERPLAYGROUND_SEQUENCEINTERFACE_HPP
