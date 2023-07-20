/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Vehicle.h
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
#ifndef SDDS_VEHICLE_H_
#define SDDS_VEHICLE_H_

#include "ReadWritable.h"

namespace sdds {

    class Vehicle : public ReadWritable {
        char m_plate[9]{ '\0' };
        char* m_makeModel = nullptr;
        int m_spot = 0;
    protected:
        void setEmpty();
        bool isEmpty() const;
        const char* getMakeModel() const;
        void setMakeModel(const char* MakeModel);
        const char* getLicencePlate() const;
    public:
        int getParkingSpot() const;
        Vehicle();
        Vehicle(const char* plate, const char* MakeModel);
        virtual ~Vehicle();
        Vehicle& operator=(const Vehicle& V);
        Vehicle(const Vehicle& V);
        void setParkingSpot(int spot);
        bool operator==(const char* plate) const;
        bool operator==(const Vehicle& V) const;
        std::istream& read(std::istream& is = std::cin);
        std::ostream& write(std::ostream& os = std::cout) const;
      
        virtual std::ostream& writeType(std::ostream& os) const = 0;
     };
}

#endif
