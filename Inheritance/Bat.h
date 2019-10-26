#pragma once
#include "Weapon.h"
#include "MemeFighter.h"

class Bat : public Weapon
{
public:
	Bat()
		:
		Weapon( "bat",1 )
	{}
	virtual int CalculateDamage( const Attributes& attr,Dice& d ) const
	{
		return attr.power * 2 + d.Roll( 1 );
	}
};