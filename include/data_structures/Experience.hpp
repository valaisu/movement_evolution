#ifndef EXPERIENCE_HPP
#define EXPERIENCE_HPP

#include <iostream>
#include <vector>


struct Experience
{
    std::vector<float> start_state;
    std::vector<float> end_state;
    std::vector<float> action;
    float reward;

    Experience(
        std::vector<float> start_state,
        std::vector<float> end_state,
        std::vector<float> action,
        float reward
    );
    
    
    ~Experience();
};


#endif