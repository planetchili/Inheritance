#include <iostream>
#include <string>

class Smasher
{
public:
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

class EliteSmasher : public Smasher
{
public:
	EliteSmasher( int hp,int str,const std::string& name )
		:
		Smasher( hp,str,name )
	{}
	void SuperSmash( Smasher& target )
	{
		if( sp > 0 )
		{
			if( target.IsDead() )
			{
				std::cout << GetName() << " uses super smash on " << target.GetName() << "'s dead body. Still dead.\n";
			}
			else
			{
				std::cout << GetName() << " uses super smash on " << target.GetName() << ".\n";
				target.TakeDamage( GetStr() * 2 );
			}
			sp -= 3;
		}
		else
		{
			std::cout << GetName() << " tried to use super smash on " << target.GetName() << ", but he didn't have enough goddamn sp.\n";
		}
	}
private:
	int sp = 6;
};

int main()
{
	Smasher df( 100,30,"Dik Fuk" );
	EliteSmasher tb( 110,33,"Cunt Destroyer" );;

	df.Smash( tb );
	tb.SuperSmash( df );
	tb.SuperSmash( df );
	tb.SuperSmash( df );
	tb.SuperSmash( df );
	tb.Smash( df );

	std::cin.get();
	return 0;
}