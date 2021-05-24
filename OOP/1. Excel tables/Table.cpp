#include <vector>
#include <cmath>
#include <sstream>
#include "Table.h"

Cell::Cell():data(""){}

void Table::setRows(Menu& m)
{
    size_t lines = 0;
    std::string line;
    while (std::getline(m.file, line))
    {
        lines++;
    }
    rows = lines;
}
void Table::setColumns(Menu& m)
{
    m.file.clear();
    m.file.seekg(0);

    std::string line;
    size_t cols = 0;
    while (std::getline(m.file, line))
    {
        size_t counter = 0;
        for (size_t i = 0; i < line.size(); i++)
        {
            if (line[i] == ',')
            {
                counter++;
            }
        }
        if (cols <= counter)
        {
            cols = counter;
        }
    }
    columns = cols + 1;
}
size_t Table::setWidth(size_t index)const
{
    size_t max = 0;
    for (size_t i = 0; i < rows; i++)
    {
        if (max <= cells[i][index].data.size())
        {
            max = cells[i][index].data.size();
        }
    }
    
    return max;
}

std::string Table::extractString(std::string source, const char end)
{
    // size_t startIndex = source.find(end); 
    // if (startIndex == std::string::npos)
    // {
    //     return source;
    // }

    // size_t endIndex = source.find(end, startIndex + 1);
    // std::string temp = source.substr(0, source.find(end));
    // return source.substr(startIndex, endIndex - startIndex);

    size_t startIndex = source.find(end), endIndex = source.find(end, startIndex + 1);
    return source.substr(0, source.find(end));
}
std::string Table::extractString(std::string source, std::string start, std::string end)
{
    size_t startIndex = source.find(start);
    if (startIndex == std::string::npos)
    {
        return source;
    }
    startIndex += start.length();

    size_t endIndex = source.find(end, startIndex);

    return source.substr(startIndex, endIndex - startIndex);
}
// std::string Table::removeWhiteSpaces(Menu& m)
// {
//     m.file.clear();
//     m.file.seekg(0);
//     std::string temp;
//     char symbol;
//     while (m.file >> std::noskipws >> symbol)
//     {
//         if (symbol != ' ')
//         {
//             temp += symbol;
//         }
//     }
//     return temp;
// }
std::string Table::removeWS(const std::string source)
{
    std::string temp;
    for (size_t i = 0; i < source.size(); i++)
    {
        if (source[i] != ' ')
        {
            temp += source[i];
        }
    }
    return temp;
}

void Table::read(Menu& m)
{
    m.file.clear();
    m.file.seekg(0);
    
    std::vector<std::string> vec;
    std::string line;
    while (std::getline(m.file, line))
    {
        //simplifying by removing all white spaces
        std::string temp = removeWS(line);
        vec.push_back(temp);
    }
    
    //then pushing the actual data(strings before ',' its the data in the cell)
    std::vector<std::string> vec2;
    for (size_t i = 0; i < vec.size(); i++)
    {
        while (vec[i] != "")
        {
            vec2.push_back(extractString(vec[i], ','));
            vec[i] = vec[i].erase(0, extractString(vec[i], ',').size() + 1);
        }
        vec2.push_back("\n");
    }
    
    std::vector<std::string> temp;
    for (size_t i = 0; i < vec2.size(); i++)
        temp.push_back(extractString(vec2[i], "\"", "\""));

    // for (size_t i = 0; i < temp.size(); i++)
    // {
    //     std::cout << temp[i] << std::endl;
    // }
    
    
    // for (size_t i = 0; i < vec2.size(); i++)
    // {
    //     std::cout << vec2[i] << " ";
    // }
    


    size_t i = 0, j = 0;
    for (size_t k = 0; k < vec2.size(); k++)
    {
        if (vec2[k] == "\n")
        {
            i++;
            j = 0;
        }
        else
        {
            cells[i][j].data = vec2[k];
            j++;
        }
    }

    // for (size_t i = 0; i < rows; i++)
    // {
    //     for (size_t j = 0; j < columns; j++)
    //     {
    //         std::cout << cells[i][j].data << " ";
    //     }
    //     std::cout << std::endl;
    // }
}

