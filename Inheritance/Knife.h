#pragma once
#include "Weapon.h"
#include "MemeFighter.h"

class Knife : public Weapon
{
public:
	Knife()
		:
		Weapon( "knife",2 )
	{}
	virtual int CalculateDamage( const Attributes& attr,Dice& d ) const
	{
		return attr.speed * 3 + d.Roll( 3 );
	}
};