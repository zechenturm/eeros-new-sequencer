cmake_minimum_required(VERSION 3.15)
project(newSequencerPlayground)

set(CMAKE_CXX_STANDARD 11)


add_executable(newSequencerPlayground main.cpp Sequencer.cpp Sequencer.hpp Sequence.hpp SequenceHandle.hpp SequenceController.hpp SequenceInterface.hpp)

target_link_libraries(newSequencerPlayground pthread)
