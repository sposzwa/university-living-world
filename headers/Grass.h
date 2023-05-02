#pragma once
#include "Plant.h"

class Grass : public Plant {
    public: 
        // Constructors & Destructor
        Grass();
        Grass(Position pos);
        Grass(Grass const& grass);
        ~Grass();

        // Overriden organism methods
        Organism* createOffspring(Position pos) override;
};