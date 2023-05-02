#include "headers/Plant.h"

Plant::Plant()
: Organism() {};

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, std::string sign) 
: Organism(power, initiative, liveLength, powerToReproduce, sign) {};

Plant::Plant(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign) 
: Organism(pos, power, initiative, liveLength, powerToReproduce, sign) {};

Plant::Plant(Plant const& plant)
: Organism(plant) {
	std::cout<<"Copying Plant object!"<<std::endl;
};

Plant::~Plant(){
	std::cout<<"Destructing Plant object!"<<std::endl;
}

void Plant::reproduce(Organism* otherParent = nullptr)
{
	auto optPos = getPositionForReproduction();
	if(optPos){
		power /= 2;
		auto offspring = createOffspring(optPos.value());
		// Add offspring to the descendants list
		Attach(offspring);
		// Add ancestors info to the offspring
		auto ancestorsCopy = ancestors;
		Ancestor anc{turnOfBirth, -1, this};
		ancestorsCopy.push_back(anc);
		offspring->setAncestors(ancestorsCopy);
		// Add offspring to the world
		descendants.push_back(offspring);
		world->addOrganism(offspring);
	}	
}

void Plant::action()
{
	if(liveLength <= 0) delete this;
	else{
		liveLength--;
		power++;
		if(canReproduce()) reproduce();
	}
}

void Plant::move(Position pos) {}

void Plant::interact(Organism* initator)
{
	initator->move(position);
	delete this;
}

void Plant::serialize(std::fstream& out)
{
	Organism::serialize(out);
}

void Plant::deserialize(std::fstream& in)
{
	Organism::deserialize(in);
}