/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Motorcycle.cpp
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
#include "Motorcycle.h"
#include "Utils.h"

using namespace std;

namespace sdds {

    Motorcycle::Motorcycle() : Vehicle() {}
 
    Motorcycle::Motorcycle(const char* plate, const char* MakeModel)
        : Vehicle(plate, MakeModel) {
        if (plate && MakeModel) {
            int plateLength = ut.strlen(plate);
            int ModLength = ut.strlen(MakeModel);
            if (plateLength > 0 && ModLength > 1 && plateLength <= 8)
                m_valid = true;
        } else m_valid = false;
    }

    Motorcycle::Motorcycle(const Motorcycle& M) {
        *this = M;
    }
    Motorcycle& Motorcycle::operator=(const Motorcycle& M) {
        if (this != &M) {
            Vehicle::operator=(M);
            m_valid = true;
        } else m_valid = false;
        return *this;
    }
    Motorcycle::~Motorcycle() {}
    std::ostream& Motorcycle::writeType(std::ostream& os) const {

        if (Vehicle::ReadWritable::isCsv()) os << "M,";
        else os << "Vehicle type: Motorcycle" << endl;
        return os;
    }

    std::istream& Motorcycle::read(std::istream& is) {
        if (Vehicle::ReadWritable::isCsv()) {
            Vehicle::read(is);
            m_sidecar = ut.getYN(is);
            m_valid = true;
        } else {
            cout << "Motorcycle information entry" << endl;
            Vehicle::read(is);
            cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
            m_sidecar = ut.getYN(is);
            m_valid = true;
        }
        return is;
    }
  
    std::ostream& Motorcycle::write(std::ostream& os) const {
        if (m_valid) {
            Vehicle::write(os);
            bool res = Vehicle::ReadWritable::isCsv();
            if (res)
                os << m_sidecar;
            else if (!res) {
                if (m_sidecar)
                    os << endl << "With Sidecar";
            }
        } else os << "Invalid Motorcycle Object" << endl;
        return os;
    }
}
