#include <torch/torch.h>
#include "brains/DQN_networks.hpp"






QTNet::QTNet(){
    fc1_Q = register_module("fc1", torch::nn::Linear(512, 256));
    fc2_Q = register_module("fc2", torch::nn::Linear(256, 128));
    fc3_Q = register_module("fc3", torch::nn::Linear(128, 64));
    fc1_T = register_module("fc1", torch::nn::Linear(512, 256));
    fc2_T = register_module("fc2", torch::nn::Linear(256, 128));
    fc3_T = register_module("fc3", torch::nn::Linear(128, 64));
}

torch::Tensor QTNet::forward_Q(torch::Tensor x) {
    x = torch::relu(fc1_Q->forward(x));
    x = torch::relu(fc2_Q->forward(x));
    x = fc3_Q->forward(x);
    return x;
}

torch::Tensor QTNet::forward_T(torch::Tensor x) {
    x = torch::relu(fc1_T->forward(x));
    x = torch::relu(fc2_T->forward(x));
    x = fc3_T->forward(x);
    return x;
}

void QTNet::copy_Q_to_T() {
    fc1_T->weight.data().copy_(fc1_Q->weight.data());
    fc1_T->bias.data().copy_(fc1_Q->bias.data());
    fc2_T->weight.data().copy_(fc2_Q->weight.data());
    fc2_T->bias.data().copy_(fc2_Q->bias.data());
    fc3_T->weight.data().copy_(fc3_Q->weight.data());
    fc3_T->bias.data().copy_(fc3_Q->bias.data());
}





