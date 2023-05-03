#include "headers/Animal.h"

Animal::Animal()
: Organism() {};

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, std::string sign)
: Organism::Organism(power, initiative, liveLength, powerToReproduce, sign) {};

Animal::Animal(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign) 
: Organism::Organism(pos, power, initiative, liveLength, powerToReproduce, sign), lastPosition(pos) {}

Animal::Animal(Animal const& animal)
:Organism(animal) {
	std::cout<<"Copying Animal object!"<<std::endl;
}

Animal::~Animal(){
	std::cout<<"Destructing Animal object!"<<std::endl;
}

Position Animal::getLastPosition()
{
	return lastPosition;
}

void Animal::setLastPosition(Position pos)
{
	lastPosition = pos;
}

void Animal::action()
{
	if(getLiveLength() == 0) delete this;
	else{
		liveLength--;
		power++;
		auto optPos = getPositionForMove();
		if(optPos){
			auto pos = optPos.value();
			world->isPositionFree(pos) ? move(pos) : world->getOrganismFromPosition(pos)->interact(this);	
		}
	}
}

void Animal::reproduce(Organism* otherParent)
{
	auto optPos = getPositionForReproduction();
	if(optPos){
		power /= 2;
		otherParent->setPower(otherParent->getPower() / 2);
		auto offspring = createOffspring(optPos.value());

		// Managing offsprings and ancestors
		Ancestor anc_1{ turnOfBirth, -1, this };
		Ancestor anc_2{ otherParent->getTurnOfBirth(), -1, otherParent };
		auto copyAncestors = ancestors, otherAncestors = otherParent->getAncestors();
		copyAncestors.insert(copyAncestors.end(), otherAncestors.begin(), otherAncestors.end());
		copyAncestors.push_back(anc_1);
		copyAncestors.push_back(anc_2);
		for (auto& ancestor : ancestors) {
			if (ancestor.subject != nullptr) {
				ancestor.subject->Attach(this);
			}
		}

		// Adding organism to the world queue
		world->queue(offspring);
	}
}

void Animal::move(Position newPosition)
{
	lastPosition = position;
	position = newPosition;
}

void Animal::interact(Organism* initiator)
{	
	bool isSameSpecie = (*initiator).getSign() == sign ? true : false;
	if(isSameSpecie && initiator->canReproduce() && canReproduce())
	{
		reproduce(initiator); 
	}else if(!isSameSpecie){
		if(initiator->getPower() >= power){
			initiator->move(position);
			delete this;
		} 
		else delete initiator;
	}
}

void Animal::serialize(std::fstream& out)
{
	Organism::serialize(out);
	int x = lastPosition.getX();
	out.write((char*) &x, sizeof(int));
	int y = lastPosition.getY();
	out.write((char*) &y, sizeof(int));
}

void Animal::deserialize(std::fstream& in)
{
	Organism::deserialize(in);
	int result, x, y;
	in.read((char*) &result, sizeof(int));
	x = (int) result;
	in.read((char*) &result, sizeof(int));
	y = (int) result;
	lastPosition = Position(x, y);
}