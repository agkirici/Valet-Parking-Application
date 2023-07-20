/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Car.cpp
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
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Car.h"
#include "Utils.h"

using namespace std;

namespace sdds {
    Car::Car() : Vehicle() {}
    Car::Car(const char* plate, const char* MakeModel) : Vehicle(plate, MakeModel) {
        if (plate && MakeModel) {
            int plateLength = ut.strlen(plate);
            int ModLength = ut.strlen(MakeModel);
            if (plateLength > 0 && plateLength <= 8 && ModLength > 1 && ModLength <= 60)
                m_valid = true;
        } else m_valid = false;
    }
    
    Car::Car(const Car& C) {
        *this = C;
    }
    
    Car& Car::operator=(const Car& C) {
        if (this != &C) {
            Vehicle::operator=(C); // here
            m_valid = true;
        } else m_valid = false;
        return *this;
    }
    Car::~Car() {}
    std::ostream& Car::writeType(std::ostream& os) const {
        if (Vehicle::ReadWritable::isCsv()) os << "C,";
        else os << "Vehicle type: Car" << endl;
        return os;
    }

    std::istream& Car::read(std::istream& is) {
        if (Vehicle::ReadWritable::isCsv()) {
            Vehicle::read(is);
            m_wash = ut.getYN(is);
            m_valid = true;
        } else {
            cout << "Car information entry" << endl;
            Vehicle::read(is);
            cout << "Carwash while parked? (Y)es/(N)o: ";
            m_wash = ut.getYN(is);
            m_valid = true;
        }
        return is;
    }

    std::ostream& Car::write(std::ostream& os) const {
        if (m_valid) {
            Vehicle::write(os);
            bool res = Vehicle::ReadWritable::isCsv();
            if (res)
                os << m_wash;
            else if (!res) {
                os << endl;
                if (m_wash) os << "With Carwash";
                else os << "Without Carwash";
            }
        } else {
            os << "Invalid Car Object" << endl;
        }
        return os;
    }
}
