#include "States/Arch/Application.hpp"

#include <stdexcept>
#include <iostream>

int main()
{
    /*Google Translate dit : bonjour monde !*/

	try
	{
		States::Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
