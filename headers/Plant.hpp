#pragma once
#include "Organism.hpp"
#include "World.hpp"

class Plant : public Organism
{
protected:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Organism>(*this);
	}

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
};

