/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Vehicle.cpp
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
#include "Vehicle.h"
#include "Utils.h"

using namespace std;

namespace sdds {
   
    void Vehicle::setEmpty() {
        delete[] m_makeModel;
        m_makeModel = nullptr;
        m_plate[0] = '\0';
        m_spot = 0;
    }

    bool Vehicle::isEmpty() const {
        return m_makeModel == nullptr;
    }
    const char* Vehicle::getLicencePlate() const {
        return m_plate;
    }
    const char* Vehicle::getMakeModel() const {
        return m_makeModel;
    }
    int Vehicle::getParkingSpot() const {
        return m_spot;
    }
  
    Vehicle::Vehicle() :ReadWritable() {}
    Vehicle::Vehicle(const char* plate, const char* MakeModel)
        :ReadWritable() {
        if (plate && MakeModel) {
            int plateLength = ut.strlen(plate);
            int ModLength = ut.strlen(MakeModel);
            if (plateLength > 0 && ModLength > 1 && plateLength <= 8) {
                ut.strcpy(m_plate, plate);
                setMakeModel(MakeModel);
                m_spot = 0;
            } else setEmpty();
        } else setEmpty();
    }
    Vehicle::~Vehicle() {
        delete[] m_makeModel;
    }

    Vehicle& Vehicle::operator=(const Vehicle& V) {
        if (this != &V) {
            m_spot = V.m_spot;
            Vehicle::setCsv(V.isCsv()); // csv is remembered
            ut.strcpy(m_plate, V.m_plate, ut.strlen(V.m_plate));
            if (V.m_makeModel)
                setMakeModel(V.m_makeModel);
            else setEmpty();
        }
        return *this;
    }
    Vehicle::Vehicle(const Vehicle& V) {
        *this = V;
    }

    void Vehicle::setMakeModel(const char* MakeModel) {
        int len = ut.strlen(MakeModel);
        if (MakeModel && len > 1 && len <= 60) {
            delete[] m_makeModel;
            m_makeModel = nullptr;
            m_makeModel = ut.alcpy(MakeModel);
        } else setEmpty();
    }

    void Vehicle::setParkingSpot(int spot) {
        if (spot >= 0)
            m_spot = spot;
        else setEmpty();
    }

    bool Vehicle::operator==(const char* plate) const {
        int cmp = ut.stricmp(m_plate, plate);
        return cmp == 0;
    }
    bool Vehicle::operator==(const Vehicle& V) const {
        int cmp = ut.stricmp(m_plate, V.m_plate);
        return cmp == 0;
    }

    std::istream& Vehicle::read(std::istream& is) {
        char* plate = new char[128] {'\0'};
        char* MakeModel = new char[128] {'\0'};
        if (ReadWritable::isCsv()) {
            is >> m_spot;
            if (m_spot > 0) {
                is.ignore(); // ,
                ut.getStr(plate, true, is);
                ut.strcpy(m_plate, plate, ut.strlen(plate));
                ut.getStr(MakeModel, false, is);
                setMakeModel(MakeModel);
            } else setEmpty();
        } else {
            bool ok = false;
            cout << "Enter License Plate Number: ";
            do {
                if (ut.getStr(plate, true, is) > 8) {
                    cout << "Invalid License Plate, try again: ";
                } else {
                    ok = true;
                    ut.strcpy(m_plate, plate);
                }
            } while (!ok);
            ok = false;
            cout << "Enter Make and Model: ";
            do {
                int len = ut.getStr(MakeModel, false, is);
                if (len > 60 || len < 2) {
                    cout << "Invalid Make and model, try again: ";
                } else {
                    ok = true;
                    setMakeModel(MakeModel);
                }
            } while (!ok);
            m_spot = 0;
        }
        delete[] plate;
        delete[] MakeModel;
        return is;
    }

    std::ostream& Vehicle::write(std::ostream& os) const {
        if (isEmpty())
            os << "Invalid Vehicle Object" << endl;
        else {
            writeType(os);
            if (ReadWritable::isCsv()) { // check if csv
                os << getParkingSpot() << "," << getLicencePlate()
                    << "," << getMakeModel() << ",";
            } else {
                os << "Parking Spot Number: ";
                if (getParkingSpot() == 0) os << "N/A" << endl;
                else os << m_spot << endl;
                os << "License Plate: " << getLicencePlate() << endl;
                os << "Make and Model: " << getMakeModel();
            }
        }
        return os;
    }
}
