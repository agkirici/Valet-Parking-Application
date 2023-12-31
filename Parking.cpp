/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Parking.cpp
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

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Parking.h"
#include "Utils.h"
#include "Car.h"
#include "Motorcycle.h"

using namespace std;

namespace sdds {

    Parking::Parking(const char* path, int numSpots) : m_path(nullptr),
        m_menu("Parking Menu, select an action:", 0),
        m_Vmenu("Select type of the vehicle:", 1) {
        if (path && path[0] != '\0' && numSpots <= m_numSpots && numSpots >= 10) {
            m_numSpots = numSpots;
            m_path = ut.alcpy(path);
            for (int i = 0; i < MAX_PARKING_SPOTS; i++)
                m_vehicles[i] = nullptr;
        }
        if (loadData()) {
            m_menu << "Park Vehicle" << "Return Vehicle" <<
                "List Parked Vehicles" << "Find Vehicle" <<
                "Close Parking (End of day)" << "Exit Program";
            m_Vmenu << "Car" << "Motorcycle" << "Cancel";
        } else cout << "Error in data file" << endl;
    }
  
    int Parking::run() {
        int choice, ret = 1;
        bool res = false;
        if (!isEmpty()) {
            ret = 0;
            do {
                status();
                choice = m_menu.run();
                if (choice == 1) park();
                else if (choice == 2) returnV();
                else if (choice == 3) list();
                else if (choice == 4) find();
                else if (choice == 5) res = close();
                else if (choice == 6) res = exitApp();
            } while (!res);
        }
        return ret;
    }
    bool Parking::isEmpty() const {
        return m_path == nullptr;
    }
    void Parking::status() const {
        cout << "****** Valet Parking ******" << endl;
        cout << "*****  Available spots: ";
        cout.setf(ios::left);
        cout << setw(5) << m_numSpots - m_numParked << "*****" << endl;
        cout.unsetf(ios::left);
    }

    void Parking::parkVehicle(Vehicle* V, int loc) {
        V->setCsv(false);
        cout << endl;
        V->read();
        V->setParkingSpot(loc + 1);
        cout << endl << "Parking Ticket" << endl;
        V->write(cout);
        cout << endl;
        m_numParked++;
    }

    void Parking::park() {
        int selection, spotFound = -1;
        for (int i = 0; i < m_numSpots && spotFound == -1; i++)
            if (!m_vehicles[i])
                spotFound = i;
        if (spotFound >= 0) {
            selection = m_Vmenu.run();
            if (selection == 1) {
                m_vehicles[spotFound] = new Car;
                parkVehicle(m_vehicles[spotFound], spotFound);
            } else if (selection == 2) {
                m_vehicles[spotFound] = new Motorcycle;
                parkVehicle(m_vehicles[spotFound], spotFound);
            } else cout << "Parking cancelled";
            cout << endl;
        } else cout << "Parking is full" << endl << endl;
        pause();
    }

    int Parking::findVehicle(const char* heading) {
        const char* plate{};
        int loc = -1;
        plate = ut.getDynCstr("Enter License Plate Number: ");
        int len = ut.strlen(plate);
        while (len < 1 || len > 8) {
            plate = ut.getDynCstr("Invalid License Plate, try again: ");
            len = ut.strlen(plate);
        }
        for (int i = 0; i < m_numSpots && loc == -1; i++)
            if (m_vehicles[i])
                if (m_vehicles[i]->operator==(plate))
                    loc = i;
        if (loc == -1) {
            cout << endl << "License plate ";
            ut.toUpper(plate, cout);
            cout << " Not found" << endl << endl;
        } else {
            cout << endl << heading << endl;
            m_vehicles[loc]->setCsv(false);
            m_vehicles[loc]->write();
            cout << endl << endl;
        }
        delete[] plate;
        pause();
        return loc;
    }
    void Parking::pause() {
        cout << "Press <ENTER> to continue....";
        cin.ignore(1000, '\n');
    }

    void Parking::returnV() {
        cout << "Return Vehicle" << endl;
        int index = findVehicle("Returning:");
        if (index != -1) {
            delete m_vehicles[index];
            m_vehicles[index] = nullptr;
            m_numParked--;
        }
    }

    void Parking::find() {
        cout << "Vehicle Search" << endl;
        findVehicle("Vehicle found:");
    }

    void Parking::list() {
        cout << "*** List of parked vehicles ***" << endl;
        for (int i = 0; i < m_numSpots; i++)
            if (m_vehicles[i]) {
                m_vehicles[i]->setCsv(false);
                m_vehicles[i]->write(cout) << endl;
                cout << "-------------------------------" << endl;
            }
        pause();
    }

    bool Parking::close() {
        bool res = false;
        if (m_numParked == 0) {
            cout << "Closing Parking" << endl;
            res = true;
        } else {
            cout << "This will Remove and tow all remaining vehicles from the parking!"
                << endl;
            cout << "Are you sure? (Y)es/(N)o: ";
            if (ut.getYN(cin)) {
                res = true;
                cout << "Closing Parking" << endl;
                for (int i = 0; i < m_numSpots; i++)
                    if (m_vehicles[i]) {
                        cout << endl << "Towing request" <<
                            endl << "*********************" << endl;
                        m_vehicles[i]->setCsv(false);
                        m_vehicles[i]->write() << endl;
                        delete m_vehicles[i];
                        m_vehicles[i] = nullptr;
                    }
            }
            saveData();
        }
        return res;
    }

    bool Parking::exitApp() {
        bool res = false;
        cout << "This will terminate the program!" << endl;
        cout << "Are you sure? (Y)es/(N)o: ";
        if (ut.getYN(cin)) {
            res = true;
            cout << "Exiting program!" << endl;
            saveData();
        }
        return res;
    }
  
    Parking::~Parking() {
        delete[] m_path;
        for (int i = 0; i < m_numSpots; i++)
            delete m_vehicles[i];
    }
   
    bool Parking::loadData() {
        bool res = true;
        bool ok = true;
        char ch;
        Vehicle* V{};
        ifstream fin(m_path);
        while (ok && m_numParked < m_numSpots) {
            fin.get(ch);
            if (!fin.eof()) {
                V = nullptr;
                if (ch == 'C' || ch == 'c') V = new Car;
                else if (ch == 'M' || ch == 'm') V = new Motorcycle;
                else res = false;
                fin.ignore(); 
                if (res) {
                    V->setCsv(true);
                    V->read(fin);
                    m_vehicles[V->getParkingSpot() - 1] = V;
                    m_numParked++;
                }
            } else ok = false;
        }
        fin.close();
        return res;
    }

    void Parking::saveData() {
        ofstream fout(m_path);
        if (fout) {
            for (int i = 0; i < m_numSpots; i++)
                if (m_vehicles[i]) {
                    m_vehicles[i]->setCsv(true);
                    fout << *m_vehicles[i] << endl;
                }
            fout.close();
        } else cout << "Couldn't open file " << m_path << endl;
    }
}
