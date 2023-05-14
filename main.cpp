
#include "Environment.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <memory>
#include "Genetic.hpp"
#include <math.h>
#include <vector>


double fit(double x, double y)
{
    double t = std::pow(1-x, 2) * exp(-1 * pow(x,2) - pow(y+1, 2))
                -(x-pow(x,3) - pow(y,3))*exp(-pow(x,2)-pow(y,2));
                return t;
}

double fit2(double x, double y)
{
    return 5 - pow(x,2) - pow(y-1,2);
}
double fit3(double x, double y)
{
    return (15 - (x+1)*(x-2)-(y+0.5)*(y-0.8))*0.2;
}
double fit4(double x, double y)
{
    return (30 - (x*x)-(y*y))*0.2;
}
double fit5(double x, double y)
{
    //f(x,y)=(30-0.3 (x+3) x (x-2) (x-3)-2 y^(2))*0.1
    return 0.1*(30-0.3*((x+3)*x*(x-2)*(x-3)) - 2*pow(y,2));
}
int main(int argc, char** argv)
{
    Fitness f = fit;
    std::vector<uint32_t> v;
    int mul = 1;
    int cp = 6;
    for(int i = 1; i <= cp;i++)
    {
        v.push_back(mul * i);
    }
    Environment e(10, 0.7, 0.01, 1, f, v);
    e.Run();
    return 0;
}