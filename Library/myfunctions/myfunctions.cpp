// My functions

#include <iostream>
#include <math.h>
//#include <string>
#include "myfunctions.h"


namespace mfAE {
    
    // begin Rand()
    Rand::Rand() {
        set(0, 9, false);
    }
    Rand::Rand(bool seed) {
        set(0, 9, seed);
    }
    Rand::Rand(int Upper) {        
        set(0, Upper, false);
    }
    Rand::Rand(int Upper, bool seed) {        
        set(0, Upper, seed);
    }
    Rand::Rand(int Lower, int Upper) {
        set(Lower, Upper, false);
    }
    Rand::Rand(int Lower, int Upper, bool seed) {
        set(Lower, Upper, seed);
    }
    void Rand::set(int Lower, int Upper, bool seed) {
        if (seed)
            srand(static_cast<unsigned>(time(NULL)));
        lower = Lower;
        upper = Upper;
    }
    int Rand::get() {
        return createRandomNumber(lower, upper);
    }
    int Rand::newNbr() {
        lower = 0;
        upper = 9;
        return createRandomNumber(lower, upper);
    }
    int Rand::newNbr(int Upper) {
        lower = 0;
        upper = Upper;
        return createRandomNumber(lower, upper);
    }
    int Rand::newNbr(int Lower, int Upper) {
        lower = Lower;
        upper = Upper;
        return createRandomNumber(lower, upper);
    }
    int Rand::createRandomNumber(int lower_bound, int upper_bound) {
        int temp, difference;
        
        if (upper_bound < lower_bound) {
            temp = lower_bound;
            lower_bound = upper_bound;
            upper_bound = temp;
        }
        difference = (upper_bound - lower_bound) + 1;
        return (rand() % difference + lower_bound);	
    }
    
    
    int createRandomNumber(int lower_bound, int upper_bound) {
        int temp, difference;
        
        if (upper_bound < lower_bound) {
            temp = lower_bound;
            lower_bound = upper_bound;
            upper_bound = temp;
        }
        difference = (upper_bound - lower_bound) + 1;
        return (rand() % difference + lower_bound);	
    }
    // end Rand()
    
    
    int cStringLength(char *cString) {
        int length = 0;
        char next;
        do {
            next = cString[length++];
        } while (next != '\0');
        return length;
    }
    
    char *intToStr(int Number) {
        int length = dgtsCnt(Number), pos = 0;
        if (Number < 0) {
            length++;
        }
        char *cStr = new char[length + 1];
        if (Number < 0) {
            cStr[0] = '-';
            pos++;
        }
        for (int i = 0; i < (dgtsCnt(Number)); i++) {
            cStr[pos] = dgtToChar(Number,i + 1);
            pos++;
        }
        cStr[length] = '\0';
        return cStr;
    }
    /*
    void *intToStr(int Number, char *cStr) {
        if (cStr != NULL) {
            int length = dgtsCnt(Number);
            if (Number < 0) {
                length++;
            }
            delete [] cStr;
            char *newCstr = new char[length + 1];
            cStr = newCstr;
            cStr = intToStr(Number);
        }
    }*/
    char dgtToChar(int Number, int digit) {
        int numb = abs(Number) / pow(10, (dgtsCnt(Number) - digit));
        return intToCar(numb % 10);
    }
    int dgtsCnt(int Number) {
        int length = 0, numb = abs(Number);
        while (numb > 9) {
            length++;
            numb = numb / 10;
        }
        if (numb > 0) {
            length++;
        }
        if (Number == 0) {
            length = 1;
        }
        return length;
    }
    
    int strToInt(char *cStr) {
        int pos = 0;
        return getIntegerUntil(cStr, pos, '\0');
    }
    int getIntegerUntil(char *cStr, int &pos, char until) {
        char *temp;
        int lengthReturnChar,returnInt;
        temp = new char[strlen(cStr)];
        getUntilChar(cStr, pos,until,lengthReturnChar,temp);
        getInvertedCstr(temp);
        pos = pos + lengthReturnChar;
        returnInt = invertedCstrToInt(temp);
        delete [] temp;
        return returnInt;
    } 
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /////// getIntegerUntil() SUPPORT FUNKTIONS ////////////////////////////////
    int lengthCstr(char *cStr) {
        int i = 0;
        char next;
        do {
            next = cStr[i];
            i++;
        } while (next != '\0');
        return i;
    }
    char* getUntilChar(char *cStr, int pos, char until, 
                             int &lengthReturnChar, char *returnChar) {
        int i = pos;
        char next;
        do {
            next = cStr[i];
            i++;
        } while ( (next != until) && (next != '\0')  && (next != '\n') );
        lengthReturnChar = i - pos;
        for (int i = 0; i < lengthReturnChar - 1; i++) {
            returnChar[i] = cStr[pos + i];
        }
        returnChar[lengthReturnChar - 1] = '\0';
        return returnChar;
    }
    char* getInvertedCstr(char *cStr) {
        // takes the string cStr and returns it inverted
        // updated on 10/04/11 DON'T USE OLDER VERSION! Memmory leak issues.
        char *front = cStr, *back = front + strlen(cStr) -1,temp;
        while (front < back) {
            temp = *front;
            *front = *back;
            *back = temp;
            front++;
            back--;
        }
        return cStr;
    }
    int invertedCstrToInt(char *cStr) {
        int returnInt = 0;
        int sign = 1;
        for (int i = 0; i < ( lengthCstr(cStr) - 1); i++) {
            returnInt = returnInt + ( charToInt(cStr[i]) * pow(10, i) );
            if (cStr[i] == '-') {
                sign = -1;
            }
        }
        return (returnInt * sign);
    }
    int charToInt(char character) {
        if (isdigit(character)) {
            return character - '0';
        } else return NAN; //Test this
    }
    char intToCar(int integer) {
        return static_cast<char>(integer + static_cast<int>('0'));
    }
}