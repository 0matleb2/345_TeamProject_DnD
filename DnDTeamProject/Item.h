#pragma once
#include <string>
#include "boost\serialization\access.hpp"



class Item {

public:

	Item();
	Item(std::string name);
	virtual ~Item();

	std::string getName();


	void setName(std::string);
	virtual std::string toString();

private:
	static int _sNextId;

	const int _id;
	std::string _name;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _name;
	}

};
