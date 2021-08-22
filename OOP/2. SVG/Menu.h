#ifndef _MENU_H_
#define _MENU_H_

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
    void close(void);
    void save(const Figures&);
    void saveas(const std::string&, const Figures&);
    void help(void) const;
    void execute(const std::string&, const std::string&, Figures&);
    
    void print_menu(void) const;
    //bool isOpen(void)const;
    //void initName(const std::string);
    
private:
    void reset_file(void);
    std::string extract_string(std::string, std::string, std::string);
    std::string take_data(std::string&);
    bool valid_arg(const std::string&);

    void init(Figures&);

    void create_rectangle(std::string&, Figures&);
    void create_circle(std::string&, Figures&);
    void create_line(std::string&, Figures&);

    void print(const Figures&);
    void create(const std::string&, Figures&);
    void erase(const std::string&, Figures&);
    void translate(const std::string&, Figures&);
    void within(const std::string&, Figures&);
};

#endif