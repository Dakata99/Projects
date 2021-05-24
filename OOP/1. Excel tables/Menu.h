#pragma once
#include <fstream>

class Table;

class Menu
{
private:
    friend Table;
    std::fstream file;
    std::string name;

private:
    void open(const std::string);
    void close(const std::string);
    void save();
    void save_as(const std::string);
    void help()const;
    void exit();

private:
    std::string removeWhiteSpaces(const std::string);
    std::string change(const std::string);
    void simplify();

public:
    bool execute(const std::string, const std::string);
    void printMenu()const;
    bool opened()const;
};
