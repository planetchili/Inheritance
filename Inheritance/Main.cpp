#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <algorithm>
#include <memory>

class Dice
{
public:
	int Roll( int nDice )
	{
		int total = 0;
		for( int n = 0; n < nDice; n++ )
		{
			total += d6( rng );
		}
		return total;
	}
private:
	std::uniform_int_distribution<int> d6 = std::uniform_int_distribution<int>( 1,6 );
	std::mt19937 rng = std::mt19937( std::random_device{}() );
};

struct Attributes
{
	int hp;
	int speed;
	int power;
};

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
			ApplyDamageTo( other,pWeapon->CalculateDamage( attr,d ) );
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
	void GiveWeapon( std::unique_ptr<Weapon> pNewWeapon )
	{
		pWeapon = std::move( pNewWeapon );
	}
	std::unique_ptr<Weapon> PilferWeapon()
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
	MemeFighter( const std::string& name,int hp,int speed,int power,std::unique_ptr<Weapon> pWeapon )
		:
		name( name ),
		attr( { hp,speed,power } ),
		pWeapon( std::move( pWeapon ) )
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
		return d.Roll( nDice );
	}
protected:
	Attributes attr;
	std::string name;
private:
	std::unique_ptr<Weapon> pWeapon;
	mutable Dice d;
};

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

class MemeFrog : public MemeFighter
{
public:
	MemeFrog( const std::string& name,std::unique_ptr<Weapon> pWeapon )
		:
		MemeFighter( name,69,7,14,std::move( pWeapon ) )
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

class MemeStoner : public MemeFighter
{
public:
	MemeStoner( const std::string& name,std::unique_ptr<Weapon> pWeapon )
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

int main()
{
	std::vector<std::unique_ptr<MemeFighter>> t1;
	t1.push_back( std::make_unique<MemeFrog>( "Dat Boi",std::make_unique<Fists>() ) );
	t1.push_back( std::make_unique<MemeStoner>( "Good Guy Greg",std::make_unique<Bat>() ) );
	t1.push_back( std::make_unique<MemeFrog>( "the WB Frog",std::make_unique<Knife>() ) );

	std::vector<std::unique_ptr<MemeFighter>> t2;
	t2.push_back( std::make_unique<MemeStoner>( "Chong",std::make_unique<Fists>() ) );
	t2.push_back( std::make_unique<MemeStoner>( "Scumbag Steve",std::make_unique<Bat>() ) );
	t2.push_back( std::make_unique<MemeFrog>( "Pepe",std::make_unique<Knife>() ) );

	const auto alive_pred = []( const std::unique_ptr<MemeFighter>& pf ) { return pf->IsAlive(); };
	while(
		std::any_of( t1.begin(),t1.end(),alive_pred ) &&
		std::any_of( t2.begin(),t2.end(),alive_pred ) )
	{
		std::random_shuffle( t1.begin(),t1.end() );
		std::partition( t1.begin(),t1.end(),alive_pred );
		std::random_shuffle( t2.begin(),t2.end() );
		std::partition( t2.begin(),t2.end(),alive_pred );

		for( size_t i = 0; i < t1.size(); i++ )
		{
			Engage( *t1[i],*t2[i] );
			DoSpecials( *t1[i],*t2[i] );
			std::cout << "------------------------------------" << std::endl;
		}
		std::cout << "=====================================" << std::endl;

		for( size_t i = 0; i < t1.size(); i++ )
		{
			t1[i]->Tick();
			t2[i]->Tick();
		}
		std::cout << "=====================================" << std::endl;

		std::cout << "Press any key to continue...";
		while( !_kbhit() );
		_getch();
		std::cout << std::endl << std::endl;
	}

	if( std::any_of( t1.begin(),t1.end(),alive_pred ) )
	{
		std::cout << "Team ONE is victorious!" << std::endl;
	}
	else
	{
		std::cout << "Team TWO is victorious!" << std::endl;
	}

	while( !_kbhit() );
	return 0;
}