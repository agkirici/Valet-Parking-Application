/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Car.h
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

#ifndef SDDS_CAR_H
#define SDDS_CAR_H

#include <iostream>
#include "Vehicle.h"

namespace sdds {

    class Car : public Vehicle {
        bool m_wash = false;
        bool m_valid = false;
    public:
        Car();
        Car(const char* plate, const char* MakeModel);
        Car(const Car& C);
        Car& operator=(const Car& C);
        virtual ~Car();
        std::ostream& writeType(std::ostream& os) const;
        std::istream& read(std::istream& is = std::cin);
        std::ostream& write(std::ostream& os = std::cout) const;
    };
}

#endif 
