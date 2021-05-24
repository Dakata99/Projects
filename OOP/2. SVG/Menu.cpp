#include "Menu.h"

//public functions which can be executed outside
void Menu::open(const std::string& fileName, Figures& obj)
{
    file.open(fileName);
    if (file.is_open())
    {
        name = fileName;
        std::cout << "Successfully opened " << name << std::endl; 
        init(obj); //file is opened and we initialize figures
    }
    else
    {    
        std::cout << "Could not open " << fileName << std::endl;   
    }
}
void Menu::close()
{
    if (file.is_open())
    {
        std::cout << "Successfully closed " << name << std::endl;
        file.close();
    }
    else
    {
        std::cout << "OPEN A FILE FIRST!\n";
    }
}
void Menu::save(const Figures& obj)
{
    if (file.is_open())
    {
        file.close();
        file.open(name, std::fstream::trunc|std::fstream::out);
        file << "<svg>\n";

        for (size_t i = 0; i < obj.figures.size(); i++)
            file << obj.figures[i]->getInfo();
        
        file << "</svg>\n";
        std::cout << "Successfully saved changes to " << name << std::endl;
    }
    else
    {
        std::cout << "OPEN A FILE FIRST!\n";
    }   
}
void Menu::saveas(const std::string newFile, const Figures& obj)
{
    if (file.is_open())
    {
        std::fstream out(newFile, std::ofstream::out|std::ofstream::trunc);
        
        out << "<svg>\n";

        for (size_t i = 0; i < obj.figures.size(); i++)
            out << obj.figures[i]->getInfo();

        out << "</svg>\n";
        
        std::cout << "Successfully saved as " << newFile << std::endl;
    }
    else
        std::cout << "OPEN A FILE FIRST!\n";
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
void Menu::execute(const std::string& command, const std::string& argument, Figures& obj)
{
    if (command == "open")
    {
        if (!file.is_open())
            open(argument, obj); //open and initialize figures
        else
            std::cout << "CLOSE CURRENT FILE FIRST!\n";
    }
    else if (command == "save")
    {
        save(obj);
    }
    else if (command == "saveas")
    {
        saveas(argument, obj);
    }
    else if (command == "close")
    {
        obj.figures.clear();
        close();
    }
    else if (command == "print")
    {
        if (file.is_open())
            print(obj);
        else 
            std::cout << "OPEN A FILE FIRST!\n";
    }
    else if (command == "create")
    {
        create(argument, obj); //create a figure and add it to the vector of figures
        std::cout << "Successfully created " << argument.substr(0, argument.find(' ')) << " (" << obj.figures.size() << ")\n";
    }
    else if (command == "erase")
    {
        erase(argument, obj);
    }
    else if (command == "translate")
    {
        translate(argument, obj);
    }
    else if (command == "within")
    {
        within(argument, obj);
    }
    else if (command == "exit")
    {
        std::cout << "Exiting the program...\n";
    } 
    else
    {
        std::cout << "Invalid command!\n";
    }
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
    std::cout << "--------------------------\n";
}

//private functions which initialize all the data
void Menu::resetFile()
{
    file.clear();
    file.seekg(0);
}
std::string Menu::extractString(std::string source, std::string start, std::string end)
{
    size_t startIndex = source.find(start);
    if (startIndex == std::string::npos)
        return source;
    
    startIndex += start.length();
    size_t endIndex = source.find(end, startIndex);

    return source.substr(startIndex, endIndex - startIndex);
}
std::string Menu::takeData(std::string& argument)
{
    std::string result;
    if (argument.find('\"') != std::string::npos)
    {
        result = extractString(argument, "\"", "\"");
        argument.erase(0, argument.find(' ') + 1);
    }
    else 
    {
        result = argument.substr(0, argument.find(' '));
        argument.erase(0, result.size() + 1);
    }

    return result;
}
bool Menu::validArg(const std::string& argument) //TODO
{
    if (argument.find(' ') != std::string::npos) //has space
    {
        std::string leftSide = argument.substr(0, argument.find(' ')), 
                    rightSide = argument.substr(argument.find(' ') + 1, argument.size());
    }
    return false;
}

void Menu::init(Figures& obj)
{
    resetFile();
    std::string line;
    while (std::getline(file, line))
    {
        if (line[0] == '\t')
        {
            line = extractString(line, "<", "/>");
            std::string figure = line.substr(0, line.find(' '));
            line.erase(0, line.find(' ') + 1);
            if (figure == "rect")
            {
                createRect(line, obj);
            }
            else if (figure == "circle")
            {
                createCircle(line, obj);
            }
            else if (figure == "line")
            {
                createLine(line, obj);
            }
        }
    }
}

void Menu::createRect(std::string& argument, Figures& obj)
{
    std::string x = takeData(argument),
                y = takeData(argument),
                width = takeData(argument),
                height = takeData(argument),
                color = takeData(argument);

    obj.figures.push_back(obj.createRectangle(x, y, width, height, color));
}
void Menu::createCircle(std::string& argument, Figures& obj)
{
    std::string x = takeData(argument),
                y = takeData(argument),
                radius = takeData(argument),
                color = takeData(argument);

    obj.figures.push_back(obj.createCircle(x, y, radius, color));
}
void Menu::createLine(std::string& argument, Figures& obj)
{
    std::string x1 = takeData(argument), 
                y1 = takeData(argument), 
                x2 = takeData(argument),
                y2 = takeData(argument),
                strokeWidth = takeData(argument),
                color = takeData(argument);

    obj.figures.push_back(obj.createLine(x1, y1, x2, y2, strokeWidth, color));
}

void Menu::print(const Figures& obj)
{
    obj.print();
}
void Menu::create(const std::string& argument, Figures& obj)
{
    std::string arg = argument;
    std::string figure = arg.substr(0, arg.find(' '));
    arg.erase(0, figure.size() + 1);
    if (figure == "rect" || figure == "rectangle")
    {
        createRect(arg, obj);
    }
    else if (figure == "circle")
    {
        createCircle(arg, obj);
    }
    else if (figure == "line")
    {
        createLine(arg, obj);
    }
    else
    {
        std::cout << "This figure is not supported!\n";
    }
}
void Menu::erase(const std::string& index, Figures& obj)
{
    if (index == "all")
    {
        obj.figures.clear();
        std::cout << "All figures are erased!\n";
        return;
    }
    
    size_t i = abs(std::stoi(index));
    if (!(i >= 1 && i <= obj.figures.size()))
    {
        std::cout << "There is no figure number " << i << "!\n";
        return;
    }
    
    const std::string type = obj.figures[i - 1]->getType();
    obj.figures.erase(obj.figures.begin() + i - 1);
    std::cout << "Erased a " << type << " (" << i << ")\n";
}
void Menu::translate(const std::string& argument, Figures& obj)
{
    if (!validArg(argument)) //TODO
    {
        /* code */
    }
    
    size_t number = 0;
    std::string vertical, horizontal;
    if (argument[0] == 'v')
    {
        vertical = argument.substr(0, argument.find(' '));
        horizontal = argument.substr(argument.find(' ') + 1, argument.size());
        
        double vert = fabs(std::stod(vertical.substr(vertical.find('=') + 1, vertical.size())));
        double horiz = fabs(std::stod(horizontal.substr(horizontal.find('=') + 1, horizontal.size())));

        obj.translate(number, horiz, vert);
        std::cout << "Translated all figures\n";
    }
    else
    {
        std::string temp = argument;
        std::string index = temp.substr(0, temp.find(' '));
        temp.erase(0, temp.find(' ') + 1);
        number = abs(std::stoi(index));

        vertical = temp.substr(0, temp.find(' '));
        horizontal = temp.substr(temp.find(' ') + 1, temp.size());
        
        double vert = fabs(std::stod(vertical.substr(vertical.find('=') + 1, vertical.size())));
        double horiz = fabs(std::stod(horizontal.substr(horizontal.find('=') + 1, horizontal.size())));
        
        obj.translate(number, horiz, vert);
        std::cout << "Translated a " << obj.figures[number - 1]->getType() << " (" << number - 1 << ")\n";
    }
}
void Menu::within(const std::string& argument, Figures& obj)
{
    std::string figure = argument.substr(0, argument.find(' '));
    if (figure == "rectangle")
    {
        std::string temp = argument.substr(figure.size() + 1, argument.size());
        std::string x = takeData(temp),
                    y = takeData(temp),
                    width = takeData(temp),
                    height = takeData(temp),
                    color = takeData(temp);

        Figure* r = new Rectangle(std::stod(x), std::stod(y), std::stod(width), std::stod(height));
        obj.within(r);
        delete r;
    }
    else if (figure == "circle")
    {
        std::string temp = argument.substr(figure.size() + 1, argument.size());
        std::string x = takeData(temp),
                    y = takeData(temp),
                    radius = takeData(temp);

        Figure* c = new Circle(std::stod(x), std::stod(y), std::stod(radius));
        obj.within(c);
        delete c;
    }
    else
    {
        std::cout << "Invalid region - you can choose only between rectangle and circle!\n";
    }
}