#include "matrix.hpp"
#include <catch2/catch.hpp>

using namespace space;
using namespace std;

TEST_CASE("Construct")
{
    Matrix<int> matrix(3, 3);
    REQUIRE(matrix.shape() == vector<unsigned int>{3, 3});
}

TEST_CASE("Construct with initializer list")
{
    Matrix<int> matrix{3, 3};
    REQUIRE(matrix.shape() == vector<unsigned int>{3, 3});
}

TEST_CASE("Construct using list_initialization")
{
    Matrix<int> matrix{{0, 0}, {1, 1}, {2, 2}};
    REQUIRE(matrix.shape() == vector<unsigned int>{3, 2});
}

TEST_CASE("Bracket operator")
{
    Matrix<int> matrix{{0, 0}, {1, 1}, {2, 2}};
    REQUIRE(matrix[0] == vector{0, 0});
    REQUIRE(matrix[1] == vector{1, 1});
    REQUIRE(matrix[2] == vector{2, 2});

    REQUIRE(matrix[0][0] == 0);
    REQUIRE(matrix[1][0] == 1);
    REQUIRE(matrix[2][0] == 2);
}

TEST_CASE("Random access via bracket operator")
{
    Matrix<int> matrix{{0, 0}, {1, 1}, {2, 2}};
    REQUIRE(matrix[{0, 0}] == 0);
    REQUIRE(matrix[{0, 1}] == 0);
    REQUIRE(matrix[{1, 0}] == 1);
    REQUIRE(matrix[{1, 1}] == 1);
    REQUIRE(matrix[{2, 0}] == 2);
    REQUIRE(matrix[{2, 1}] == 2);

    matrix[{0, 1}] = 100;
    matrix[{1, 1}] = 100;
    matrix[{2, 1}] = 100;

    REQUIRE(matrix[{0, 1}] == 100);
    REQUIRE(matrix[{1, 1}] == 100);
    REQUIRE(matrix[{2, 1}] == 100);
}

TEST_CASE("Constructs by assigment")
{
    Matrix<int> m1 = {{1, 1}};
    REQUIRE(m1[{0, 0}] == 1);
    REQUIRE(m1[{0, 1}] == 1);
}

TEST_CASE("operator==")
{
    Matrix<int> m1 = {{1, 1}, {1, 1}};
    Matrix<int> m2 = {{1, 1}, {1, 1}};
    REQUIRE(m1 == m2);
}

TEST_CASE("Static initialize with zeros")
{
    auto m1 = Matrix<int>::zeros(2, 2);
    auto m2 = Matrix<int>::zeros(2, 2);
    REQUIRE(m1 == m2);
}

TEST_CASE("Static initialize with ones")
{
    auto m1 = Matrix<int>::ones(2, 2);
    Matrix<int> m2 = {{1, 1}, {1, 1}};
    REQUIRE(m1 == m2);
}

 TEST_CASE("operator+") {
    Matrix<int> m1 = {{1, 1}};
    Matrix<int> m2 = {{1, 1}};
    Matrix<int> m3 = m1 + m2;

    Matrix<int> expected = {{2, 2}};
    REQUIRE(expected == m3);
}