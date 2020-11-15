#pragma once
#include <functional>
#include "tensor_forward.hpp"

namespace ts {

template<typename Element>
using Fn = std::function<Element(Element)>;

template <typename Element, int Dim>
auto add(Tensor<Element, Dim> const &, Tensor<Element, Dim> const &) -> Tensor<Element, Dim>;

auto add(Matrix const &, Vector const &) -> Matrix ;

auto divide(Matrix const &, Vector const &) -> Matrix ;

template <typename Element, int Dim>
auto maximum(Element, Tensor<Element, Dim> const &) -> Tensor<Element, Dim>;

template <typename Element, int Dim>
auto mask(Tensor<Element, Dim> const &, std::function<bool(Element)>) -> Tensor<bool, Dim>;

template <typename Element, int Dim>
auto assign_if(Tensor<Element, Dim> const &, Tensor<bool, Dim> const &, Element) -> Tensor<Element, Dim>;

template <typename Element, int Dim>
auto apply_if(Tensor<Element, Dim>, Tensor<bool, Dim>, Fn<Element>) -> Tensor<Element, Dim>;

template <typename Element, int Dim>
auto multiply(Tensor<Element, Dim> const &, Element) -> Tensor<Element, Dim>;

auto transpose(Matrix const &) -> Matrix;

template<typename Element, int Dim>
auto sum(Tensor<Element, Dim> const &) -> Element;

auto sum(Matrix const &, int) -> Vector;

auto to_one_hot(Tensor<int, 1> const &) -> Tensor<bool, 2>;

auto get(Matrix const &, Tensor<int, 1> const &) -> Vector;

template <typename Element, int Dim>
auto apply(Tensor<Element, Dim> const &, Fn<Element>) -> Tensor<Element, Dim>;

template <typename Element, int Dim>
auto log(Tensor<Element, Dim> const &) -> Tensor<Element, Dim>;

template <typename Element, int Dim>
auto pow(Tensor<Element, Dim> const &tensor, int) -> Tensor<Element, Dim>;

template <typename Element, int Dim>
auto exp(Tensor<Element, Dim> const &tensor) -> Tensor<Element, Dim>;

template <int Dim>
auto randint(int low, int high, const std::vector<int> &shape) -> Tensor<int, Dim>;

template <typename Element>
auto from_vector(std::vector<Element>) -> Tensor<Element, 1>;

}
