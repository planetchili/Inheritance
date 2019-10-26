#pragma once
#include "Weapon.h"
#include "MemeFighter.h"

class Fists : public Weapon
{
public:
	Fists()
		:
		Weapon( "fists",0 )
	{}
	virtual int CalculateDamage( const Attributes& attr,Dice& d ) const
	{
		return attr.power + d.Roll( 2 );
	}
};