

#include "data_structures/Experience.hpp"


Experience::Experience(
        std::vector<float> start_state, 
        std::vector<float> end_state,
        std::vector<float> action,
        float reward
    ) : start_state(start_state), 
        end_state(end_state),
        action(action), 
        reward(reward) {}

Experience::~Experience(){};

