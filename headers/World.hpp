#pragma once
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "Organism.hpp"

class World {
private:
	int worldX;
	int worldY;
	int turn = 0;
	const char separator = '_';
	std::vector<Organism*> organisms;
	std::vector<Organism*> queuedToAdd;
	bool isPositionOnWorld(Position pos);
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& worldX;
		ar& worldY;
		ar& turn;
		ar& organisms;
		ar& queuedToAdd;
	};
public:
	World();
	World(int worldX, int worldY);
	~World();
	std::string toString();
	int getWorldX();
	void setWorldX(int worldX);
	int getWorldY();
	void setWorldY(int worldY);
	int getTurn();
	std::vector<Organism*> getOrganisms();
	void setOrganisms(std::vector<Organism*> newOrganisms);
	void addOrganism(Organism *organism);
	void removeOrganism(Organism* organism);
	std::vector<Position> getVectorOfValidMovePosition(Position position);
	std::vector<Position> getVectorOfFreePositionsAround(Position position);
	bool isPositionFree(Position position);
	std::string getOrganismSignFromPosition(int x, int y);
	Organism* getOrganismFromPosition(Position pos);
	void makeTurn();
	void run();
	void queue(Organism* org);
	void writeWorld(std::string fileName);
	void readWorld(std::string fileName);
};