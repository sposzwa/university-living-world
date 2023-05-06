#pragma once
#include "Animal.hpp"

class Sheep : public Animal{
public: 
    // Constructors & Destructors
    Sheep();
    Sheep(Position pos);
    Sheep(Sheep const& sheep);
    ~Sheep();

    // Overriden organism methods
    Organism* createOffspring(Position pos) override;
};