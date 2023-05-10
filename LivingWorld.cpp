#include <iostream>
#include "headers/Position.hpp"
#include "headers/World.hpp"
#include "headers/Organisms.hpp"

int main()
{
	// Random generator initialization
	srand(time(0));
	World* world = new World(8, 8);

	// Creating some organisms living in this worldd
	world->addOrganism(new Wolf(Position(0, 0)));
	world->addOrganism(new Sheep(Position(6, 6)));
	world->addOrganism(new ToadStool(Position(3, 2)));
	world->addOrganism(new Grass(Position(1, 1)));
	world->addOrganism(new Dandelion(Position(4, 2)));

	// Printing out world at the begining
	std::cout<<world->toString()<<std::endl;

	// Printing world after some turns
	for(int i = 0; i<6; i++) world->makeTurn();
	std::cout<<world->toString()<<std::endl;
	
	// Checking Ancestors list of organisms
	for (auto org : world->getOrganisms())
		for (auto& anc : org->getAncestors())
			std::cout << "Birth: " << anc.birthTurn << ", Death: " << anc.deathTurn << std::endl;

	// Saving world to the file
	world->writeWorld("save");
	delete world;

	// Loading saved world
	World* newWorld = new World(6, 6);
	newWorld->readWorld("save");
	std::cout<<newWorld->toString()<<std::endl; 

	// Checking Ancestors list of organisms
	for (auto org : newWorld->getOrganisms())
		for (auto& anc : org->getAncestors())
			std::cout << "Birth: " << anc.birthTurn << ", Death: " << anc.deathTurn << std::endl;

	delete newWorld;
	// Run simulation of world
	// newWorld->run();

	return EXIT_SUCCESS;
}