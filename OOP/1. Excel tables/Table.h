#pragma once
#include <string>

struct Cell
{
    std::string data;
    size_t row, column;
    Cell();
};

class Table
{
private:
    friend Menu;
    Cell** cells;
    size_t rows, columns;

private:
    void setRows(Menu& m);
    void setColumns(Menu& m);
    size_t setWidth(size_t index)const;

    std::string extractString(std::string, const char);
    std::string extractString(std::string, std::string, std::string);
    //std::string removeWhiteSpaces(Menu&);
    std::string removeWS(const std::string);
   
    void read(Menu&);

    bool isInteger(const std::string)const;
    bool isDouble(const std::string)const;
    bool isCell(const std::string)const;
    bool validCell(const size_t, const size_t)const;

    std::string check(std::string)const;

    size_t getRow(const std::string)const;
    size_t getColumn(const std::string)const;

    void execute(const std::string, const std::string);
    void execute(const std::string, const std::string, const char, const std::string);
    void calculate(const size_t, const size_t, const std::string, const char, const std::string);

public:
    Table();
    ~Table();

    void init(Menu&);
    void edit(std::string);
    void print()const;
};

