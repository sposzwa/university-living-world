#pragma once
#include "Organism.h"
#include "World.h"

class Plant : public Organism
{
	public:
		// Constructors & Destructor
		Plant();
		Plant(int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
		Plant(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
		Plant(Plant const& plant);
		virtual ~Plant();

		// Overriden organism methods
		virtual void action() override;
		virtual void reproduce(Organism* otherParent) override; 
		virtual Organism* createOffspring(Position pos) = 0;
		virtual void move(Position pos) override;
		virtual void interact(Organism* initiator) override;

		// Implementation of serializer methods
		virtual void serialize(std::fstream& out) override;
		virtual void deserialize(std::fstream& in) override;
};

