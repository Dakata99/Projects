#include <iostream>
#include <string>
#include <fstream>
#include "Menu.cpp"
#include "Table.cpp"

// std::string removeWS(std::string source)
// {
//     std::string temp;
//     for (size_t i = 0; i < source.size(); i++)
//     {
//         if (source[i] != ' ')
//         {
//             temp += source[i];
//         }   
//     }
//     return temp;
// }

// std::string extractString(std::string source, const char end)
// {
//     size_t startIndex = source.find(end);
//     if (startIndex == std::string::npos)
//     {
//         return source;
//     }
    
//     return source.substr(0, source.find(end));
// }
// // std::string extractString(std::string source, std::string start, std::string end)
// // {
// //     size_t startIndex = source.find(start);
// //     if (startIndex == std::string::npos)
// //     {
// //         return "";
// //     }
// //     startIndex += start.length();

// //     size_t endIndex = source.find(end, startIndex);

// //     return source.substr(startIndex, endIndex - startIndex);
// // }

void run()
{
    Menu m;
    m.printMenu();
    Table t;

    std::string operation;
    bool printable = false, editable = false;
    do
    {
        std::cout << "> ";
        std::getline(std::cin, operation);

        //if operation has an arument like open then we seperate it in 2 strings, otherwise it doesnt have
        std::string command = operation, argument; 
        if (operation.find(' ') != std::string::npos)
        {
            command = operation.substr(0, operation.find(' '));
            argument = operation.substr(operation.find(' ') + 1, operation.size());
        }
        
        if (m.execute(command, argument))
        {
            t.init(m); //file is opened and then we initialize the table
            printable = editable = true; //and table can be printed and edited
        }
        else if (command == "close")
        {
            printable = editable = false;
        }
        
        if (command == "print" && printable)
        {
            t.print();
        }
        else if (command == "edit" && editable)
        {
            t.edit(argument);
        }

    } while (operation != "exit");
}

int main()
{
    run();

    return 0;
}