#pragma once
#include "MemeFighter.h"

class MemeFrog : public MemeFighter
{
public:
	MemeFrog( const std::string& name,std::shared_ptr<Dice> dice,std::shared_ptr<Weapon> pWeapon )
		:
		MemeFighter( name,69,7,14,std::move( dice ),std::move( pWeapon ) )
	{}
	void SpecialMove( MemeFighter& other ) override
	{
		if( IsAlive() && other.IsAlive() )
		{
			if( Roll() > 4 )
			{
				std::cout << GetName() << " attacks " << other.GetName() << " with a rainbow beam!" << std::endl;
				ApplyDamageTo( other,Roll( 3 ) + 20 );
			}
			else
			{
				std::cout << GetName() << " falls off his unicycle." << std::endl;
			}
		}
	}
	void Tick() override
	{
		if( IsAlive() )
		{
			std::cout << GetName() << " is hurt by the bad AIDS!" << std::endl;
			ApplyDamageTo( *this,Roll() );
			MemeFighter::Tick();
		}
	}
	~MemeFrog()
	{
		std::cout << "Destroying MemeFrog '" << name << "'!" << std::endl;
	}
};