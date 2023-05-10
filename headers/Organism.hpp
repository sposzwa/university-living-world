#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <optional>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "Position.hpp"
#include "IObserver.hpp"
#include "ISubject.hpp"

struct Ancestor {
	int birthTurn;
	int deathTurn;
	ISubject* subject;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& birthTurn;
		ar& deathTurn;
		ar& subject;
	}
};

class World;
class Organism : public IObserver, public ISubject {
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
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<IObserver>(*this);
		ar& boost::serialization::base_object<ISubject>(*this);
		ar& power;
		ar& initiative;
		ar& position;
		ar& liveLength;
		ar& powerToReproduce;
		ar& sign;
		ar& turnOfBirth;
		ar& descendants;
		ar& ancestors;
	};

public:
	// Constructors & Destructor & Operators Overload
	Organism();
	Organism(int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
	Organism(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
	Organism(Organism const& organism);
	virtual ~Organism();
	virtual void operator=(Organism const& organism);
		
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
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Organism)