#include <cmath>
#include <utility>
#include <iostream>

std::pair<double, double> quadratic(double a, double b, double c)
{
    double x1 = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
    double x2 = (-b - sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
    return std::make_pair(x1, x2);
}

int main()
{
    std::cout << quadratic(1, 4, 3).first << ", " << quadratic(1, 4, 3).second << std::endl; 
}