bool Table::isInteger(const std::string digit)const
{
    if (digit == "")
        return false;
    
    size_t i = 0;

    if (digit[0] == '-')
        i = 1;

    
    for (; i < digit.size(); i++)
        if (!(digit[i] >= '0' && digit[i] <= '9'))
            return false;

    return true;
}
bool Table::isDouble(std::string source)const
{
    if (source == "")
        return false;
    
    size_t counter = 0;
    for (size_t i = 0; i < source.size(); i++)
        if (source[i] == '.')
            counter++;


    if (counter > 1 || source[0] == '.' || source[source.size() - 1] == '.')
        return false;

    
    if (counter == 1)
    {
        if (source[0] == '-')
            return isInteger(source.substr(1, source.find('.') - 1)) && isInteger(source.substr(source.find('.') + 1, source.size()));

        else
            return isInteger(source.substr(0, source.find('.'))) && isInteger(source.substr(source.find('.') + 1, source.size()));
    }
    
    return isInteger(source);
}
bool Table::isCell(const std::string operand)const
{
    if (operand[0] != 'R' || operand[1] == 'C' || operand[operand.size()] == 'C' || operand.find('C') == std::string::npos)
    {
        return false;
    }
    else if (!isInteger(operand.substr(1, operand.find('C') - 1)))
    {
        return false;
    }
    else if (!isInteger(operand.substr(operand.find('C') + 1, operand.size())))
    {
        return false;
    }

    return true;
}
bool Table::validCell(const size_t row, const size_t column)const
{
    return row >= 1 && row <= rows && column >= 1 && column <= columns;
}

std::string Table::check(std::string source)const
{
    if (isCell(source))
    {
        return "cell";
    }
    else if (isDouble(source))
    {
        return "number";
    }
    else 
    {
        return "string";
    }
    
    return "";
}

size_t Table::getRow(const std::string source)const
{
    return std::stoi(source.substr(1, source.find('C')));
}
size_t Table::getColumn(const std::string source)const
{
    return std::stoi(source.substr(source.find('C') + 1, source.size()));
}

