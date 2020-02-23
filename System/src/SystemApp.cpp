#include <Altair.h>
#include <iostream>


class System : public Altair::Application
{
public:
	System()
	{

	}

	~System()
	{

	}
};


Altair::Application* Altair::CreateApplication()
{
	return new System();
}