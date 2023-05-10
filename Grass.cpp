#include "headers/Grass.hpp"

Grass::Grass() 
: Plant::Plant(0, 0, 6, 3, "G") {};

Grass::Grass(Position pos) 
: Plant::Plant(pos, 0, 0, 6, 3, "G") {};

Grass::Grass(Grass const& grass)
: Plant(grass) {};

Grass::~Grass() {};

Organism* Grass::createOffspring(Position pos) {
    return new Grass(pos);
};
