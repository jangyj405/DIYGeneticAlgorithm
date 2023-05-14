#include "Environment.hpp"

Environment::Environment(int N, double crossover, double mutation, int random_seed, Fitness fit, std::vector<uint32_t> checkpoints)
:_N(N)
,_crossover(crossover)
,_mutation(mutation)
,_fit(fit)
,_v_checkpoints(checkpoints)
{
    srand(random_seed);
    generator.seed(random_seed);
    _v_genes0.resize(_N);
    _v_genes1.resize(_N);
}

void Environment::CrossOver(Genetic &gene0, Genetic &gene1)
{
    bool doCrossOver = (static_cast<double>(rand()) / RAND_MAX) < _crossover;
    if(doCrossOver)
    {
        //1~6
        int cutIndex = rand() % 7 + 1;
        uint8_t x0,y0;
        gene0.get_raw(x0,y0);

        uint8_t x1,y1;
        gene1.get_raw(x1,y1);
        
        uint8_t mask = static_cast<uint8_t>(pow(2, cutIndex)-1); 
        
        uint8_t x0_cut = x0 & ~mask;
        uint8_t x1_cut = x1 & ~mask;
        uint8_t y0_cut = y0 & ~mask;
        uint8_t y1_cut = y1 & ~mask;

        x0 = (x0 & mask) | x1_cut;
        x1 = (x1 & mask) | x0_cut;
        y0 = (y0 & mask) | y1_cut;
        y1 = (y1 & mask) | y0_cut;
        
        gene0.set_raw(x0, y0);
        gene1.set_raw(x1, y1);
    }
    else 
    {
        //children == parents
    }
}

void Environment::Mutation(Genetic &gene)
{
    bool doMutation = static_cast<double>(rand()) / RAND_MAX < _mutation;
    if(doMutation)
    {
        uint8_t x,y;
        gene.get_raw(x, y);
        
        int shift = (rand() % 8);
        uint8_t bitmask = 0x01 << shift;
        x = x ^ bitmask;

        shift = (rand() % 8);
        bitmask = 0x01 << shift;
        y = y ^ bitmask;

        gene.set_raw(x, y);
    }
}
std::vector<Genetic>* Environment::get_old()
{
    return _gen % 2 == 0 ? &_v_genes0 : &_v_genes1;
}
std::vector<Genetic>* Environment::get_new()
{
    return _gen % 2 == 1 ? &_v_genes0 : &_v_genes1;
}
void Environment::Run()
{
    if(0)
    {
        auto old = get_old();
        for(auto iter = old->begin(); iter != old->end(); iter++)
        {
            double x,y;
            iter->get_decoded(x,y);
            std::cout << x << "\t" << y << "\t" << _fit(x,y) << std::endl;
        }
    }
    for(auto cpiter = _v_checkpoints.begin(); cpiter != _v_checkpoints.end(); _gen++)
    {
        auto oldone = get_old();
        auto newone = get_new();
        double sumFitness = 0.;
        
        for(auto iter = oldone->begin(); iter != oldone->end(); iter++)
        {
            double x, y;
            iter->get_decoded(x, y);
            double fit = _fit(x,y);
            iter->set_fitness(fit);
            sumFitness += fit;
        }
        for(auto niter = newone->begin(); niter != newone->end();niter+=2)
        {
            Genetic* pg0;
            Genetic* pg1;
            do 
            {
                //pg0 = Roulette(sumFitness, *oldone);
                //pg1 = Roulette(sumFitness, *oldone);
                pg0 = Tournament( *oldone);
                pg1 = Tournament( *oldone);
            }while (pg0 == pg1);
            
            Genetic g0(*pg0);
            Genetic g1(*pg1);
            CrossOver(g0, g1);
            uint8_t x0,y0,x1,y1;
            g0.get_raw(x0, y0);
            g1.get_raw(x1, y1);

            Mutation(g0);
            Mutation(g1);

            niter->set_raw(x0, y0);
            (niter+1)->set_raw(x1, y1);
        }
        

        if(*cpiter == _gen)
        {
            cpiter++;
            {
                auto old = get_old();
                for (auto iter = old->begin(); iter != old->end(); iter++) {
                    double x, y;
                    iter->get_decoded(x, y);

                    std::cout << x << "\t" << y << "\t" << _fit(x, y) << std::endl;
                    
                    std::cout << "raw : \t" << iter->get_dna_string() << std::endl;                    
                }
                std::cout << std::endl;
            }
        }
    }
    auto old = get_old();
    for(auto iter = old->begin(); iter != old->end(); iter++)
    {
        double x,y;
        iter->get_decoded(x,y);
        std::cout << x << "\t" << y << "\t" << _fit(x,y) << std::endl;
    }
}

Genetic* Environment::Roulette(double sumFitness, std::vector<Genetic>& v_genes)
{
    double sum = sumFitness;
    //double r = rand() % (int)sum;
    std::uniform_real_distribution<double> distribution(0.0, sumFitness);
    double r = distribution(generator);
    for (int i = 0; i < v_genes.size(); i++) 
    {
        r -= v_genes[i].get_fitness();
        if(r < 0)
        {
            return &v_genes[i];
        }
    }
    return &v_genes.back();
}

Genetic* Environment::Tournament(std::vector<Genetic>& v_genes)
{
    std::vector<int> vidx;
    int i;
    std::uniform_int_distribution<int> distribution(0, v_genes.size()-1);
    do {
        //i = rand() % v_genes.size();
        i = distribution(generator);
        if(!std::count(vidx.begin(), vidx.end(), i))
        {
            vidx.push_back(i);
        }
    }while (vidx.size() < 3);
    Genetic* max = &v_genes[vidx[0]];
    for(i = 1; i < vidx.size();i++)
    {
        if(max->get_fitness() < v_genes[vidx[i]].get_fitness())
        {
            max = &v_genes[vidx[i]];
        }
    }
    return max;
}
