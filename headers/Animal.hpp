#pragma once
#include "Organism.hpp"
#include "World.hpp"

class Animal : public Organism
{
	private:
		Position lastPosition;

	public:
		// Constructors & Destructor
		Animal();
		Animal(int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
		Animal(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
		Animal(Animal const& animal);
		virtual ~Animal();

		// Getters & Setters
		Position getLastPosition();
		void setLastPosition(Position pos);

		// Overriden organism methods
		virtual void action() override;
		virtual void reproduce(Organism* otherParent) override;
		virtual Organism* createOffspring(Position pos) = 0;
		void move(Position pos) override;
		virtual void interact(Organism* initiator) override;
		
		// Implementation of serializer methods
		virtual void serialize(std::fstream& out) override;
		virtual void deserialize(std::fstream& in) override;
};
