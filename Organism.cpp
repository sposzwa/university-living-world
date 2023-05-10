#include "headers/Organism.hpp"
#include "headers/World.hpp"

Organism::Organism() : power(0), initiative(0), liveLength(0), powerToReproduce(0), sign("X") {};

Organism::Organism(int power, int initiative, int liveLength, int powerToReproduce, std::string sign) 
: power(power), initiative(initiative), liveLength(liveLength), powerToReproduce(powerToReproduce), sign(sign) {};

Organism::Organism(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign) 
: power(power), initiative(initiative), position(pos), liveLength(liveLength), powerToReproduce(powerToReproduce), sign(sign) {};

Organism::~Organism() {
	if(world!=nullptr) {
		Notify();
		world->removeOrganism(this);
	}
};

void Organism::operator=(const Organism& organism) {
	power = organism.power;
	initiative = organism.initiative;
	position = organism.position;
	liveLength = organism.liveLength;
	powerToReproduce = organism.powerToReproduce;
}

Organism::Organism(Organism const& organism)
: Organism(organism.position, organism.power, organism.initiative, organism.liveLength, organism.powerToReproduce, organism.sign) {
	// cout for testing copy constructor in LivingWorld
	std::cout << std::endl <<  "COPYING ORGANISM: " << organism.sign << ", " << organism.position << std::endl;
	for (auto& anc : organism.ancestors)
		std::cout << "Birth: " << anc.birthTurn << ", Death: " << anc.deathTurn << std::endl;
	std::cout << std::endl;

	world = organism.world;
	ancestors = organism.ancestors;
	descendants = organism.descendants;
};

std::string Organism::toString() {
	return "{ sign: " + this->getSign() +  
		", position: " + getPosition().toString() + "}";
}

int Organism::getPower() {
	return power;
}

void Organism::setPower(int power) {
	this->power = power;
}

int Organism::getInitiative() {
	return initiative;
}

void Organism::setInitiative(int initiative) {
	this->initiative = initiative;
}

Position Organism::getPosition() {
	return position;
}

void Organism::setPosition(Position position) {
	this->position = position;
}

int Organism::getLiveLength() {
	return this->liveLength;
}

void Organism::setLiveLength(int liveLength) {
	this->liveLength = liveLength;
}

int Organism::getPowerToReproduce() {
	return this->powerToReproduce;
}

void Organism::setPowerToReproduce(int powerToReproduce) {
	this->powerToReproduce = powerToReproduce;
}

std::string Organism::getSign() {
	return this->sign;
}

void Organism::setSign(std::string sign) {
	this->sign = sign;
}

int Organism::getTurnOfBirth() {
	return turnOfBirth;
}

void Organism::setTurnOfBirth(int turn) {
	turnOfBirth = turn;
}

World* Organism::getWorld() {
	return world;
}

void Organism::setWorld(World* newWorld) {
	world = newWorld; 
}

std::vector<Ancestor> Organism::getAncestors() {
	return ancestors;
}

void Organism::setAncestors(std::vector<Ancestor> anc) {
	ancestors = anc;
}

std::vector<IObserver*> Organism::getDescendants() {
	return descendants;
}

void Organism::setDescendants(std::vector<IObserver*> desc) {
	descendants = desc;
}

bool Organism::canReproduce() {
	return power > powerToReproduce;
}

std::optional<Position> Organism::getPositionForReproduction() {
	auto freePositionAround = world->getVectorOfFreePositionsAround(position);
	if(freePositionAround.empty()) return std::nullopt;
	int randIndex = rand() % freePositionAround.size();
	return freePositionAround[randIndex];
}

std::optional<Position> Organism::getPositionForMove() {
	auto validPostionAround = world->getVectorOfValidMovePosition(position);
	if(validPostionAround.empty()) return std::nullopt;
	int randIndex = rand() % validPostionAround.size();
	return validPostionAround[randIndex];
}

void Organism::Attach(IObserver* observer) {
	descendants.push_back(observer);
}

void Organism::Detach(IObserver* observer) {
	descendants.erase(std::remove(descendants.begin(), descendants.end(), observer), descendants.end());
}

void Organism::Notify() {
	for (auto& descendant : descendants) {
		descendant->Update(this);
	}

	for (auto& ancestor : ancestors) {
		if (ancestor.subject != nullptr) ancestor.subject->Detach(this);
	}
}

void Organism::Update(ISubject* subject) { 
	for (auto& ancestor : ancestors) {
		if (ancestor.subject == subject) {
			ancestor.deathTurn = dynamic_cast<Organism*>(ancestor.subject)->getWorld()->getTurn();
			ancestor.subject = nullptr;
		}
	}
}