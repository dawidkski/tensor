#pragma once

#include <tensor/tensor.hpp>
#include <tensor/ops.hpp>

namespace ts {

auto softmax(MatrixF const &logits) -> MatrixF;

}