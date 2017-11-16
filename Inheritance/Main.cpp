#include <iostream>
#include <string>

class A
{
public:
	void FuncX()
	{}
private:
	int var1;
};

// use ": public Parent" to inherit from another class
class B : public A
{
public:
	void FuncY()
	{}
private:
	float var2;
};

int main()
{
	A mya;
	B myb;

	std::cout << sizeof( mya ) << std::endl;
	std::cout << sizeof( myb ) << std::endl;

	std::cin.get();
	return 0;
}