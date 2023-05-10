#include <fstream>
#include <algorithm>
#include "headers/World.hpp"
#include "headers/Position.hpp"
#include "headers/Organisms.hpp"


World::World()
	: worldX(6), worldY(6) {};

World::World(int x, int y)
	: worldX(x), worldY(y) {};

World::~World() {
	size_t initialSize = organisms.size();
	for(size_t i = 0; i<initialSize; i++){
		organisms.at(i)->setWorld(nullptr);
		delete organisms.at(i);
	}
}

std::string World::toString(){
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

std::string World::getOrganismSignFromPosition(int x, int y){	
	for (Organism* org : organisms)
		if (org->getPosition().getX() == x && org->getPosition().getY() == y)
			return org->getSign();
	return "";
}

Organism* World::getOrganismFromPosition(Position pos){
	for (Organism* org : organisms)
		if (org->getPosition()==pos)
			return org;
	return nullptr;
}

bool World::isPositionOnWorld(Position pos){
	int x = pos.getX(), y = pos.getY();
	return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
	return getOrganismSignFromPosition(position.getX(), position.getY()).empty();
}

int World::getWorldX(){
	return worldX;
}

void World::setWorldX(int worldX){
	this->worldX = worldX;
}

int World::getWorldY(){
	return worldY;
}

void World::setWorldY(int worldY){
	this->worldY = worldY;
}

int World::getTurn() {
	return this->turn;
}

std::vector<Organism*> World::getOrganisms(){
	return organisms;
} 

void World::setOrganisms(std::vector<Organism*> newOrganisms){
	organisms = newOrganisms;
}

void World::addOrganism(Organism* organism){
	if(isPositionFree(organism->getPosition()) && isPositionOnWorld(organism->getPosition()) && organism->getWorld() == nullptr){
		organism->setWorld(this);
		if(organism->getTurnOfBirth() < 0) organism->setTurnOfBirth(turn);
		size_t orgSize = organisms.size();
		if(orgSize == 0) organisms.push_back(organism);
		else{
			for(size_t i = 0; i<orgSize; i++){
				if(organisms.at(i)->getInitiative() <= organism->getInitiative()){
					organisms.insert(organisms.begin() + i, organism);
					return;
				}
			}
			organisms.push_back(organism);
		}
	}
}

void World::removeOrganism(Organism* organism){
	std::vector<Organism*>::iterator index = std::find(organisms.begin(), organisms.end(), organism);
	if(index!=organisms.end()){
 		organisms.erase(index);
		organism->Notify();
		organism->setWorld(nullptr);
		organism->setTurnOfBirth(-1);
		organism->setDescendants(std::vector<IObserver*>());
		organism->setAncestors(std::vector<Ancestor>());
	}
}

std::vector<Position> World::getVectorOfValidMovePosition(Position position){
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

std::vector<Position> World::getVectorOfFreePositionsAround(Position position){	
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

void World::makeTurn(){
	size_t initialSize = organisms.size();
	for (size_t i = 0; i<initialSize; i++){
		organisms.at(i)->action();
		if (initialSize > organisms.size()) {
			initialSize = organisms.size();
			i--;
		}
	}
	for (auto org : queuedToAdd) addOrganism(org);
	queuedToAdd.clear();
	turn++;
}

void World::run(){
	int i = 0;
	do{
		system("cls");
		makeTurn();
		std::cout<<toString()<<std::endl;
		i++;
		system("pause");
	}while(i < 20);
}

void World::queue(Organism* org){
	queuedToAdd.push_back(org);
}

void World::writeWorld(std::string fileName){
	std::ofstream ofs(fileName);
	boost::archive::text_oarchive outArchive(ofs);
	outArchive.register_type<Wolf>();
	outArchive.register_type<Sheep>();
	outArchive.register_type<Dandelion>();
	outArchive.register_type<Grass>();
	outArchive.register_type<ToadStool>();
	outArchive << worldX;
	outArchive << worldY;
	outArchive << turn;
	outArchive << organisms;
	outArchive << queuedToAdd;
}

void World::readWorld(std::string fileName){
	std::ifstream ifs(fileName);
    boost::archive::text_iarchive inArchive(ifs);
	inArchive.register_type<Wolf>();
	inArchive.register_type<Sheep>();
	inArchive.register_type<Dandelion>();
	inArchive.register_type<Grass>();
	inArchive.register_type<ToadStool>();
	inArchive >> worldX;
	inArchive >> worldY;
	inArchive >> turn;
	inArchive >> organisms;
	inArchive >> queuedToAdd;
}