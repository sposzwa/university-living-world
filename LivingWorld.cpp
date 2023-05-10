#include <iostream>
#include <fstream>
#include "headers/Position.hpp"
#include "headers/World.hpp"
#include "headers/Organisms.hpp"

int main()
{
	// Random generator initialization
	srand(time(0));

	// Creating world object
	World* world = new World(8, 8);

	// Creating some organisms living in this worldd
	//world->addOrganism(new Wolf(Position(0, 0)));
	//world->addOrganism(new Sheep(Position(6, 6)));
	//world->addOrganism(new ToadStool(Position(3, 2)));
	world->addOrganism(new Dandelion(Position(4, 2)));

	// Printing out world
	std::cout<<world->toString()<<std::endl;

	// Printing world after some turns
	for(int i = 0; i<15; i++) world->makeTurn();
	std::cout<<world->toString()<<std::endl;

	auto anc = world->getOrganisms().at(0)->getAncestors();
	for(auto organism : world->getOrganisms()){
		for (auto& ancestor : organism->getAncestors()){
			std::cout<<"B:"<<ancestor.birthTurn<<" "<<"D:"<<ancestor.deathTurn<<std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << world->toString() << std::endl;

	// Saving world to the file
	world->writeWorld("save");
	delete world;

	// Loading saved world
	World* newWorld = new World(6, 6);
	newWorld->readWorld("save");
	std::cout<<newWorld->toString()<<std::endl; 

	// Run simulation of world
	// newWorld->run();

	return 0;
}