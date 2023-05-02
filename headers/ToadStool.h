#pragma once
#include "Plant.h"

class ToadStool : public Plant {
    public: 
        // Constructors & Destructors
        ToadStool();
        ToadStool(Position pos);
        ToadStool(ToadStool const& toadStool);
        ~ToadStool();

        // Overriden organism methods
        void interact(Organism* initiator) override;
        Organism* createOffspring(Position pos) override;
};