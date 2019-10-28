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

Ivy::Application* Ivy::CreateApplication()
{
	return new IvyApp();
}