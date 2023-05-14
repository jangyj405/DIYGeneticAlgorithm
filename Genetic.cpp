#include "Genetic.hpp"
#include <cstdint>
#include <cstdlib>
#include <limits>

Genetic::Genetic()
{
    auto x = static_cast<uint8_t>(rand() % (std::numeric_limits<uint8_t>::max()));
    auto y = static_cast<uint8_t>(rand() % (std::numeric_limits<uint8_t>::max()));
    
    this->_genes[0] = x;
    this->_genes[1] = y;
}

void Genetic::get_decoded(double &x, double &y)
{
    x = this->_genes[0] * mulX - (kMaxX - kMinX)*0.5;
    y = this->_genes[1] * mulY - (kMaxY - kMinY)*0.5;
}

void Genetic::get_raw(uint8_t &x, uint8_t &y)
{
    x = this->_genes[0];
    y = this->_genes[1];
}

void Genetic::set_raw(uint8_t x, uint8_t y)
{
    this->_genes[0] = x;
    this->_genes[1] = y;
}

void Genetic::set_fitness(double fitness)
{
    this->_fitness = fitness;
}

double Genetic::get_fitness()
{
    return _fitness;
}

std::string Genetic::get_dna_string()
{
    std::string s;
    for(int i = 0; i< 8; i++)
    {
        s+= (_genes[0] << i) & 0x80 ? "1":"0";
    }
    s+= ", ";
    for(int i = 0; i< 8; i++)
    {
        s+= (_genes[1] << i) & 0x80 ? "1":"0";
    }
    return s;
}