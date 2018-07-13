#include <iostream>

double computePi(int n)
{
    double sum = 0;
    for (double x = 1.0 / (2.0 * n); x < 1.0; x += 1.0 / n)
    {
       sum += 4.0 / (1.0 + x * x) * (1.0 / n); 
    }   
    return sum;
}

int main()
{
    std::cout << computePi(1000) << std::endl;
}
