#pragma once

#include "exceptions.hpp"
#include <array>
#include <vector>
namespace space {

template <typename Type = float> class Matrix {
  public:
    typedef std::vector<Type> Vector;
    typedef std::vector<int> ShapeVector;

    Vector _data;
    ShapeVector _shape{};

    Matrix(int m, int n)
    {
        _shape = {m, n};
        _data.resize(m * n);
    };
    explicit Matrix(Vector const &data) { _data(data); }

    Matrix(std::initializer_list<Vector> initializer)
    {
        int m = initializer.size();
        int n = -1;

        for (Vector element : initializer) {
            if (n == -1) {
                n = element.size();
            } else if (n != element.size()) {
                throw InvalidShapeException();
            }
            _data.insert(std::end(_data), std::begin(element), std::end(element));
        }
        _shape = {m, n};
    }

    auto operator=(std::initializer_list<Vector> initializer) -> Matrix &
    {
        return this(initializer);
    }

    bool operator==(const Matrix &rhs) const
    {
        return std::tie(_data, _shape) == std::tie(rhs._data, rhs._shape);
    }

    bool operator!=(const Matrix &rhs) const { return !(rhs == *this); }

    auto operator[](int index) -> Vector
    {
        if (index >= _shape[0]) {
            throw IndexOutOfRangeException(index);
        }
        auto begin = std::begin(_data) + (index * _shape[1]);
        auto end = std::begin(_data) + ((index + 1) * _shape[1]);

        return Vector(begin, end);
    }

    auto operator[](std::vector<int> const &position) -> Type &
    {
        auto index = position[0] * _shape[1] + position[1];
        return _data[index];
    }

    [[nodiscard]] auto shape() const -> ShapeVector const & { return _shape; }
};
}; // namespace space