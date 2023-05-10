#include "headers/ToadStool.hpp"

ToadStool::ToadStool() 
: Plant::Plant(0, 0, 12, 4, "T") {};

ToadStool::ToadStool(Position pos) 
: Plant::Plant(pos, 0, 0, 12, 4, "T") {};

ToadStool::ToadStool(ToadStool const& toadStool)
: Plant(toadStool) {};

ToadStool::~ToadStool() {};

void ToadStool::interact(Organism* initiator) {
    delete initiator;
    delete this;
}

Organism* ToadStool::createOffspring(Position pos) {
    return new ToadStool(pos);
}
