#include <fstream>
#include <algorithm>
#include "headers/World.h"
#include "headers/Position.h"
#include "headers/Organisms.h"


World::World()
: worldX(6), worldY(6)
{
	std::cout<<"Creating world object."<<std::endl;
}

World::World(int x, int y)
: worldX(x), worldY(y) 
{
	std::cout<<"Creating world object with parametrized constructor."<<std::endl;
}

World::~World()
{
	std::cout<<"Destroying world object and all Organisms living in it."<<std::endl;
	size_t initialSize = organisms.size();
	for(size_t i = 0; i<initialSize; i++){
		organisms.at(i)->setWorld(nullptr);
		delete organisms.at(i);
	}
}

std::string World::toString()
{
	std::string result = "\nturn: " + std::to_string(getTurn()) + "\n";
	std::string spec;

	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
			spec = getOrganismSignFromPosition(wX, wY);
			if (spec != "")
				result += spec;
			else
				result += separator;
		};
		result += "\n";
	}
	return result;
}

std::string World::getOrganismSignFromPosition(int x, int y)
{	
	for (Organism* org : organisms)
		if (org->getPosition().getX() == x && org->getPosition().getY() == y)
			return org->getSign();
	return "";
}

Organism* World::getOrganismFromPosition(Position pos)
{
	for (Organism* org : organisms)
		if (org->getPosition()==pos)
			return org;
	return nullptr;
}

bool World::isPositionOnWorld(Position pos)
{
	int x = pos.getX(), y = pos.getY();
	return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
	return getOrganismSignFromPosition(position.getX(), position.getY()).empty();
}

int World::getWorldX()
{
	return worldX;
}

void World::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int World::getWorldY()
{
	return worldY;
}

void World::setWorldY(int worldY)
{
	this->worldY = worldY;
}

int World::getTurn()
{
	return turn;
}

std::vector<Organism*> World::getOrganisms()
{
	return organisms;
} 

void World::setOrganisms(std::vector<Organism*> newOrganisms)
{
	organisms = newOrganisms;
}

void World::addOrganism(Organism* organism)
{
	if(isPositionFree(organism->getPosition()) && isPositionOnWorld(organism->getPosition()) && organism->getWorld() == nullptr)
	{
		organism->setTurnOfBirth(turn);
		organism->setWorld(this);
		if(organism->getTurnOfBirth() < 0) organism->setTurnOfBirth(turn);
		size_t orgSize = organisms.size();
		if(orgSize == 0) organisms.push_back(organism);
		else{
			for(int i = 0; i<orgSize; i++){
				if(organisms.at(i)->getInitiative() <= organism->getInitiative()){
					organisms.insert(organisms.begin() + i, organism);
					return;
				}
			}
			organisms.push_back(organism);
		}
	}
}

void World::removeOrganism(Organism* organism)
{
	std::vector<Organism*>::iterator index = std::find(organisms.begin(), organisms.end(), organism);
	if(index!=organisms.end()){
 		organisms.erase(index);
		organism->Notify();
		organism->setWorld(nullptr);
		organism->setTurnOfBirth(-1);
		// Clearing descendats list
		std::vector<IObserver*> des;
		organism->setDescendants(des);
		// Clearing ancestors list
		std::vector<Ancestor> anc;
		organism->setAncestors(anc);
	}
}

std::vector<Position> World::getVectorOfValidMovePosition(Position position)
{
	int pos_x = position.getX(), pos_y = position.getY();
	std::vector<Position> result;
	for(int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			if ((x != 0 || y != 0) && 
				isPositionOnWorld(Position(pos_x + x, pos_y + y))) {
				result.push_back(Position(pos_x + x, pos_y + y));
			}
	return result;
}

std::vector<Position> World::getVectorOfFreePositionsAround(Position position)
{	
	int pos_x = position.getX(), pos_y = position.getY();
	std::vector<Position> result;
	for(int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			if ((x != 0 || y != 0) && 
				isPositionOnWorld(Position(pos_x + x, pos_y + y))) {
				result.push_back(Position(pos_x + x, pos_y + y));
			}
	auto iter = std::remove_if(result.begin(), result.end(),
		[this](Position pos) {return !isPositionFree(pos); });
	result.erase(iter, result.end());
	return result;
}

void World::makeTurn()
{
	size_t initialSize = organisms.size();
	for (size_t i = 0; i<initialSize; i++){
		organisms.at(i)->action();
		if(initialSize > organisms.size()) initialSize = organisms.size();
	}
	turn++;
}

void World::run()
{
	int i = 0;
	srand(time(0));
	do{
		system("cls");
		makeTurn();
		std::cout<<toString()<<std::endl;
		i++;
		system("pause");
	}while(i < 20);
}

void World::serialize(std::fstream& out)
{
	out.write((char*) &worldX, sizeof(int));
	out.write((char*) &worldY, sizeof(int));
	out.write((char*) &turn, sizeof(int));

	int vecSize = organisms.size();
	out.write((char*) &vecSize, sizeof(int));
	for(int i = 0; i<vecSize; i++){
		organisms.at(i) -> serialize(out); 
	}
}

void World::deserialize(std::fstream& in)
{
	int result;
	in.read((char*) &result, sizeof(int));
	worldX = result;
	in.read((char*) &result, sizeof(int));
	worldY = result;	
	in.read((char*) &result, sizeof(int));
	turn = result;
	
	int vecSize;
	in.read((char*) &vecSize, sizeof(int));
	std::vector<Organism*> newOrganisms;
	organisms = newOrganisms;
	for(int i = 0; i<vecSize; i++){
		in.read((char*) &result, sizeof(int));
		int strSize = (int) result;
		std::string sign;
		sign.resize(strSize);
		in.read((char*) sign.data(), strSize);
		Organism* organism;
		if(sign == "W") organism = new Wolf();
		if(sign == "S") organism = new Sheep();
		if(sign == "D") organism = new Dandelion();
		if(sign == "T") organism = new ToadStool();
		if(sign == "G") organism = new Grass();
		organism->deserialize(in);
		addOrganism(organism);
	}
}

void World::writeWorld(std::string fileName)
{
	std::fstream my_file;
	my_file.open(fileName, std::ios::out | std::ios::binary);
	if (my_file.is_open()) {
		serialize(my_file);
		my_file.close();
	}
}

void World::readWorld(std::string fileName)
{
	std::fstream my_file;
	my_file.open(fileName, std::ios::in | std::ios::binary);
	if (my_file.is_open()) {
		deserialize(my_file);
		my_file.close();
	}
}