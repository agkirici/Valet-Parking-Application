/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Parking.h
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

#ifndef SDDS_PARKING_H_
#define SDDS_PARKING_H_

#include "Menu.h"
#include "Vehicle.h"

const int MAX_PARKING_SPOTS = 100;

namespace sdds {
    class Parking {
        char* m_path;
        Menu m_menu;
        Menu m_Vmenu;
        Vehicle* m_vehicles[MAX_PARKING_SPOTS];
        int m_numSpots = MAX_PARKING_SPOTS;
        int m_numParked = 0;
        bool isEmpty() const;
        void status() const;
        void park();
     
        void parkVehicle(Vehicle* V, int loc);

        int findVehicle(const char* heading);
        void pause();
        void find();
        void returnV();
        void list();
        bool close();
        bool exitApp();
        bool loadData();
        void saveData();
    public:
        Parking(const char* filePath, int numSpots);
        Parking(const Parking& P) = delete;
        Parking& operator=(const Parking& P) = delete;
        int run();
        
        virtual ~Parking();
    };
}

#endif 
