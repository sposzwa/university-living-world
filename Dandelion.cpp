#include "headers/Dandelion.hpp"

Dandelion::Dandelion() 
: Plant::Plant(0, 0, 6, 2, "D") {};

Dandelion::Dandelion(Position pos) 
: Plant::Plant(pos, 0, 0, 6, 2, "D") {};

Dandelion::Dandelion(Dandelion const& dandelion)
: Plant(dandelion) {};

Dandelion::~Dandelion() {};

Organism* Dandelion::createOffspring(Position pos) {
    return new Dandelion(pos);
}