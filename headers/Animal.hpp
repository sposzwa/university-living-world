#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include "Organism.hpp"
#include "World.hpp"

class Animal : public Organism {
protected:
	Position lastPosition;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Organism>(*this);
		ar& lastPosition;
	}
public:
	Animal();
	Animal(int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
	Animal(Position pos, int power, int initiative, int liveLength, int powerToReproduce, std::string sign);
	Animal(Animal const& animal);
	virtual ~Animal();
	Position getLastPosition();
	void setLastPosition(Position pos);
	virtual void action() override;
	virtual void reproduce(Organism* otherParent) override;
	virtual Organism* createOffspring(Position pos) = 0;
	void move(Position pos) override;
	virtual void interact(Organism* initiator) override;
};


