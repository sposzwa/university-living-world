#include "headers/Organism.hpp"
#include "headers/World.hpp"

Organism::Organism() {};

Organism::Organism(int power, int initiative, int liveLength, int powerToReproduce, std::string sign) 
: power(power), initiative(initiative), liveLength(liveLength), powerToReproduce(powerToReproduce), sign(sign) {};

Organism::Organism(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign) 
: power(power), initiative(initiative), position(pos), liveLength(liveLength), powerToReproduce(powerToReproduce), sign(sign) {};

Organism::~Organism()
{
	std::cout<<"Destructing Organism object!"<<std::endl;
	if(world!=nullptr){
		Notify();
		world->removeOrganism(this);
	}
};

void Organism::operator=(const Organism& organism)
{
	power = organism.power;
	initiative = organism.initiative;
	liveLength = organism.liveLength;
	powerToReproduce = organism.powerToReproduce;
}

Organism::Organism(Organism const& organism)
: Organism(organism.power, organism.initiative, organism.liveLength, organism.powerToReproduce, organism.sign) {
	std::cout<<"Copying Organism object!"<<std::endl;
}

std::string Organism::toString()
{
	return "{ sign: " + this->getSign() +  
		", position: " + getPosition().toString() + "}";
}

int Organism::getPower()
{
	return power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

int Organism::getInitiative()
{
	return initiative;
}

void Organism::setInitiative(int initiative){
	this->initiative = initiative;
}

Position Organism::getPosition()
{
	return position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

int Organism::getLiveLength()
{
	return this->liveLength;
}

void Organism::setLiveLength(int liveLength)
{
	this->liveLength = liveLength;
}

int Organism::getPowerToReproduce()
{
	return this->powerToReproduce;
}

void Organism::setPowerToReproduce(int powerToReproduce)
{
	this->powerToReproduce = powerToReproduce;
}

std::string Organism::getSign()
{
	return this->sign;
}

void Organism::setSign(std::string sign)
{
	this->sign = sign;
}

int Organism::getTurnOfBirth()
{
	return turnOfBirth;
}

void Organism::setTurnOfBirth(int turn)
{
	turnOfBirth = turn;
}

World* Organism::getWorld()
{
	return world;
}

void Organism::setWorld(World* newWorld)
{
	world = newWorld; 
}

std::vector<Ancestor> Organism::getAncestors()
{
	return ancestors;
}

void Organism::setAncestors(std::vector<Ancestor> anc)
{
	ancestors = anc;
}

std::vector<IObserver*> Organism::getDescendants()
{
	return descendants;
}

void Organism::setDescendants(std::vector<IObserver*> desc)
{
	descendants = desc;
}

bool Organism::canReproduce()
{
	return power > powerToReproduce;
}

std::optional<Position> Organism::getPositionForReproduction()
{
	auto freePositionAround = world->getVectorOfFreePositionsAround(position);
	if(freePositionAround.empty()) return std::nullopt;
	int randIndex = rand() % freePositionAround.size();
	return freePositionAround[randIndex];
}

std::optional<Position> Organism::getPositionForMove()
{
	auto validPostionAround = world->getVectorOfValidMovePosition(position);
	if(validPostionAround.empty()) return std::nullopt;
	int randIndex = rand() % validPostionAround.size();
	return validPostionAround[randIndex];
}

void Organism::Attach(IObserver* observer)
{
	descendants.push_back(observer);
}

void Organism::Detach(IObserver* observer)
{
	descendants.erase(std::remove(descendants.begin(), descendants.end(), observer), descendants.end());
}

void Organism::Notify()
{
	for (auto& descendant : descendants) {
		descendant->Update(this);
	}

	for (auto& ancestor : ancestors) {
		if (ancestor.subject != nullptr) ancestor.subject->Detach(this);
	}
}

void Organism::Update(ISubject* subject)
{ 
	for (auto& ancestor : ancestors) {
		if (ancestor.subject == subject) {
			ancestor.deathTurn = dynamic_cast<Organism*>(ancestor.subject)->getWorld()->getTurn();
			ancestor.subject = nullptr;
		}
	}
}

void Organism::serialize(std::fstream& out)
{
	int strSize = sign.size();
	out.write((char*) &strSize, sizeof(int));
	std::string orgSign = sign;
	out.write((char*) &orgSign[0], strSize);
	int x = position.getX();
	out.write((char*) &x, sizeof(int));
	int y = position.getY();
	out.write((char*) &y, sizeof(int));
	out.write((char*) &power, sizeof(int));
	out.write((char*) &initiative, sizeof(int));
	out.write((char*) &liveLength, sizeof(int));
	out.write((char*) &powerToReproduce, sizeof(int));
	out.write((char*) &turnOfBirth, sizeof(int));
}

void Organism::deserialize(std::fstream& in)
{
	int result, x, y;
	in.read((char*) &result, sizeof(int));
	x = (int) result;
	in.read((char*) &result, sizeof(int));
	y = (int) result;
	this->position = Position(x, y);
	in.read((char*) &result, sizeof(int));
	this->power = (int) result;
	in.read((char*) &result, sizeof(int));
	this->initiative = (int) result;
	in.read((char*) &result, sizeof(int));
	this -> liveLength = (int) result;
	in.read((char*) &result, sizeof(int));
	this -> powerToReproduce = (int) result;
	in.read((char*) &result, sizeof(int));
	this -> turnOfBirth = (int) result;
}