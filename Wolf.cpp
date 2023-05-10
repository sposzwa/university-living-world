#include "headers/Wolf.hpp"

Wolf::Wolf() 
: Animal::Animal(8, 5, 20, 16, "W") {};

Wolf::Wolf(Position pos) 
: Animal::Animal(pos, 8, 5, 20, 16, "W") {};

Wolf::Wolf(Wolf const& wolf)
: Animal(wolf) {};

Wolf::~Wolf() {};

Organism* Wolf::createOffspring(Position pos) {
    return new Wolf(pos);
}
