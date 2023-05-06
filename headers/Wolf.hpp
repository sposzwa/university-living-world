#pragma once
#include "Animal.hpp"

class Wolf : public Animal{
public: 
    // Constructors & Destructors
    Wolf();
    Wolf(Position pos);
    Wolf(Wolf const& wolf);
    ~Wolf();

    // Overriden organism methods
    Organism* createOffspring(Position pos) override;
};