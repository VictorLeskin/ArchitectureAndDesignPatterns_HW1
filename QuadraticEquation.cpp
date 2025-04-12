#include <gtest/gtest.h>

#include <tuple>

class QuadraticEquation
{
    public:
    static std::tuple<int, double, double> solve(double a, double b, double c)
    {
        double D = b * b - 4 * a * c;
        if (D < 0)
            return std::tuple(0,0,0);

        return std::tuple(99, 0, 0);
    }
};

// gTest grouping class
class test_QuadraticEquation : public ::testing::Test
{
public:
    // additional class to access to member of tested class
    class Test_QuadraticEquation : public QuadraticEquation
    {
    public:
        // add here members for free access.
        using QuadraticEquation::QuadraticEquation; // delegate constructors

    };
};

TEST_F(test_QuadraticEquation, test_solve_no_roots )
{
    auto res = Test_QuadraticEquation::solve(1, 0, 1);

    EXPECT_EQ(0, std::get<0>(res));
}


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}