/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Utils.h
Version 1.0
Author   Yunus Emre Ertas
Revision History
-----------------------------------------------------------
Date      Reason
2022/12/08  Preliminary release
2022/12/08  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_

#include <iostream>

namespace sdds {
    class Utils {
    public:
  
        int strlen(const char* str);
        void strcpy(char* des, const char* src, int len = -1);
        int strcmp(const char* s1, const char* s2);
        char* alcpy(const char* cstr);
        char* getDynCstr(const char* prompt = nullptr);

        int getInt(int low, int high);
        bool getYN(std::istream& is);
        int getStr(char* str, bool upper, std::istream& is);
        int stricmp(const char* s1, const char* s2);
        std::ostream& toUpper(const char* srt, std::ostream& os);
    };
    extern Utils ut;
}

#endif
