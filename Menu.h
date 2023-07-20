/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Menu.h
Version 1.0
Author    Yunus Emre Ertas
Revision History
-----------------------------------------------------------
Date      Reason
2022/12/08  Preliminary release
2022/12/08  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_

#include <iostream>
#include "Utils.h"

namespace sdds {
    const int MAX_NO_OF_ITEMS = 6;


    class MenuItem {
        char m_item[51];
        
        MenuItem(const MenuItem&) = delete;
        MenuItem& operator=(const MenuItem&) = delete;
       
        std::ostream& display(std::ostream& ostr = std::cout) const {
            if (m_item[0] !='\0') ostr << m_item << std::endl;
            return ostr;
        }
       
        MenuItem(const char* content = nullptr) : m_item{ 0 } {
            if (content) ut.strcpy(m_item, content, 50);
            else m_item[0] = 0;
        }
        friend class Menu;
    };
   
    class Menu {
        char m_title[51];
        int m_indent;
        int m_numItems;
        bool m_valid;
        MenuItem m_items[MAX_NO_OF_ITEMS];
        bool isEmpty() const;
        bool isFull() const;
        bool isValid() const;
        void indent(int num) const;
        void addItem(const char* item);
    public:
        void clear();

        Menu(const char* title, int indent = 0);

        Menu(const Menu& src) = delete;
        Menu& operator=(const Menu& src) = delete;

        Menu& operator=(const char* newTitle);

        Menu& operator<<(const char* item);
        void add(const char* item);

        operator bool() const;

        operator int() const;

        int run() const;

        std::ostream& display(std::ostream& ostr = std::cout) const;
    };

    std::ostream& operator<<(Menu& menu, std::ostream& ostr);
}

#endif 
