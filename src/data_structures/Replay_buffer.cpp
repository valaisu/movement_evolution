

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "data_structures/Experience.hpp"
#include "data_structures/Replay_buffer.hpp"



Replay_buffer::Replay_buffer(int buffer_size) : buffer_size(buffer_size) {
    full = false;
    buffer_ind = 0;
}

void Replay_buffer::update_buffer(Experience exp) {
    buffer[buffer_ind] = exp;
    buffer_ind += 1;
    if (buffer_ind == buffer_size) {
        full = true;
        buffer_ind = 0;
    }
}


std::vector<Experience*> Replay_buffer::sample_buffer(int n) {
    // gen list of len(buffer)
    int max = full ? buffer_size-1 : buffer_ind-1;

    if (max < 0 && n > 0) {
        std::cout<< "Tried to sample from empty buffer" <<std::endl;
        return {};
    }
    if (n >= buffer_size) {
        std::cout<< "Not enough samples in buffer"<<std::endl;
        return {};
    }
    
    std::vector<int> numbers;
    for (int i = 0; i <= max; ++i) {
        numbers.push_back(i);
    }
    
    // shuffle to take first n elements
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);
    
    std::vector<Experience*> exp_pointers;
    for (int i = 0; i < n; i++) {
        exp_pointers.push_back(&buffer[numbers[i]]);
    }
    
    return exp_pointers;
}
