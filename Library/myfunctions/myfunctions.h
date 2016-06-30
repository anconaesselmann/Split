// my functions header file

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H
//#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


namespace mfAE {
    
    class Rand {    
    // turn into template so it takes int or double. If double use all deciamal places of double
    public:
        Rand();
        // initializes with a random number 0 <= number <= 9, does not seed
        Rand(bool seed);
        // initializes with a random number 0 <= number <= 9, seeds if seed is true
        Rand(int Upper);
        // initializes with a random number 0 <= number <= upper, does not seed
        Rand(int Upper, bool seed);
        // initializes with a random number 0 <= number <= upper, seeds if seed is true
        Rand(int Lower, int Upper);
        // initializes with a random number lower <= number <= upper, does not seed
        Rand(int Lower, int Upper, bool seed);
        // initializes with a random number lower <= number <= upper but, seeds if seed is true
        int get();
        // returns a random number within upper and lower
        int newNbr();
        // reinitializes with a random number 0 <= number <= 9 and returns a new random number
        int newNbr(int Upper);
        // reinitializes with a random number 0 <= number <= upper and returns a new random number
        int newNbr(int Lower, int Upper);
        // reinitializes with a random number lower <= number <= upper and returns a new random number
        
        operator int() {
            return get();
        } // conversion operator for int
        //operator double() {
           // return static_cast<double>(get());
        //} // conversion operator for double
    private:
        int lower;
        int upper;
        int createRandomNumber(int lower_bound, int upper_bound);
        void set(int Lower, int Upper, bool seed);
    };
    
    class Chance {
    public:
        Chance() {
            r = Rand(0,100,false);
            likelyhood = 100;
        }
        Chance(unsigned _likelyhood) {
            r = Rand(0,100,false);
            likelyhood = _likelyhood;
        }
        Chance(unsigned _likelyhood, bool flip) {
            r = Rand(0,100,flip);
            likelyhood = _likelyhood;
        }
        void set(unsigned _likelyhood) {
            likelyhood = _likelyhood;
        }
        bool flip() {
            if (r.get() <= likelyhood) {
                return true;
            } else return false;
        }
    private:
        Rand r;
        unsigned likelyhood;
    };
    
    int cStringLength(char *cString);
    // returns the length of a Cstring, including its null termination character
    
    int createRandomNumber(int lower_bound, int upper_bound);
    // creates a random number between lower_bound and upper_bound
    // call srand(static_cast<int>(time(NULL))); 
    
    char *intToStr(int Number);
    // returns a pointer to Number in cString form. The cString must be deleted
    // manually.
    //void *intToStr(int Number, char *cStr);
    int  dgtsCnt(int Number);
    char dgtToChar(int Number, int digit);
    
    int strToInt(char *cStr);
    //
    int strToInt(char *cStr);
    //
    int getIntegerUntil(char *cStr, int &pos, char until);
    // takes a cstring and extracts an integer starting at pos until the 
    // character "until" is reached.
    // does not check if the character pesides "until" are actually integers
    // broke when soemthing other than '/'... Investigate! 
    // (\0 caused the issue...)
    /////// getIntegerUntil() SUPPORT FUNKTIONS ////////////////////////////
    int charToInt(char character);
    char intToCar(int integer);
    int lengthCstr(char *cStr); 
    // returns the length of a cstring, including the null termination 
    // character
    char *getUntilChar(char *cStr, int pos, char until, 
                       int &lengthReturnChar, char *returnChar);
    // extracts a string from a Cstring starting with position pos, 
    // until the character "until" is reached or the end of the cstring.
    char *getInvertedCstr(char *cStr);
    // takes the string cStr and returns it inverted
    // updated on 10/04/11 DON'T USE OLDER VERSION! Memmory leak issues.
    int invertedCstrToInt(char *cStr);
    // takes the cString cStr and returns an inverted integer
}


#endif
