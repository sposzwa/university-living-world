#include "headers/Animal.hpp"

Animal::Animal()
: Organism() {};

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, std::string sign)
: Organism::Organism(power, initiative, liveLength, powerToReproduce, sign) {};

Animal::Animal(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign) 
: Organism::Organism(pos, power, initiative, liveLength, powerToReproduce, sign), lastPosition(pos) {}

Animal::Animal(Animal const& animal)
: Organism(animal) {
	lastPosition = animal.lastPosition;
};

Animal::~Animal() {};

Position Animal::getLastPosition() {
	return lastPosition;
}

void Animal::setLastPosition(Position pos) {
	lastPosition = pos;
}

void Animal::action() {
	if(!liveLength) delete this;
	else{
		liveLength--;
		power++;
		auto optPos = getPositionForMove();
		if(optPos){
			auto &pos = optPos.value();
			world->isPositionFree(pos) ? move(pos) : world->getOrganismFromPosition(pos)->interact(this);	
		}
	}
}

void Animal::reproduce(Organism* otherParent) {
	auto optPos = getPositionForReproduction();
	if(optPos){
		power /= 2;
		otherParent->setPower(otherParent->getPower() / 2);
		auto offspring = createOffspring(optPos.value());
		// Managing offsprings and ancestors
		Ancestor anc_1{ turnOfBirth, -1, this };
		Ancestor anc_2{ otherParent->getTurnOfBirth(), -1, otherParent };
		std::vector<Ancestor> copyAncestors = ancestors, otherAncestors = otherParent->getAncestors();
		copyAncestors.insert(copyAncestors.end(), otherAncestors.begin(), otherAncestors.end());
		copyAncestors.push_back(anc_1);
		copyAncestors.push_back(anc_2);
		for (auto& ancestor : ancestors) {
			if (ancestor.subject != nullptr) {
				ancestor.subject->Attach(this);
			}
		}
		world->queue(offspring);
	}
}

void Animal::move(Position newPosition) {
	lastPosition = position;
	position = newPosition;
}

void Animal::interact(Organism* initiator) {	
	bool isSameSpecie = (*initiator).getSign() == sign ? true : false;
	if(isSameSpecie && initiator->canReproduce() && canReproduce()) reproduce(initiator);	
	else if(!isSameSpecie){
		if(initiator->getPower() >= power){
			initiator->move(position);
			delete this;
		} 
		else delete initiator;
	}
}