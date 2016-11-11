//! @file
//! @brief Implementation for the Enchant class
//!
#include <iostream>

#include "Enchant.h"

using namespace std;

//! default constructor
Enchant::Enchant() : type(stats::STR), value(0)
{

}

//! constructor receives type of stat as an enum and value as an int
//! @param type : type of stat affected
//! @param value : bonus value
Enchant::Enchant(stats t, int v) : type(t), value(v)
{

}

//! copy constructor
//! @param orig : original enchant to be copied
Enchant::Enchant(const Enchant& orig) : type(orig.type), value(orig.value)
{


}

//prints out information
void Enchant::print() {
	std::cout << "Enchantment Type: " << type << ", Value: +" << value << endl;
}

//! accessor for stat affected by Enchant
//! @return : type of stat of Enchant
stats Enchant::getType()
{
	return type;
}

//! accessor for bonus value of Enchant
//! @return : value of bonus
int Enchant::getValue()
{
	return value;
}

//! mutator for type
//! @param nt : new stat type to set
void Enchant::setType(stats nt)
{
	type = nt;
}

//! mutator for bonus value
//! @param nv : new value for Enchant
void Enchant::setValue(int nv)
{
	value = nv;
}

//! destructor
Enchant::~Enchant()
{

}

//! overload for output operator
ostream& operator<<(ostream& op, Enchant e)
{
	op << "Enchantment Type: " << e.getType() << ", Value: +" << e.getValue() << endl;

	return op;
}