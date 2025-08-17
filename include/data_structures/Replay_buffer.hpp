#ifndef REPLAY_BUFFER_HPP
#define REPLAY_BUFFER_HPP

#include <iostream>
#include <vector>

#include "Experience.hpp"


class Replay_buffer {
public:
    Replay_buffer(int buffer_size);
    void update_buffer(Experience);
    std::vector<Experience*> sample_buffer(int n);
    
private:
    std::vector<Experience> buffer;
    int buffer_size;
    int buffer_ind; // points to the next free spot
    bool full;
};


#endif