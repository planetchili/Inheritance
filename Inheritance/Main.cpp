#include <iostream>
#include <string>

class Smasher
{
public:
	Smasher()
		:
		Smasher( 69,1,"McDefault" )
	{}
	Smasher( int hp,int str,const std::string& name )
		:
		hp( hp ),
		str( str ),
		name( name )
	{}
	int GetStr() const
	{
		return str;
	}
	int GetHP() const
	{
		return hp;
	}
	const std::string& GetName() const
	{
		return name;
	}
	void Smash( Smasher& target ) const
	{
		if( target.IsDead() )
		{
			std::cout << name << " smashes " << target.GetName() << "'s dead body. Still dead.\n";
		}
		else
		{
			std::cout << name << " smashes " << target.GetName() << ".\n";
			target.TakeDamage( GetStr() );
		}
	}
	void TakeDamage( int damage )
	{
		std::cout << name << " takes " << damage << " damage.\n";
		hp -= damage;

		if( IsDead() )
		{
			std::cout << name << " dies.\n";
		}
	}
	bool IsDead() const
	{
		return hp <= 0;
	}

private:
	int hp;
	int str;
	std::string name;
};

int main()
{
	Smasher df( 100,30,"Dik Fuk" );
	Smasher tb( 120,35,"Tor Bjorn" );

	df.Smash( tb );
	tb.Smash( df );
	tb.Smash( df );
	tb.Smash( df );
	tb.Smash( df );
	tb.Smash( df );

	std::cin.get();
	return 0;
}