#ifndef DQN_NETWORKS_HPP
#define DQN_NETWORKS_HPP

#include <torch/torch.h>

// Let's just define both Q and T networks in the same class, 
// bc they are quite intertwined


class QTNet : torch::nn::Module {
public:
    QTNet();
    ~QTNet();
    void copy_Q_to_T();
    torch::Tensor forward_Q(torch::Tensor x);
    torch::Tensor forward_T(torch::Tensor x);

private:
    torch::nn::Linear fc1_Q{nullptr};
    torch::nn::Linear fc2_Q{nullptr};
    torch::nn::Linear fc3_Q{nullptr};

    torch::nn::Linear fc1_T{nullptr};
    torch::nn::Linear fc2_T{nullptr};
    torch::nn::Linear fc3_T{nullptr};
};




#endif