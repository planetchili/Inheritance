#pragma once
#include <string>
#include <iostream>
#include "Weapon.h"
#include "Dice.h"


struct Attributes
{
	int hp;
	int speed;
	int power;
};

class MemeFighter
{
public:
	const std::string& GetName() const
	{
		return name;
	}
	bool IsAlive() const
	{
		return attr.hp > 0;
	}
	int GetInitiative() const
	{
		return attr.speed + Roll( 2 );
	}
	void Attack( MemeFighter& other ) const
	{
		if( IsAlive() && other.IsAlive() )
		{
			std::cout << name << " attacks " << other.GetName() << " with his " << pWeapon->GetName()
				<< "!" << std::endl;
			ApplyDamageTo( other,pWeapon->CalculateDamage( attr,*d ) );
		}
	}
	virtual void Tick()
	{
		if( IsAlive() )
		{
			const int recovery = Roll();
			std::cout << name << " recovers " << recovery << " HP." << std::endl;
			attr.hp += recovery;
		}
	}
	virtual void SpecialMove( MemeFighter& ) = 0;
	void GiveWeapon( std::shared_ptr<Weapon> pNewWeapon )
	{
		pWeapon = std::move( pNewWeapon );
	}
	std::shared_ptr<Weapon> PilferWeapon()
	{
		return std::move( pWeapon );
	}
	bool HasWeapon() const
	{
		return pWeapon != nullptr;
	}
	const Weapon& GetWeapon() const
	{
		return *pWeapon;
	}
	virtual ~MemeFighter() = default;
protected:
	MemeFighter( const std::string& name,int hp,int speed,int power,std::shared_ptr<Dice> dice,std::shared_ptr<Weapon> pWeapon )
		:
		name( name ),
		attr( { hp,speed,power } ),
		pWeapon( std::move( pWeapon ) ),
		d( std::move( dice ) )
	{
		std::cout << name << " enters the ring!" << std::endl;
	}
	void ApplyDamageTo( MemeFighter& target,int damage ) const
	{
		target.attr.hp -= damage;
		std::cout << target.name << " takes " << damage << " damage." << std::endl;
		if( !target.IsAlive() )
		{
			std::cout << "As the life leaves " << target.name << "'s body, so does the poop." << std::endl;
		}
	}
	int Roll( int nDice = 1 ) const
	{
		return d->Roll( nDice );
	}
protected:
	Attributes attr;
	std::string name;
private:
	std::shared_ptr<Weapon> pWeapon;
	std::shared_ptr<Dice> d;
};

void TakeWeaponIfDead( MemeFighter& taker,MemeFighter& giver )
{
	if( taker.IsAlive() && !giver.IsAlive() && giver.HasWeapon() )
	{
		if( giver.GetWeapon().GetRank() > taker.GetWeapon().GetRank() )
		{
			std::cout << taker.GetName() << " takes the " << giver.GetWeapon().GetName()
				<< " from " << giver.GetName() << "'s still-cooling corpse." << std::endl;
			taker.GiveWeapon( giver.PilferWeapon() );
		}
	}
}

void Engage( MemeFighter& f1,MemeFighter& f2 )
{
	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;
	// determine attack order
	if( p1->GetInitiative() < p2->GetInitiative() )
	{
		std::swap( p1,p2 );
	}
	// execute attacks
	p1->Attack( *p2 );
	TakeWeaponIfDead( *p1,*p2 );
	p2->Attack( *p1 );
	TakeWeaponIfDead( *p2,*p1 );
}

void DoSpecials( MemeFighter& f1,MemeFighter& f2 )
{
	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;
	// determine attack order
	if( p1->GetInitiative() < p2->GetInitiative() )
	{
		std::swap( p1,p2 );
	}
	// execute attacks
	p1->SpecialMove( *p2 );
	TakeWeaponIfDead( *p1,*p2 );
	p2->SpecialMove( *p1 );
	TakeWeaponIfDead( *p2,*p1 );
}