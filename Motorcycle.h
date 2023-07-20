/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Motorcycle.h
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

#ifndef SDDS_MOTORCYCLE_H
#define SDDS_MOTORCYCLE_H

#include <iostream>
#include "Vehicle.h"

namespace sdds {
   
    class Motorcycle : public Vehicle {
        bool m_sidecar = false;
        bool m_valid = false;
    public:
        Motorcycle();
        Motorcycle(const char* plate, const char* MakeModel);
        Motorcycle(const Motorcycle& M);
        Motorcycle& operator=(const Motorcycle& M);
        virtual ~Motorcycle();
        std::ostream& writeType(std::ostream& os) const;
        std::istream& read(std::istream& is = std::cin);
        std::ostream& write(std::ostream& os = std::cout) const;
    };
}

#endif 
