/* Citation and Sources...
Final Project Milestone 4
Module: Car and Motorcycle
Filename: Utils.cpp
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
#include <cstring>
#include <ctype.h>
#include "Utils.h"

using namespace std;

namespace sdds {
 
    Utils ut;
    const int alocUnit = 128;
 
    int Utils::strlen(const char* str) {
        int len = 0;
        while (str[len])
            len++;
        return len;
    }
   
    void Utils::strcpy(char* des, const char* src, int len) {
        int i;
        for (i = 0; src[i] && (len < 0 || i < len); i++)
            des[i] = src[i];
        des[i] = 0;
    }
    
    int Utils::strcmp(const char* s1, const char* s2) {
        int i;
        for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++);
        return s1[i] - s2[i];
    }
   
    int Utils::getInt(int low, int high) {
        int num;
        bool ok = false;
        do {
            cin >> num;
            if (!cin) {
                cout << "Invalid Integer, try again: ";
                cin.clear();
            } else if (num < low || num > high)
                cout << "Invalid selection, try again: ";
            else ok = true;
            cin.ignore(1000, '\n');
        } while (!ok);
        return num;
    }
    bool Utils::getYN(istream& is) {
        char ch;
        bool ok = false;
        bool res = false;
        do {
            is >> ch;
            if (!is) {
                is.clear();
                ok = true;
            } else if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'
                || ch == '0' || ch == '1') {
                if (ch == 'Y' || ch == 'y' || ch == '1')
                    res = true;
                else
                    res = false;
                ok = true;
                is.ignore(1000, '\n');
            }
            if (!ok) cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
        } while (!ok);
        return res;
    }
    int Utils::getStr(char* str, bool upper, istream& is) {
        char ch;
        bool ok = true;
        int count = 0;
        do {
            is.get(ch);
            if (is && ch && ch != ',' && ch != '\n') {
                str[count] = upper ? toupper(ch) : ch;
                count++;
            } else {
                ok = false; is.clear();
            }
        } while (ok);
        str[count] = '\0';
        return count;
    }
    int Utils::stricmp(const char* s1, const char* s2) {
        bool ok = true;
        int count = 0;
        if (ut.strlen(s1) == ut.strlen(s2)) {
            while (s1 && s2 && ok && s1[count] != '\0' && s2[count] != '\0') {
                if (toupper(s1[count]) != toupper(s2[count]))
                    ok = false;
                else count++;
            }
        } else ok = false;
        return ok ? 0 : 1;
    }
    ostream& Utils::toUpper(const char* str, ostream& os) {
        int len = ut.strlen(str);
        char c;
        for (int i = 0; i < len; i++) {
          
            if (str[i] >= 97 && str[i] <= 122) c = str[i] - 32;
            else c = str[i];
            os << c;
        }
        return os;
    }
    char* Utils::alcpy(const char* cstr) {
        char* newStr{};
        if (cstr) {
            newStr = new char[ut.strlen(cstr) + 1];
            ut.strcpy(newStr, cstr);
        }
        return newStr;
    }
    char* Utils::getDynCstr(const char* prompt) {
        bool done = false;
        if (prompt) cout << prompt;
        char* cstr = new char[alocUnit];
        char* toRet = cstr;
        int size = alocUnit;
        int nullindex = 1;
        do {
            cin.getline(cstr, alocUnit);
            if (cin.fail()) {
                char* temp = new char[size + alocUnit];
                strcpy(temp, toRet);
                delete[] toRet;
                toRet = temp;
                cstr = &toRet[size - nullindex++];
                size += alocUnit;
                cin.clear();
            } else {
                done = true;
            }
        } while (!done);
        char* temp = new char[strlen(toRet) + 1];
        strcpy(temp, toRet);
        delete[] toRet;
        toRet = temp;
        return toRet;
    }
}
