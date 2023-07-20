/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: ReadWritable.cpp
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

#include "ReadWritable.h"

namespace sdds {
   
    ReadWritable::ReadWritable() {
        m_comma = false;
    }
  
    ReadWritable::~ReadWritable() { }

    bool ReadWritable::isCsv() const {
        return m_comma;
    }
 
    void ReadWritable::setCsv(bool val) {
        m_comma = val;
    }
    
    std::ostream& operator<<(std::ostream& os, ReadWritable& R) {
        R.write(os);
        return os;
    }
    std::istream& operator>>(std::istream& is, ReadWritable& R) {
        R.read(is);
        return is;
    }
}
