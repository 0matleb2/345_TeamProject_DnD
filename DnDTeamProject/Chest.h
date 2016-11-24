#pragma once
#include "ItemContainer.h"



class Chest : public ItemContainer {

public:

	Chest();
	Chest(int x, int y, int capacity = 9);
	~Chest();

	int getX();
	int getY();

	void setX(int x);
	void setY(int y);

	std::string toString();

	bool operator==(const Chest& chest) const;

private:

	int _x;
	int _y;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<ItemContainer>(*this);
		ar & _x;
		ar & _y;
	}
};

