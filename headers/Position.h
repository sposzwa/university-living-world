#pragma once
#include <string>

class Position {
private:
	int x;
	int y;

public:
	// Constructors
	Position();
	Position(int x, int y);

	// Getters & Setters
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);

	// Basic object functionality
	std::string toString();

	// Position specific methods
	double distance(Position position);
	void move(int dx, int dy);
};
