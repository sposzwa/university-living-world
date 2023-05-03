#pragma once
#include <vector>
#include <ctime>
#include <iostream>
#include "Organism.h"
#include "ISerializer.h"

class World : public ISerializer
{
private:
	int worldX;
	int worldY;
	int turn = 0;
	const char separator = '_';
	std::vector<Organism*> organisms;
	std::vector<Organism*> queuedToAdd;
	bool isPositionOnWorld(Position pos);

public:
	// Constructors & Destructor
	World();
	World(int worldX, int worldY);
	~World();

	// Basic object functionality
	std::string toString();

	// Getters & Setters
	int getWorldX();
	void setWorldX(int worldX);
	int getWorldY();
	void setWorldY(int worldY);
	int getTurn();
	std::vector<Organism*> getOrganisms();
	void setOrganisms(std::vector<Organism*> newOrganisms);

	// World specific methods
	void addOrganism(Organism *organism);
	void removeOrganism(Organism* organism);
	std::vector<Position> getVectorOfValidMovePosition(Position position);
	std::vector<Position> getVectorOfFreePositionsAround(Position position);
	bool isPositionFree(Position position);
	std::string getOrganismSignFromPosition(int x, int y);
	Organism* getOrganismFromPosition(Position pos);
	void makeTurn();
	void run();
	void queue(Organism* org) {
		queuedToAdd.push_back(org);
	}

	// Serializer interface methods
	virtual void serialize(std::fstream& out) override;
	virtual void deserialize(std::fstream& in) override;

	// Saving & Loading methods
	void writeWorld(std::string fileName);
	void readWorld(std::string fileName);
};