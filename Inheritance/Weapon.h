#pragma once
#include <string>

struct Attributes;
class Dice;

class Weapon
{
public:
	Weapon( const std::string& name,int rank )
		:
		name( name ),
		rank( rank )
	{}
	const std::string& GetName() const
	{
		return name;
	}
	int GetRank() const
	{
		return rank;
	}
	virtual int CalculateDamage( const Attributes& attr,Dice& d ) const = 0;
	virtual ~Weapon() = default;
private:
	std::string name;
	int rank;
};