#include "headers/Sheep.hpp"

Sheep::Sheep() 
: Animal::Animal(3, 3, 10, 6, "S") {};

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