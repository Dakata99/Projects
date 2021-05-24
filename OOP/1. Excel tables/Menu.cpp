#include <iomanip>
#include "Menu.h"

std::string Menu::removeWhiteSpaces(const std::string line)
{
    std::string temp;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] != ' ')
        {
            temp += line[i];
        }
    }
    return temp;
}
std::string Menu::change(const std::string line)
{
    std::string temp;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == ',')
        {
            temp += '|';
        }
        else if (line[i] == '\0')
        {
            temp += '\n';
        }
        else
        {
            temp += line[i];
        }
    }
    return temp;
}
void Menu::simplify()
{
    if (file.is_open())
    {
        char symbol;
        std::string temp;
        while (file >> std::noskipws >> symbol)
        {
            if (symbol == ',')
            {
                temp += '|';
            }
            else
            {
                temp += symbol;
            }
        }
        file.close();
        file.open(name, std::fstream::in|std::fstream::out|std::fstream::trunc);
        file << temp;
    }
}

bool Menu::execute(const std::string command, const std::string fileName)
{
    if (command == "open" && !file.is_open())
    {
        open(fileName);
        return true;
    }
    else if (command == "open" && file.is_open())
    {
        std::cout << "You have already opened a file. To open other one - first close the current!\n";
        return false;
    }
    else if (command == "close" && file.is_open())
    {
        close(fileName);
        return false;
    }
    else if (command == "save" && file.is_open())
    {
        save();
        return false;
    }
    else if (command == "saveas" && file.is_open())
    {
        save_as(fileName);
        return false;
    }
    else if (command == "help")
    {
        help();
        return false;
    }
    else if (command == "exit")
    {
        exit();
        return false;
    }
    else if (!file.is_open())
    {
        std::cout << "Cannot execute " << command << " - invalid command or unopened file!\n";
        return false;
    }
    return false;
    // else
    // {
    //     std::cout << "The command maybe invalid or you have chosen an operation without opening a file!\n";
    //     return false;
    // }
}
void Menu::open(const std::string fileName)
{
    file.open(fileName);
    name = fileName.substr(fileName.rfind('/') + 1, fileName.size());
    if (file.is_open())
    {
        std::cout << "Successfully opened " << name << std::endl;
        return;
    }
    
    file.open("empty.txt", std::fstream::in|std::fstream::out|std::fstream::trunc);
    if (file.is_open())
    {
        std::cout << "Created and opened an empty file with name empty.txt\n";
        return;
    }
}
void Menu::close(const std::string fileName)
{
    if (file.is_open())
    {
        file.close();
        std::cout << "Successfully closed " << name << std::endl;
    }
    else
    {
        std::cout << "No file opened in order to close it\n";
    }
}
void Menu::save()
{
    if (file.is_open())
    {
        file.flush();
        std::cout << "Successfully saved " << name << std::endl;
    }
    else
    {
        std::cout << "No file opened in order to save it!\n";
    }
}
void Menu::save_as(const std::string filePath)
{
    if (file.is_open())
    {
        std::ofstream tempFile(filePath);
        std::string name = filePath.substr(filePath.rfind('/') + 1, filePath.size());    
        tempFile << file.rdbuf();
        std::cout << "Successfully saved another " << name << std::endl;
    }
    else
    {
        std::cout << "No file opened in order to save it as other file!\n";
    }
}
void Menu::help()const
{
    std::cout << "The following commands are supported:\n";
    std::cout << "open <file>   -   opens <file>\n";
    std::cout << "close     -   closes currently opened file\n";
    std::cout << "save  -   saves the currently open file\n";
    std::cout << "saveas <file>     -   saves the currently open file in <file>\n";
    std::cout << "help      -       prints this information\n";
    std::cout << "exit      -       exits the program\n";
}
void Menu::exit()
{
    std::cout << "Exiting the program...\n";
}

void Menu::printMenu()const
{
    std::cout << "---------- MENU ----------\n";
    std::cout << "1. Open\n";
    std::cout << "2. Close\n";
    std::cout << "3. Save\n";
    std::cout << "4. Save as\n";
    std::cout << "5. Help\n";
    std::cout << "6. Exit\n";
    std::cout << "7. Print\n";
    std::cout << "8. Edit\n";
    std::cout << "**Note: if you have entered an invalid command or there is no opened file for which to execute the command - the program will continue till you enter the right command(in the right order)!\n";
    std::cout << "--------------------------\n";
}
bool Menu::opened()const
{
    return file.is_open();
}

