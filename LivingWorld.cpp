#include <iostream>
#include "headers/Position.hpp"
#include "headers/World.hpp"
#include "headers/Organisms.hpp"

void DandelionCopyTest(Dandelion dan) {
	std::cout<<dan.toString()<<std::endl;
	for (auto& anc : dan.getAncestors())
		std::cout << "Birth: " << anc.birthTurn << ", Death: " << anc.deathTurn << std::endl;
}

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
	std::cout << "BEGINNING OF WORLD" << std::endl;
	std::cout<<world->toString()<<std::endl;

	// Printing world after some turns
	std::cout << std::endl << "WORLD AFTER SOME TURNS" << std::endl;
	for(int i = 0; i<6; i++) world->makeTurn();
	std::cout<<world->toString()<<std::endl;
	
	// Checking Ancestors list of organisms
	std::cout << std::endl << "ANCESTORS OF ALL ORGANISMS" << std::endl;
	for (auto org : world->getOrganisms())
		for (auto& anc : org->getAncestors())
			std::cout << "Birth: " << anc.birthTurn << ", Death: " << anc.deathTurn << std::endl;

	// Testing copy constructor
	std::cout << std::endl << "TESTING COPY CONSTRUCTOR" << std::endl;
	for (auto org : world->getOrganisms())
		if (org->getSign() == "D" && org->getAncestors().size() > 0) { 
			DandelionCopyTest(*dynamic_cast<Dandelion*>(org)); 
			break; 
		}


	// Saving world to the file
	world->writeWorld("save");
	delete world;

	// Loading saved world
	World* newWorld = new World(6, 6);
	newWorld->readWorld("save");
	std::cout << std::endl << "LOADED WORLD" << std::endl;
	std::cout<<newWorld->toString()<<std::endl; 

	// Checking Ancestors list of organisms
	std::cout << std::endl << "LOADED WORLD ANCESTORS" << std::endl;
	for (auto org : newWorld->getOrganisms())
		for (auto& anc : org->getAncestors())
			std::cout << "Birth: " << anc.birthTurn << ", Death: " << anc.deathTurn << std::endl;

	delete newWorld;
	// Run simulation of world
	// newWorld->run();

	return EXIT_SUCCESS;
}