void Table::execute(const std::string lhs, const std::string rhs)
{
    size_t row = getRow(lhs), column = getColumn(lhs);
    if (!(row >= 1 && row <= rows && column >= 1 && column <= columns))
    {
        std::cout << "No such cell(" << lhs << ") in table!\n";
        std::cout << "This table has " << rows << " rows and " << columns << " columns.\n";
        return;
    }
    
    std::string type = check(rhs);
    if (type == "cell")
    {
        size_t rhsRow = getRow(rhs), rhsColumn = getColumn(rhs);

        if (rhsRow >= 1 && rhsRow <= rows && rhsColumn >= 1 && rhsColumn <= columns)
            cells[row - 1][column - 1].data = cells[rhsRow - 1][rhsColumn - 1].data;
        else 
            cells[row - 1][column - 1].data = "0";
    }
    else if (type == "number")
    {
            double number = std::stod(rhs);
            std::stringstream s;
            s << number;
            cells[row - 1][column - 1].data = s.str();
    }
    else if (type == "string")
    {
        cells[row - 1][column - 1].data = rhs;
    }
}
void Table::execute(const std::string cell, const std::string larg, const char oper, const std::string rarg)
{
    size_t row =  getRow(cell), column = getColumn(cell);
    if (!(row >= 1 && row <= rows && column >= 1 && column <= columns))
    {
        std::cout << "No such cell(" << cell << ") in this table\n";
        std::cout << "This table has " << rows << " rows and " << columns << " columns.\n";
        return;
    }
     
    std::string type1 = check(larg);
    std::string type2 = check(rarg);
    if (type1 == "cell" && type2 == "cell")
    {
        calculate(row, column, larg, oper, rarg);
    }
    else if (type1 == "cell" && type2 == "number")
    {
        size_t largRow = getRow(larg), largColumn = getColumn(larg);
                
        type1 = check(cells[largRow - 1][largColumn - 1].data);
        if (type1 == "number")
        {
            double num1 = std::stod(cells[largRow - 1][largColumn - 1].data);
            double num2 = std::stod(rarg);

            std::stringstream s;
            switch (oper)
            {
                case '+': s << num1 + num2; cells[row - 1][column - 1].data = s.str(); break;
                case '-': s << num1 - num2; cells[row - 1][column - 1].data = s.str(); break;
                case '*': s << num1 * num2; cells[row - 1][column - 1].data = s.str(); break;
                case '/': 
                    if (num2 == 0)
                    {
                        cells[row - 1][column - 1].data = "ERROR";
                    }
                    else
                    {
                        s << num1 / num2; 
                        cells[row - 1][column - 1].data = s.str();
                    }break;
                case '^': s << pow(num1, num2); cells[row - 1][column - 1].data = s.str(); break;
            }
        }
        else
        {
            cells[row - 1][column - 1].data = "0";
        }
    }
    else if (type1 == "number" && type2 == "cell")
    {
        size_t rargRow = getRow(rarg), rargColumn = getColumn(rarg);

        type2 = check(cells[rargRow - 1][rargColumn - 1].data);
        if (type2 == "number")
        {
            double num1 = std::stod(larg);
            double num2 = std::stod(cells[rargRow - 1][rargColumn - 1].data);

            std::stringstream s;
            switch (oper)
            {
                case '+': s << num1 + num2; cells[row - 1][column - 1].data = s.str(); break;
                case '-': s << num1 - num2; cells[row - 1][column - 1].data = s.str(); break;
                case '*': s << num1 * num2; cells[row - 1][column - 1].data = s.str(); break;
                case '/': 
                    if (num2 == 0)
                    {
                        cells[row - 1][column - 1].data = "ERROR";
                    }
                    else
                    {
                        s << num1 / num2; 
                        cells[row - 1][column - 1].data = s.str();
                    } 
                    break;
                case '^': s << pow(num1, num2); cells[row - 1][column - 1].data = s.str(); break;
            }
        }
        else
        {
            if (oper == '^')
            {
                std::stringstream s;
                s << pow(std::stod(larg), 0);
                cells[row - 1][column - 1].data = s.str();
            }
            else
            {
                cells[row - 1][column - 1].data = "ERROR";
            }
        }
    }
    else if (type1 == "number" && type2 == "number")
    {
        double num1 = std::stod(larg), num2 = std::stod(rarg);

        std::stringstream s;
        switch (oper)
        {
            case '+': s << num1 + num2; cells[row - 1][column - 1].data = s.str(); break;
            case '-': s << num1 - num2; cells[row - 1][column - 1].data = s.str(); break;
            case '*': s << num1 * num2; cells[row - 1][column - 1].data = s.str(); break;
            case '/': 
                if (num2 == 0)
                {
                    cells[row - 1][column - 1].data = "ERROR";
                }
                else
                {
                    s << num1 / num2;
                    cells[row - 1][column - 1].data = s.str();
                }   
                break;
            case '^': s << pow(num1, num2); cells[row - 1][column - 1].data = s.str(); break;
        }
    } 
}
void Table::calculate(const size_t row, const size_t column, const std::string larg, const char oper, const std::string rarg)
{
    size_t largRow = getRow(larg), largColumn = getColumn(larg);
    size_t rargRow = getRow(rarg), rargColumn = getColumn(rarg);        

    bool cell1 = validCell(largRow, largColumn), cell2 = validCell(rargRow, rargColumn);
    if (cell1 && cell2)
    {
        std::string type1 = check(cells[largRow - 1][largColumn - 1].data);
        std::string type2 = check(cells[rargRow - 1][rargColumn - 1].data);
        if (type1 == "number" && type2 == "number")
        {
            double num1 = std::stod(cells[largRow - 1][largColumn - 1].data);
            double num2 = std::stod(cells[rargRow - 1][rargColumn - 1].data);

            std::stringstream s;
            switch (oper)
            {
                case '+': s << num1 + num2; cells[row - 1][column - 1].data = s.str(); break;
                case '-': s << num1 - num2; cells[row - 1][column - 1].data = s.str(); break;
                case '*': s << num1 * num2; cells[row - 1][column - 1].data = s.str(); break;
                case '/': 
                    if (num2 == 0)
                    {
                        cells[row - 1][column - 1].data = "ERROR";
                    }
                    else
                    { 
                        s << num1 / num2; 
                        cells[row - 1][column - 1].data = s.str();
                    }                      
                    break;
                case '^': s << pow(num1, num2); cells[row - 1][column - 1].data = s.str(); break;
            }
        }
        else if(type1 == "number" && type2 != "number")
        {
            double num1 = std::stod(cells[largRow - 1][largColumn - 1].data);
            double num2 = 0.0;
            double result = 0.0;
        
            std::stringstream s;
            switch (oper)
            {
                case '+': result = num1 + num2; s << result; cells[row - 1][column - 1].data = s.str(); break;
                case '-': result = num1 - num2; s << result; cells[row - 1][column - 1].data = s.str(); break;
                case '*': result = num1 * num2; s << result; cells[row - 1][column - 1].data = s.str(); break;
                case '/': cells[row - 1][column - 1].data = "ERROR"; break;
                case '^': s << pow(num1, 0); cells[row - 1][column - 1].data = s.str(); break;
            }
        }
        else if (type1 != "number" && type2 == "number")
        {
            double num1 = 0.0;
            double num2 = std::stod(cells[rargRow - 1][rargRow - 1].data);
            double result = 0.0;

            std::stringstream s;
            switch (oper)
            {
                case '+': result = num1 + num2; s << result; cells[row - 1][column - 1].data = s.str(); break;
                case '-': result = num1 - num2; s << result; cells[row - 1][column - 1].data = s.str(); break;
                case '*': result = num1 * num2; s << result; cells[row - 1][column - 1].data = s.str(); break;
                case '/': cells[row - 1][column - 1].data = "0"; break;
                case '^': cells[row - 1][column - 1].data = "0";
            }
        }
        else //?
        {
            cells[row - 1][column - 1].data = "0"; //or "Invalid type"
        }
    }
    else
    {
        cells[row - 1][column - 1].data = "0";
    }
}

