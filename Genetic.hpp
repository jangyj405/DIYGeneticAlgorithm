#pragma once
#include <cstdint>
#include <limits>
#include <string>
class Genetic
{
    public:
    Genetic();
    ~Genetic(){};
    void get_decoded(double& x, double& y);
    void get_raw(uint8_t& x, uint8_t& y);
    void set_raw(uint8_t x, uint8_t y);
    void set_fitness(double fitness);
    double get_fitness();
    std::string get_dna_string();
    private:
    uint8_t _genes[2] = {0,};
    double _fitness = 0;
    static constexpr double kMaxX = 3.;
    static constexpr double kMinX = -3.;
    static constexpr double kMaxY = 3.;
    static constexpr double kMinY = -3.;
    static constexpr double mulX = (kMaxX - kMinX) / (std::numeric_limits<uint8_t>::max());
    static constexpr double mulY = (kMaxX - kMinY) / (std::numeric_limits<uint8_t>::max());
};