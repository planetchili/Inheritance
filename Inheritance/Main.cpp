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

protected:
	int hp;
	int str;
private:
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
		if( sp >= 3 )
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
	void Smash( Smasher& target )
	{
		Smasher::Smash( target );
		std::cout << GetName() << " recovers 2 sp.\n";
		sp += 2;
	}
	void PepUp()
	{
		if( sp >= 2 )
		{
			std::cout << GetName() << " uses Pep Up and gains 30 hp and 10 str. His boner is so huge.\n";
			hp += 30;
			str += 10;
			sp -= 2;
		}
		else
		{
			std::cout << GetName() << " tried to use Pep Up but lacks sp. Tremendously flaccid.\n";
		}
	}
private:
	int sp = 6;
};

int main()
{
	Smasher df( 100,30,"Dik Fuk" );
	EliteSmasher tb( 110,13,"Cunt Destroyer" );;

	df.Smash( tb );
	
	tb.PepUp();
	tb.SuperSmash( df );
	tb.SuperSmash( df );
	tb.SuperSmash( df );
	tb.Smash( df );
	tb.Smash( df );
	tb.SuperSmash( df );
	tb.SuperSmash( df );

	std::cin.get();
	return 0;
}