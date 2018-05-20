#include "States/Arch/Application.hpp"

#include <exception>
#include <iostream>

int main()
{
    /*Google Translate dit : bonjour monde !*/

    try
    {
        st::Application app;
        app.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "\nEXCEPTION: " << e.what() << std::endl;
    }
}
