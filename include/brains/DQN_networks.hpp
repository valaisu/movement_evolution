

// Q - netowork

// T -network
/*
#include <torch/torch.h>

// Define a simple neural network
struct QNet : torch::nn::Module {
  QNet() {
    fc1 = register_module("fc1", torch::nn::Linear(512, 256));
    fc2 = register_module("fc2", torch::nn::Linear(256, 128));
    fc3 = register_module("fc2", torch::nn::Linear(128, 64));
  }
  
  torch::Tensor forward(torch::Tensor x) {
    x = torch::relu(fc1->forward(x));
    x = torch::relu(fc2->forward(x));
    x = fc3->forward(x);
    return x;
  }
  
  torch::nn::Linear fc1{nullptr}, fc2{nullptr};
};
*/