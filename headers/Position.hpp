#pragma once
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Position {
private:
	int x;
	int y;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& x;
		ar& y;
	};
public:
	Position();
	Position(int x, int y);
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	std::string toString();
	friend bool operator ==(const Position &pos1, const Position &pos2);
	double distance(Position position);
	void move(int dx, int dy);
};