//public funcs
Table::Table()
{
    cells = nullptr;
}
Table::~Table()
{
    for (size_t i = 0; i < rows; i++)
    {
        delete[]cells[i];
    }
    delete[]cells;
}

void Table::init(Menu& m)
{
    if (m.file.is_open())
    {
        setRows(m);
        setColumns(m);   

        cells = new Cell*[rows];
        for (size_t i = 0; i < rows; i++)
        {
            cells[i] = new Cell[columns];
        }

        read(m);
    }
}
void Table::edit(std::string expression)
{
    std::string result = expression.substr(0, expression.find('=') - 1);
    expression.erase(0, result.size() + 3);

    std::string operand1, operand2;
    char oper;
    if (expression.find(' ') != std::string::npos)
    {
        operand1 = expression.substr(0, expression.find(' '));
        expression.erase(0, operand1.size() + 1);

        oper = expression[0];
        operand2 = expression.substr(2, expression.size());
         
        if (oper != '+' && oper != '-' && oper != '*' && oper != '/' && oper != '^')
        {
            std::cout << "Invalid operator in expression!\n";
            return;
        }
    }
    else
    {
        operand1 = expression.substr(0, expression.size());
    }

    
    if (!isCell(result))
    {
        std::cout << "Invalid expression!\n";
        return;
    }
    
    if (operand2 == "")
    {
        execute(result, operand1);
    }
    else
    {
        execute(result, operand1, oper, operand2);
    }
}
void Table::print()const
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            size_t width = setWidth(j);
            std::cout << cells[i][j].data << std::setw(width - cells[i][j].data.size() + 3) << " | ";
        }
        std::cout << std::endl;
    }
}
