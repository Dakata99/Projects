#pragma once
#include <fstream>
#include <string>
#include <cmath>
#include "Figures.h"

class Menu
{
private:
    friend Figures;
    std::fstream file;
    std::string name;
    
public:
    
    void open(const std::string&, Figures&);
    void close();
    void save(const Figures&);
    void saveas(const std::string, const Figures&);
    void help()const;
    void execute(const std::string&, const std::string&, Figures&);
    
    void printMenu()const;
    //bool isOpen()const;
    //void initName(const std::string);
    
private:
    void resetFile();
    std::string extractString(std::string, std::string, std::string);
    std::string takeData(std::string&);
    bool validArg(const std::string&);

    void init(Figures&);

    void createRect(std::string&, Figures& obj);
    void createCircle(std::string&, Figures& obj);
    void createLine(std::string&, Figures&);

    void print(const Figures&);
    void create(const std::string&, Figures&);
    void erase(const std::string&, Figures&);
    void translate(const std::string&, Figures&);
    void within(const std::string&, Figures&);
};
