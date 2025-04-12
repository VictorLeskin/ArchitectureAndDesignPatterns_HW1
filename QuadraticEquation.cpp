#include <gtest/gtest.h>

#include <tuple>

class QuadraticEquation
{

    public:
    inline static const double eps = 1.0e-15;

    static std::tuple<int, double, double> solve(double a, double b, double c)
    {
        double D = b * b - 4 * a * c;
        if (D < -eps)
            return std::tuple(0,0,0);

        a *= 2;
        if( D > eps )
        {
            D = sqrt(D);
            return std::tuple(2, (-b - D) / a, (-b + D) / a);
        }
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

TEST_F(test_QuadraticEquation, test_solve_no_roots)
{
    auto res = Test_QuadraticEquation::solve(1, 0, 1);

    EXPECT_EQ(0, std::get<0>(res));
}

TEST_F(test_QuadraticEquation, test_solve_2_roots)
{
    auto res = Test_QuadraticEquation::solve(1, 0, -1);

    EXPECT_EQ(2, std::get<0>(res));
    EXPECT_NEAR(-1, std::get<1>(res), 1.0e-15);
    EXPECT_NEAR( 1, std::get<2>(res), 1.0e-15);

}
