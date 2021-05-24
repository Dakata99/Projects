#include <iostream>
#include "Menu.cpp"
#include "Figure.cpp"
#include "Figures.cpp"
#include "Rectangle.cpp"
#include "Circle.cpp"
#include "Line.cpp"

void run()
{
    Menu m;
    m.printMenu();

    Figures figures; //object of figures
    
    std::string operation;
    bool initialized = false;
    do
    {
        std::cout << "> ";
        std::getline(std::cin, operation);
        
        std::string command = operation.substr(0, operation.find(' ')), argument;
                    
        if (operation.find(' ') != std::string::npos)
            argument = operation.substr(operation.find(' ') + 1, operation.size());
        
        m.execute(command, argument, figures);

    } while (operation != "exit");
}

int main()
{
    run();
    
    return 0;
}