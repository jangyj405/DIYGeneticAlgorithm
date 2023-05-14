#pragma once
#include "Genetic.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <random>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <ostream>
#include <string>
#include <iostream>
#include <algorithm>
typedef double (*Fitness)(double x, double y);

class Environment
{
    public:
    Environment()
    :_N(100)
    ,_crossover(0.7)
    ,_mutation(0.001)
    ,_fit(nullptr)
    {

    };
    Environment(int N, double crossover, double mutation, int random_seed, Fitness fit, std::vector<uint32_t> checkpoints);
    ~Environment(){};
    
    void Run();
    private:
    std::default_random_engine generator;
    Genetic* Tournament(std::vector<Genetic>& v_genes);
    Genetic* Roulette(double sumFitness, std::vector<Genetic>& v_genes);
    std::vector<Genetic> _v_genes0;
    std::vector<Genetic> _v_genes1;
    std::vector<Genetic>* get_old();
    std::vector<Genetic>* get_new();
    std::vector<uint32_t> _v_checkpoints;
    void CrossOver(Genetic& gene0, Genetic& gene1);
    void Mutation(Genetic& gene);

    int _N = 0;
    double _crossover = 0.;
    double _mutation = 0.;
    Fitness _fit = nullptr;
    int _gen = 0;
};