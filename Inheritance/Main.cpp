#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm>
#include <memory>
#include "MemeFrog.h"
#include "MemeStoner.h"
#include "Bat.h"
#include "Fists.h"
#include "Knife.h"


int main()
{
	auto fists = std::make_shared<Fists>();
	auto bat = std::make_shared<Bat>();
	auto knife = std::make_shared<Knife>();

	std::vector<std::unique_ptr<MemeFighter>> t1;
	t1.push_back( std::make_unique<MemeFrog>( "Dat Boi",fists ) );
	t1.push_back( std::make_unique<MemeStoner>( "Good Guy Greg",bat ) );
	t1.push_back( std::make_unique<MemeFrog>( "the WB Frog",knife ) );

	std::vector<std::unique_ptr<MemeFighter>> t2;
	t2.push_back( std::make_unique<MemeStoner>( "Chong",std::move( fists ) ) );
	t2.push_back( std::make_unique<MemeStoner>( "Scumbag Steve",std::move( bat ) ) );
	t2.push_back( std::make_unique<MemeFrog>( "Pepe",std::move( knife ) ) );

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