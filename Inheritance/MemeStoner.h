#pragma once
#include "MemeFighter.h"


class MemeStoner : public MemeFighter
{
public:
	MemeStoner( const std::string& name,std::shared_ptr<Weapon> pWeapon )
		:
		MemeFighter( name,80,4,10,std::move( pWeapon ) )
	{}
	void SpecialMove( MemeFighter& ) override
	{
		if( IsAlive() )
		{
			if( Roll() > 3 )
			{
				std::cout << GetName() << " smokes the dank sticky icky, becoming " << "Super " << GetName() << std::endl;
				name = "Super " + name;
				attr.speed += 3;
				attr.power = (attr.power * 69) / 42;
				attr.hp += 10;
			}
			else
			{
				std::cout << GetName() << " spaces out." << std::endl;
			}
		}
	}
	~MemeStoner()
	{
		std::cout << "Destroying MemeStoner '" << name << "'!" << std::endl;
	}
};
