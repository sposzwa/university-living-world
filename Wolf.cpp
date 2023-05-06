#include "headers/Wolf.hpp"

Wolf::Wolf() 
: Animal::Animal(8, 5, 20, 16, "W") {};

Wolf::Wolf(Position pos) 
: Animal::Animal(pos, 8, 5, 20, 16, "W") {};

Wolf::Wolf(Wolf const& wolf)
: Animal(wolf){
    std::cout<<"Copying Wolf object!"<<std::endl;
}

Wolf::~Wolf(){  
    std::cout<<"Destructing Wolf object!"<<std::endl;  
}

Organism* Wolf::createOffspring(Position pos){
    return new Wolf(pos);
}
