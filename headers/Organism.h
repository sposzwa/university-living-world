#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <optional>
#include "Position.h"
#include "IObserver.h"
#include "ISubject.h"
#include "ISerializer.h"

// Ancestor data structure
struct Ancestor{
	int birthTurn;
	int deathTurn;
	ISubject* subject;
};

// Forward declaration of World  class
class World;
class Organism : public IObserver, public ISubject, public ISerializer{
	protected:
		int power;
		int initiative;
		Position position;
		int liveLength;
		int powerToReproduce;
		std::string sign;
		int turnOfBirth = -1;
		World* world = nullptr;
		std::vector<Ancestor> ancestors;
		std::vector<IObserver*> descendants;

	public:
		// Constructors & Destructor
		Organism();
		Organism(int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
		Organism(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
		Organism(Organism const& organism);
		virtual ~Organism();
		
		// Overloading assignment operator
		virtual void operator=(const Organism& organism);
		
		// Basic object functionality
		std::string toString();

		// Getters & Setters
		int getPower();
		void setPower(int power);
		int getInitiative();
		void setInitiative(int initiative);
		Position getPosition();
		void setPosition(Position position);
		int getLiveLength();
		void setLiveLength(int liveLength);
		int getPowerToReproduce();
		void setPowerToReproduce(int powerToReproduce);
		std::string getSign();
		void setSign(std::string sign);
		int getTurnOfBirth();
		void setTurnOfBirth(int turn);
		World* getWorld();
		void setWorld(World* world);
		std::vector<Ancestor> getAncestors();
		void setAncestors(std::vector<Ancestor> anc);
		std::vector<IObserver*> getDescendants();
		void setDescendants(std::vector<IObserver*> des);

		// Organism behaviour methods
		virtual void action() = 0;
		virtual void reproduce(Organism* otherParent) = 0;
		virtual Organism* createOffspring(Position pos) = 0;
		bool canReproduce();
		virtual void move(Position pos) = 0;

		// Methods for interacting with other organisms
		virtual void interact(Organism* initiator) = 0;

		// Methods for interacting with the world
		std::optional<Position> getPositionForReproduction();
		std::optional<Position> getPositionForMove();

		// Subject methods
		virtual void Attach(IObserver* observer) override;
		virtual void Detach(IObserver* observer) override;
		virtual void Notify() override;

		// Observer methods
		virtual void Update(ISubject* subject) override;

		// Serializer methods
		virtual void serialize(std::fstream& out);
		virtual void deserialize(std::fstream& in);
};