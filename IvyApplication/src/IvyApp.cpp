#include <Ivy.h>

class IvyApp : public Ivy::Application
{
public:
	IvyApp()
	{

	}
	~IvyApp()
	{

	}
};


Ivy::Application* Ivy::CreateApp()
{
	return new IvyApp();
}