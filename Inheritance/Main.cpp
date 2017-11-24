#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <algorithm>

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

class MemeFighter
{
public:
	const std::string& GetName() const
	{
		return name;
	}
	bool IsAlive() const
	{
		return hp > 0;
	}
	int GetInitiative() const
	{
		return speed + Roll( 2 );
	}
	void Punch( MemeFighter& other ) const
	{
		if( IsAlive() && other.IsAlive() )
		{
			std::cout << name << " punches " << other.GetName()
				<< "!" << std::endl;
			ApplyDamageTo( other,power + Roll( 2 ) );
		}
	}
	void Tick()
	{
		if( IsAlive() )
		{
			const int recovery = Roll();
			std::cout << name << " recovers " << recovery << " HP." << std::endl;
			hp += recovery;
		}
	}
	virtual void SpecialMove( MemeFighter& ) = 0;
	virtual ~MemeFighter() = default;
protected:
	MemeFighter( const std::string& name,int hp,int speed,int power )
		:
		name( name ),
		hp( hp ),
		speed( speed ),
		power( power )
	{
		std::cout << name << " enters the ring!" << std::endl;
	}
	void ApplyDamageTo( MemeFighter& target,int damage ) const
	{
		target.hp -= damage;
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
	int hp;
	int speed;
	int power;
	std::string name;
private:
	mutable Dice d;
};

class MemeFrog : public MemeFighter
{
public:
	MemeFrog( const std::string& name )
		:
		MemeFighter( name,69,7,14 )
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
	void Tick()
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
	MemeStoner( const std::string& name )
		:
		MemeFighter( name,80,4,10 )
	{}
	void SpecialMove( MemeFighter& ) override
	{
		if( IsAlive() )
		{
			if( Roll() > 3 )
			{
				std::cout << GetName() << " smokes the dank sticky icky, becoming " << "Super " << GetName() << std::endl;
				name = "Super " + name;
				speed += 3;
				power = (power * 69) / 42;
				hp += 10;
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
	p1->Punch( *p2 );
	p2->Punch( *p1 );
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
	p2->SpecialMove( *p1 );
}

int main()
{
	std::vector<MemeFighter*> t1 = {
		new MemeFrog( "Dat Boi" ),
		new MemeStoner( "Good Guy Greg" ),
		new MemeFrog( "the WB Frog" )
	};
	std::vector<MemeFighter*> t2 = {
		new MemeStoner( "Chong" ),
		new MemeStoner( "Scumbag Steve" ),
		new MemeFrog( "Pepe" )
	};

	const auto alive_pred = []( MemeFighter* pf ) { return pf->IsAlive(); };
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
		std::cout << "Team ONE is victorious!" << std::endl;
	}

	for( size_t i = 0; i < t1.size(); i++ )
	{
		delete t1[i];
		delete t2[i];
	}

	while( !_kbhit() );
	return 0;
}