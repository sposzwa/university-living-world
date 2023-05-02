#pragma once
#include "Plant.h"

class Dandelion : public Plant {
    public:
        // Constructors & Destructor
        Dandelion();
        Dandelion(Position pos);
        Dandelion(Dandelion const& dandelion);
        ~Dandelion();

        // Overriden organism methods
        Organism* createOffspring(Position pos) override;
};
