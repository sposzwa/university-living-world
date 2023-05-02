#include "headers/Dandelion.h"
#include "headers/World.h"

Dandelion::Dandelion() 
: Plant::Plant() {};

Dandelion::Dandelion(Position pos) 
: Plant::Plant(pos, 0, 0, 6, 2, "D") {};

Dandelion::Dandelion(Dandelion const& dandelion)
: Plant(dandelion) {
    std::cout<<"Copying Dandelion object!"<<std::endl;
};

Dandelion::~Dandelion() {};

Organism* Dandelion::createOffspring(Position pos){
    return new Dandelion(pos);
}