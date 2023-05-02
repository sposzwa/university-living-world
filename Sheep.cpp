#include "headers/Sheep.h"
#include "headers/World.h"

Sheep::Sheep() 
: Animal::Animal() {};

Sheep::Sheep(Position pos) 
: Animal::Animal(pos, 3, 3, 10, 6, "S") {};

Sheep::Sheep(Sheep const& sheep)
: Animal(sheep) {
    std::cout<<"Copying Sheep object!"<<std::endl;
};

Sheep::~Sheep() {};

Organism* Sheep::createOffspring(Position pos){
    return new Sheep(pos);
}